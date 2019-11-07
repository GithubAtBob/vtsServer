#ifndef _ENCRYPT_HHH
#define _ENCRYPT_HHH
/**********************************************************************************************//**
 * @file	Encrypt.h
 *
 * @brief	Declares the encrypt class.
 **************************************************************************************************/

bool decryption( const char *filePath );

bool checkDateTime(const char *filePath, char *errMsg);

bool createDateTimeFile(const char *filePath, int day);

#endif _ENCRYPT_HHH
