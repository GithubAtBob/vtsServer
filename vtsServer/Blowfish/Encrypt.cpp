#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include <time.h>

#include "Encrypt.h"
#include "Blowfish.h"
#include "CryptTool.h"
#include "DiskInfo.h"

void BlowfishEncrypt( char* input, size_t inlen, char* output, size_t outlen )
{
    int the_remain = inlen%8;
    if ( the_remain != 0 )
    {
        int new_len = inlen + (8-the_remain);
        char * new_buf = (char* )malloc( new_len );
        memcpy(new_buf,input,inlen);
        memset(new_buf+inlen,3,new_len-inlen);
        input = new_buf;
        inlen = new_len;
    }

    char * encrypted_buf = (char* )malloc( inlen*2+1 );

	CBlowFish blow_fish((unsigned char*)"JMU05926181767MTI",17);
    blow_fish.Encrypt( (unsigned char*)input, (unsigned char*)encrypted_buf, inlen, CBlowFish::ECB );
    CharStr2HexStr((unsigned char*)encrypted_buf, output, inlen);

    if (the_remain != 0)
        free( input );
}

void BlowfishDecrypt( char* input, size_t inlen, char* output, size_t outlen )
{
	int tmp_len = inlen/2;
	char* tmp_buf = new char[tmp_len];
	memset(output,3,outlen);

	HexStr2CharStr(input,(unsigned char *)tmp_buf,tmp_len);

	CBlowFish blow_fish((unsigned char*)"JMU05926181767MTI",17);
	int the_remain = tmp_len%8;
	if (the_remain !=0 )
	{
		tmp_len = tmp_len+(8-the_remain);
	}
	blow_fish.Decrypt((unsigned char *)tmp_buf,(unsigned char*)output,tmp_len,CBlowFish::ECB);

	for (int i_len = outlen-1 ; i_len>=0 ; --i_len)
	{
		if (output[i_len] == 3)
		{
			output[i_len] = 0;
		}
		else
		{
			break;
		}
	}
	delete tmp_buf;
}

static bool VerifySdaSerialNumber(const char *filePath)
{
	DiskInfo diskInfo;
	//int n = disk.m_serialNumberVec.size();
	//DiskInfo::Instance().LoadDiskInfo();
	diskInfo.LoadDiskInfo();
	if ( diskInfo.GetCount() <= 0 )
	{
		return false;
	}

	const char *local_sda_serialnumber = diskInfo.getSerialNumber(0);
	if ( strlen(local_sda_serialnumber) <= 0 )
	{
		return false;
	}

	FILE* fp = fopen(filePath,"r");
	if (fp)
	{
		char szbuf[128];
		char decrypted_sda_serialnubmer[128];
		memset(szbuf,0,128);
		memset(decrypted_sda_serialnubmer,0,128);
		fscanf(fp,"%s\n",szbuf);
		BlowfishDecrypt(szbuf,strlen(szbuf),decrypted_sda_serialnubmer,128);
		if (memcmp(local_sda_serialnumber,
			decrypted_sda_serialnubmer,strlen(local_sda_serialnumber)) == 0)
		{
			return true;
		}

        // 仅仅是为了兼容用
        change_byte_order((char *)local_sda_serialnumber, strlen(local_sda_serialnumber));
		if (memcmp(local_sda_serialnumber,
			decrypted_sda_serialnubmer,strlen(local_sda_serialnumber)) == 0)
		{
			return true;
		}
	}
	return false;
}

bool decryption( const char *filePath )
{
	if ( !VerifySdaSerialNumber(filePath) )
	{
		return false;
	}
	return true;
}

