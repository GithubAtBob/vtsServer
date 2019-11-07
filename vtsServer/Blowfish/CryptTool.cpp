// S63Tool.cpp: implementation of the CS63Tool class.
//
//////////////////////////////////////////////////////////////////////

#include "CryptTool.h"
#include "string.h"

#include <time.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>

#include "Blowfish.h"

//////////////////////////////////////////////////////////////////////////

static char s_key_buf[256] = {0};
static size_t s_key_len = 0;

#define RAND_NORMAL_ASCII()   (rand()%94+33)
#define RAND_NUMBER() ( rand()%10+48 )
#define RAND_UPPER() ( rand()%26+65 )
#define RAND_LOWER() ( rand()%26+97 )

//////////////////////////////////////////////////////////////////////////

//Function to convert unsigned char to string of length 2
void Char2Hex(const unsigned char ch, char* szHex)
{
	unsigned char byte[2];
	byte[0] = ch/16;
	byte[1] = ch%16;
	for(int i=0; i<2; i++)
	{
		if(byte[i] >= 0 && byte[i] <= 9)
			szHex[i] = '0' + byte[i];
		else
			szHex[i] = 'A' + byte[i] - 10;
	}
	szHex[2] = 0;
}

//Function to convert string of length 2 to unsigned char
void Hex2Char(const char* szHex, unsigned char& rch)
{
	rch = 0;

	for(int i=0; i<2; i++)
	{
		if(*(szHex + i) >='0' && *(szHex + i) <= '9')
			rch = (rch << 4) + (*(szHex + i) - '0');
		else if(*(szHex + i) >='A' && *(szHex + i) <= 'F')
			rch = (rch << 4) + (*(szHex + i) - 'A' + 10);
		else
			break;
	}
}    

//Function to convert string of unsigned chars to string of chars
void CharStr2HexStr(const unsigned char* pucCharStr, char* pszHexStr, int iSize)
{
	int i;

	char szHex[3];
	pszHexStr[0] = 0;
	for(i=0; i<iSize; i++)
	{
		Char2Hex(pucCharStr[i], szHex);
		strcat(pszHexStr, szHex);
	}
}

//Function to convert string of chars to string of unsigned chars
void HexStr2CharStr(const char* pszHexStr, unsigned char* pucCharStr, int iSize)
{
	int i;
	unsigned char ch;
	for(i=0; i<iSize; i++)
	{
		Hex2Char(pszHexStr+2*i, ch);
		pucCharStr[i] = ch;
	}
}
// 两个16字节数加一个空格的签名文件 [5/10/2010 leslie]
void HexStr2CharStr_ex(const char* pszHexStr, unsigned char* pucCharStr, int iSize)
{
	int i;
	unsigned char ch;
	const char * pIndex = pszHexStr;
	for(i=0; i<iSize; i++)
	{
		if (i%2 ==0&&i>0)
		{
			pIndex ++;
		}
		Hex2Char(pIndex+2*i, ch);
		pucCharStr[i] = ch;
	}	
}

/********************************************************************
	created:	2010/05/08
	created:	8:5:2010   11:07
	Funcionname: 	
	input1:			
	input2:		pHashed,hash过之后的结果，为20byte引用	
	return:			
	author:		leslie
	
	purpose:	
*********************************************************************/
int getfilesize(const char *pName)
{    
#ifdef __WXMSW__
#define COMPATIBLE_STAT _stat
#else
#define COMPATIBLE_STAT stat
#endif
    // 兼容linux [7/20/2010 yyb]
	int iresult;    
	struct /*_stat*/COMPATIBLE_STAT buf;    
	iresult = /*_stat*/COMPATIBLE_STAT(pName,&buf);    
	if(iresult == 0)    
	{        
		return buf.st_size;    
	}    
	return NULL;
}

void BlowfishEncrypt_hex( char* input, size_t inlen, char* output, size_t outlen )
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

    int header = s_key_buf[0]+s_key_buf[1];
    CBlowFish blow_fish((unsigned char*)( s_key_buf+header ),s_key_len);
    blow_fish.Encrypt( (unsigned char*)input, (unsigned char*)encrypted_buf, inlen, CBlowFish::ECB );
    CharStr2HexStr((unsigned char*)encrypted_buf, output, inlen);

    if (the_remain != 0)
        free( input );
}

