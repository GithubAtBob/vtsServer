// S63Tool.h: interface for the CS63Tool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_S63TOOL_H__5040FFBA_742E_41DE_A4C0_E7A3FDA42FE9__INCLUDED_)
#define AFX_S63TOOL_H__5040FFBA_742E_41DE_A4C0_E7A3FDA42FE9__INCLUDED_
#include <stdio.h>

void Char2Hex(const unsigned char ch, char* szHex);
void Hex2Char(const char* szHex, unsigned char& rch);

// iSize Ϊ2�����ַ����ĳ���
// ת��Ϊ��ascii��ʾ��16�����ַ���
/*!
 * @param pucCharStr[int] ԭʼ2��������
 * @param pszHexStr[out] ת����ģ���ASCIIֵ��ʾ��16�����ַ���
 * @param iSize[int] ԭʼ2�������е��ֽڳ���
 */
void CharStr2HexStr(const unsigned char* pucCharStr, char* pszHexStr, int iSize);

// iSize Ϊ2�����ַ����ĳ���
// ת��Ϊ������ 
void HexStr2CharStr(const char* pszHexStr, unsigned char* pucCharStr, int iSize);

void HexStr2CharStr_ex(const char* pszHexStr, unsigned char* pucCharStr, int iSize);

// ����blowfish����
// ��Զ������ֽ�����
void BlowfishEncrypt_bin( unsigned char* input, size_t inlen, unsigned char* output, size_t* outlen);
void BlowfishDecrypt_bin( unsigned char* input, size_t inlen, unsigned char* output, size_t* outlen);

// ����blowfish����
// �����ASCII��ʾ��16�����ַ���
void BlowfishEncrypt_hex( char* input, size_t inlen, char* output, size_t outlen);
void BlowfishDecrypt_hex( char* input, size_t inlen, char* output, size_t outlen);

void SetCryptContext( char* key, size_t key_len );

#endif // !defined(AFX_S63TOOL_H__5040FFBA_742E_41DE_A4C0_E7A3FDA4  2FE9__INCLUDED_)
