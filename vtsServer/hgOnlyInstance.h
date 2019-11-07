#ifndef HGONLYINSTANCE_H_
#define HGONLYINSTANCE_H_

#include <Windows.h>


class hgOnlyInstance
{
public:

    enum InstResult
    {
        Inst_OK = 0,
        Inst_ERROR,
        Inst_EXISTS,
    };

    hgOnlyInstance()
    {
        m_handle = NULL;
    }
    ~hgOnlyInstance()
    {
        ReleaseMutex(m_handle);
        ::CloseHandle(m_handle);
        m_handle = NULL;
    }

    InstResult Init( const char* name )
    {
        size_t converSize;
        WCHAR cTmp[MAX_PATH];
        memset(cTmp, 0x00, sizeof(cTmp));
        mbstowcs( cTmp ,name, strlen(name));
        m_handle = ::CreateMutex( NULL, FALSE, cTmp);
        if ( m_handle == NULL )
        {
            return hgOnlyInstance::Inst_ERROR;
        }
        else if ( ::GetLastError() == ERROR_ALREADY_EXISTS )
        {
            //::MessageBox( NULL, "程序已经打开!", "提示", MB_OK );
            return hgOnlyInstance::Inst_EXISTS;
        } 

        return hgOnlyInstance::Inst_OK;
    }

protected:
    HANDLE  m_handle;
};

#endif