void BlowfishDecrypt_hex( char* input, size_t inlen, char* output, size_t outlen )
{
    int tmp_len = inlen/2;
    char* tmp_buf = (char* )malloc( tmp_len );
    memset(output,3,outlen);

    HexStr2CharStr(input,(unsigned char *)tmp_buf,tmp_len);

    int header = s_key_buf[0]+s_key_buf[1];
    CBlowFish blow_fish((unsigned char*)( s_key_buf+header ),s_key_len);
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
    free( tmp_buf );
}

void BlowfishEncrypt_bin( unsigned char* input, size_t inlen, unsigned char* output, size_t* outlen)
{
    int the_remain = inlen%8;
    if ( the_remain != 0 )
    {
        int new_len = inlen + (8-the_remain);
        unsigned char * new_buf = (unsigned char* )malloc( new_len );
        memcpy(new_buf,input,inlen);
        memset(new_buf+inlen,3,new_len-inlen);
        input = new_buf;
        inlen = new_len;
    }

    char * encrypted_buf = (char* )malloc( inlen*2+1 );

    int header = s_key_buf[0]+s_key_buf[1];
    CBlowFish blow_fish((unsigned char*)( s_key_buf+header ),s_key_len);
    blow_fish.Encrypt( input, output, inlen, CBlowFish::ECB );
    *outlen = inlen;

    if (the_remain != 0)
        free( input );
}

void  BlowfishDecrypt_bin( unsigned char* input, size_t inlen, unsigned char* output, size_t* outlen)
{
    int tmp_len = inlen;

    int header = s_key_buf[0]+s_key_buf[1];
    CBlowFish blow_fish((unsigned char*)( s_key_buf+header ),s_key_len);
    int the_remain = tmp_len%8;
    if (the_remain !=0 )
    {
        tmp_len = tmp_len+(8-the_remain);
    }
    blow_fish.Decrypt( input,(unsigned char*)output,tmp_len,CBlowFish::ECB );
    *outlen = tmp_len;

    for ( ; tmp_len>=0 ; --tmp_len)
    {
        if (output[tmp_len-1] == 3)
            output[tmp_len-1] = 0;
        else
            break;
    }

    *outlen = tmp_len;
}


void SetCryptContext( char* key, size_t key_len )
{
    srand( (unsigned int)time(NULL) );
    int header = 0;
    do 
    {
        s_key_buf[0] = RAND_NORMAL_ASCII();
        s_key_buf[1] = RAND_NORMAL_ASCII();
        header = s_key_buf[0] + s_key_buf[1];
    } while ( header <24 || header>160 );

    memcpy( s_key_buf+header, key, key_len );
    s_key_len = key_len;

    for ( int i=2; i<header; ++i )
        s_key_buf[i] = RAND_NORMAL_ASCII();

    int special = rand()%(header-16);
    while ( special == 0 || special == 1)
        special = rand()%(header-16);

    s_key_buf[special] = 'J';
    s_key_buf[special+1] = 'M';
    s_key_buf[special+2] = 'U';
    s_key_buf[special+3] = '-';
    s_key_buf[special+4] = 'M';
    s_key_buf[special+5] = 'T';
    s_key_buf[special+6] = 'I';
    s_key_buf[special+7] = '0';
    s_key_buf[special+8] = '5';
    s_key_buf[special+9] = '9';
    s_key_buf[special+10] = '2';
    s_key_buf[special+11] = '-';
    s_key_buf[special+12] = '2';
    s_key_buf[special+13] = '0';
    s_key_buf[special+14] = '1';
    s_key_buf[special+15] = '2';

    int len = s_key_len + header;
    for ( int i = 0; i< 56; ++i )
    {
        if ( len < 256 )
        {
            s_key_buf[ len ] = RAND_NORMAL_ASCII();
            ++len;
        }
    }
    s_key_buf[ len ] = '\0';
}