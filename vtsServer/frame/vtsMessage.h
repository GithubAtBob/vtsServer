#pragma once

#include <stdint.h>

/*
 *	MESSAGE_MINOR:0 contentSize是16bit
 *  MESSAGE_MINOR:1 contentSize是32bit
 */
const uint8_t MESSAGE_HEAD1 = 0xff;
const uint8_t MESSAGE_HEAD2 = 0x23;
const uint8_t MESSAGE_MAJOR = 1;
const uint8_t MESSAGE_MINOR = 1;

// 字节对齐
#include <PshPack1.h>

struct vtsMessageHead
{
  uint8_t head1;           // 0xff
  uint8_t head2;           // 0x23
  uint8_t majorVer;         // 1
  uint8_t minorVer;        // 1
  uint32_t contentSize;    //
  //uint16_t dump;           //
};

struct vtsMessageHead_minv0
{
    uint8_t head1;           // 0xff
    uint8_t head2;           // 0x23
    uint8_t majorVer;         // 1
    uint8_t minorVer;        // 0
    uint16_t contentSize;    //
    uint16_t dump;           //
};

#include <PopPack.h>

const int MESSAGE_HEAD_LEN = sizeof(vtsMessageHead);
const int MESSAGE_TYPE_LEN = 16;

class vtsMessagePacker
{
public:
    explicit vtsMessagePacker(const char* type, const char *msg, size_t msgLen)
    {
        size_t write_len = MESSAGE_HEAD_LEN + MESSAGE_TYPE_LEN + msgLen;
        char *write_data = new char[write_len];

        vtsMessageHead head;
        head.head1 = MESSAGE_HEAD1;
        head.head2 = MESSAGE_HEAD2;
        head.majorVer = MESSAGE_MAJOR;
        head.minorVer = MESSAGE_MINOR;
        head.contentSize = MESSAGE_TYPE_LEN + msgLen;
        //head.dump = 0;

        memcpy(write_data, &head, MESSAGE_HEAD_LEN);

        memset(write_data+MESSAGE_HEAD_LEN, 0, MESSAGE_TYPE_LEN);
        strncpy(write_data+MESSAGE_HEAD_LEN, type, MESSAGE_TYPE_LEN);

        memcpy(write_data+MESSAGE_HEAD_LEN+MESSAGE_TYPE_LEN, msg, msgLen);

        _data = write_data;
        _len = write_len;
    }
    ~vtsMessagePacker()
    {
        delete[] _data;
    }

    void *data() { return _data; }
    size_t len() { return _len; }

    void *dump()
    {
        void *d = _data;
        _data = nullptr;
        _len = 0;
        return d;
    }

protected:
    void *_data;
    size_t _len;
};