bool checkDateTime(const char *filePath, char *errMsg)
{
    FILE* fp = fopen(filePath,"r");
    if (!fp)
    {
        strcpy(errMsg, "时间文件不存在");
        return false;
    }

    // 时间文件，名称一般为：datetime.dat
    // 内容如下：
    // 使用有效期,hg-expired-date~hg2015-09-28
    // 上次启动时间,预防被修改系统时间,hg-last-date~hg2015-09-28

    char szbuf[128];
    char expired_date[128];
    char last_date[128];
    memset(szbuf,0,128);
    memset(expired_date,0,128);
    memset(last_date,0,128);

    time_t now = time(NULL);
    struct tm *now_tm = localtime(&now);

    fscanf(fp,"%s\n",szbuf);
    BlowfishDecrypt(szbuf,strlen(szbuf),expired_date,128);
    if (strncmp(expired_date, "hg-expired-date~hghelloworld", 18) != 0)
    {
        strcpy(errMsg, "时间出错");
        return false;
    } 

    fscanf(fp,"%s\n",szbuf);
    BlowfishDecrypt(szbuf,strlen(szbuf),last_date,128);
    if (strncmp(last_date, "hg-last-date~hghelloworld", 15) != 0)
    {
        strcpy(errMsg, "时间出错");
        return false;
    }

    struct tm t1;
    memset(&t1, 0, sizeof(struct tm));
    sscanf(last_date+15, "%d-%d-%d", &t1.tm_year, &t1.tm_mon, &t1.tm_mday);
    t1.tm_year -= 1900;
    t1.tm_mon -= 1;
    //strftime(last_date+15, 10, "%Y-%m-%d", &t1);
    if (now <= mktime(&t1))
    {
        strcpy(errMsg, "时间被修改了");
        return false;
    }

    struct tm t2;
    memset(&t2, 0, sizeof(struct tm));
    sscanf(expired_date+18, "%d-%d-%d", &t2.tm_year, &t2.tm_mon, &t2.tm_mday);
    t2.tm_year -= 1900;
    t2.tm_mon -= 1;
    //strftime(expired_date+18, 10, "%Y-%m-%d", &t2);
    if (now >= mktime(&t2))
    {
        strcpy(errMsg, "时间已经过期!");
        return false;
    }

    fclose(fp);
    fp = fopen(filePath,"r");
    if (!fp)
    {
        strcpy(errMsg, "文件打开出错");
        return false;
    }

    fprintf(fp, "%s\n", expired_date);
    strftime(last_date, 128, "%Y-%m-%d", now_tm);
    BlowfishEncrypt(last_date, strlen(last_date), szbuf, 128);
    fprintf(fp, "%s\n", szbuf);
    fclose(fp);

    int delta = (mktime(&t2) - now)/60/60/24;
    if (delta > 0 && delta <= 30)
        sprintf(errMsg, "有效期只剩%d天，请注意!", delta);

    return true;
}

#if 0
bool createDateTimeFile(const char *filePath, int day)
{
    FILE *fp = fopen(filePath, "w");
    if (!fp)
        return false;

    char szbuf[128];
    char expired_date[128];
    char last_date[128];
    memset(szbuf,0,128);
    memset(expired_date,0,128);
    memset(last_date,0,128);

    time_t now = time(NULL);
    struct tm *now_tm = localtime(&now);

    time_t tmp_t = now + day*60*60*24;

    strncpy(expired_date, "hg-expired-date~hghelloworld", 18);
    strftime(szbuf, 128, "%Y-%m-%d", localtime(&tmp_t));
    strncat(expired_date, szbuf, strlen(szbuf));
    BlowfishEncrypt(expired_date,strlen(expired_date),szbuf,128);
    fprintf(fp,"%s\n",szbuf);

    tmp_t = now;
    strncpy(last_date, "hg-last-date~hghelloworld", 15);
    strftime(szbuf, 128, "%Y-%m-%d", localtime(&tmp_t));
    strncat(last_date, szbuf, strlen(szbuf));
    BlowfishEncrypt(last_date,strlen(last_date),szbuf,128);
    fprintf(fp,"%s\n",szbuf);
    fclose(fp);

    return true;
}
#endif
