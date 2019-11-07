
#include "stdafx.h"

#include <iostream>
#include <string>
#include <QSqlDatabase>
#include <QString>
#include <QCoreApplication>

#include "frame/vtsServer.h"
#include "frame/vtsDBPool.h"
#include "frame/vtsLog.h"
#include "frame/vtsServicePool.h"
#include "Managers/hgConfigManager.h"
#include "Managers/hgDataManager.h"

#include "BlowFish/Encrypt.h"
#include "hgOnlyInstance.h"

#include "hgLogExpand.h"

#ifdef HG_DEBUG
//#include <vld.h>
#endif

#include <time.h>
#include <windows.h>  
#include < Dbghelp.h>  
#include <iostream>    
#include <vector>    
#include <tchar.h>    
using namespace std;   
//#include <vld.h>

#pragma comment(lib, "Dbghelp.lib")  


namespace NSDumpFile  
{   
    void CreateDumpFile(LPCWSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException)    
    {    
        // 创建Dump文件    
        //    
        HANDLE hDumpFile = CreateFile(lpstrDumpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);    


        // Dump信息    
        //    
        MINIDUMP_EXCEPTION_INFORMATION dumpInfo;    
        dumpInfo.ExceptionPointers = pException;    
        dumpInfo.ThreadId = GetCurrentThreadId();    
        dumpInfo.ClientPointers = TRUE;    


        // 写入Dump文件内容    
        //    
        MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);    


        CloseHandle(hDumpFile);    
    }    


    LPTOP_LEVEL_EXCEPTION_FILTER WINAPI MyDummySetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)  
    {  
        return NULL;  
    }  


    BOOL PreventSetUnhandledExceptionFilter()  
    {  
        HMODULE hKernel32 = LoadLibrary(_T("kernel32.dll"));  
        if (hKernel32 ==   NULL)  
            return FALSE;  


        void *pOrgEntry = GetProcAddress(hKernel32, "SetUnhandledExceptionFilter");  
        if(pOrgEntry == NULL)  
            return FALSE;  


        unsigned char newJump[ 100 ];  
        DWORD dwOrgEntryAddr = (DWORD) pOrgEntry;  
        dwOrgEntryAddr += 5; // add 5 for 5 op-codes for jmp far  


        void *pNewFunc = &MyDummySetUnhandledExceptionFilter;  
        DWORD dwNewEntryAddr = (DWORD) pNewFunc;  
        DWORD dwRelativeAddr = dwNewEntryAddr -  dwOrgEntryAddr;  


        newJump[ 0 ] = 0xE9;  // JMP absolute  
        memcpy(&newJump[ 1 ], &dwRelativeAddr, sizeof(pNewFunc));  
        SIZE_T bytesWritten;  
        BOOL bRet = WriteProcessMemory(GetCurrentProcess(),    pOrgEntry, newJump, sizeof(pNewFunc) + 1, &bytesWritten);  
        return bRet;  
    }  


    LONG WINAPI UnhandledExceptionFilterEx(struct _EXCEPTION_POINTERS *pException)  
    {  
        TCHAR szMbsFile[MAX_PATH] = { 0 };  
        ::GetModuleFileName(NULL, szMbsFile, MAX_PATH);  
        TCHAR* pFind = _tcsrchr(szMbsFile, '\\');  
        if(pFind)  
        {  
            QString l_str = QString("vtsServer%1.dmp").arg(time(NULL));
            *(pFind+1) = 0;  
            _tcscat(szMbsFile, reinterpret_cast<const wchar_t *>(l_str.utf16())/*_T("CrashDumpFile.dmp")*/);  
            CreateDumpFile(szMbsFile, pException);  
        }  


        // TODO: MiniDumpWriteDump  
        //FatalAppExit(-1,  _T("Fatal Error"));  
        return EXCEPTION_CONTINUE_SEARCH;  
    }  


    void RunCrashHandler()  
    {  
        SetUnhandledExceptionFilter(UnhandledExceptionFilterEx);  
        PreventSetUnhandledExceptionFilter();  
    }  
};  


