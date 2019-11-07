// S63Tool.h: interface for the CS63Tool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_S63TOOL_H__5040FFBA_742E_41DE_A4C0_E7A3FDA42FE9__INCLUDED_)
#define AFX_S63TOOL_H__5040FFBA_742E_41DE_A4C0_E7A3FDA42FE9__INCLUDED_
#include <stdio.h>

void Char2Hex(const unsigned char ch, char* szHex);
void Hex2Char(const char* szHex, unsigned char& rch);

// iSize 为2进制字符串的长度
// 转换为用ascii表示的16进制字符串
/*!
 * @param pucCharStr[int] 原始2进制序列
 * @param pszHexStr[out] 转换后的，用ASCII值表示的16进制字符串
 * @param iSize[int] 原始2进制序列的字节长度
 */
void CharStr2HexStr(const unsigned char* pucCharStr, char* pszHexStr, int iSize);

// iSize 为2进制字符串的长度
// 转换为二进制 
void HexStr2CharStr(const char* pszHexStr, unsigned char* pucCharStr, int iSize);

void HexStr2CharStr_ex(const char* pszHexStr, unsigned char* pucCharStr, int iSize);

// 用于blowfish加密
// 针对二进制字节序列
void BlowfishEncrypt_bin( unsigned char* input, size_t inlen, unsigned char* output, size_t* outlen);
void BlowfishDecrypt_bin( unsigned char* input, size_t inlen, unsigned char* output, size_t* outlen);

// 用于blowfish加密
// 针对用ASCII表示的16进制字符串
void BlowfishEncrypt_hex( char* input, size_t inlen, char* output, size_t outlen);
void BlowfishDecrypt_hex( char* input, size_t inlen, char* output, size_t outlen);

void SetCryptContext( char* key, size_t key_len );

#endif // !defined(AFX_S63TOOL_H__5040FFBA_742E_41DE_A4C0_E7A3FDA4  2FE9__INCLUDED_)