#define DeclareDumpFile() NSDumpFile::RunCrashHandler();  

int main(int argc, char *argv[])
{
    // 崩溃报告dump
    DeclareDumpFile();
    QFile l_file("./tmp1");
    if (!l_file.exists())
    {
        puts("Illegal start[file does not exist]");
        int i = 5;
        while (1)
        {
            printf("%d\n",i);
            Sleep(1000);
            i--;
            if (i == 0)
            {
                return 0;
            }
        }
        return 0;
    }
    else
    {
        if (!decryption("./tmp1"))
        {
            puts("Illegal start[File open failed]");
            int i = 5;
            while (1)
            {
                printf("%d\n",i);
                Sleep(1000);
                i--;
                if (i == 0)
                {
                    return 0;
                }
            }
            return 0;
        }
    }

    hgOnlyInstance l_OnlyInstance;
    hgOnlyInstance::InstResult l_type = l_OnlyInstance.Init("vtsServer.exe");
    if (l_type == hgOnlyInstance::Inst_EXISTS)
    {
        puts("vtsServer exists");
        Sleep(2000);
        return 0;
    }
    else if (l_type == hgOnlyInstance::Inst_ERROR)
    {
        puts("vtsServer inst error");
        Sleep(2000);
        return 0;
    }


	try
	{
		// Check command line arguments.
		if (argc != 3)
		{
			std::cerr << "Usage: http_server <address> <port> <doc_root>\n";
			std::cerr << "  For IPv4, try:\n";
			std::cerr << "    receiver 0.0.0.0 80 .\n";
			std::cerr << "  For IPv6, try:\n";
			std::cerr << "    receiver 0::0 80 .\n";
			//return 1;
		}

        hgDataManager::CreateAllData();
		vtsLog::init(vtsLog::Log_Debug);
		hgLogExpand::init();
		QCoreApplication::addLibraryPath("./plugins");

		vtsDBPool::DBPoolConfig dbConfig;
		dbConfig.databaseType = hgConfigManager::m_sSysConfig->m_databaseType/*"QMYSQL"*/;
		dbConfig.databaseName = hgConfigManager::m_sSysConfig->m_databaseName/*"test"*/;
		dbConfig.hostName = hgConfigManager::m_sSysConfig->m_hostName/*"localhost"*/;
		dbConfig.username = hgConfigManager::m_sSysConfig->m_username/*"root"*/;
		dbConfig.password = hgConfigManager::m_sSysConfig->m_password/*"hg@2015"*/;
		dbConfig.maxConnectionCount = hgConfigManager::m_sSysConfig->m_maxConnectionCount/*5*/;
		dbConfig.maxWaitTime = hgConfigManager::m_sSysConfig->m_maxWaitTime/*1000*/;
		dbConfig.waitInterval = hgConfigManager::m_sSysConfig->m_waitInterval/*200*/;
		dbConfig.testOnBorrow = hgConfigManager::m_sSysConfig->m_testOnBorrow/*true*/;
		dbConfig.testOnBorrowSql = hgConfigManager::m_sSysConfig->m_testOnBorrowSql/*"SELECT 1;"*/;
		dbConfig.testTime = hgConfigManager::m_sSysConfig->m_testTime/*60*/;
		vtsDBPool dbPool(dbConfig);

		// 子线程个数,一般设置为cpu核心数*2
		int num_of_threads = hgConfigManager::m_sSysConfig->m_Threads;//8;
		vtsServicePool servicePool(num_of_threads);

		// Initialise the server.
		vtsServer s(/*argv[1], argv[2]*/hgConfigManager::m_sSysConfig->m_IP.toStdString(),hgConfigManager::m_sSysConfig->m_Port.toStdString(), dbPool, servicePool);

		// Run the server until stopped.
		s.run();
	}
	catch (std::exception& e)
	{
        std::cerr << "exception: " << e.what() << "\n";
	}

	return 0;
}
