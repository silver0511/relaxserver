/*
 * file_name: ICodec.h
 * file_detail:codec interface,virtual decoder and encoder
 * created by silver0511
 */

#ifndef __RX_ICODEC_H__
#define __RX_ICODEC_H__

#include "common/platform.h"

RELAX_NAMESPACE_BEGIN

    class ICodec
    {
    public:
        typedef function<long(ubyte *, ulong)> ICustomCodec;

        enum ENUM_CODEC_TYPE
        {
            READ = 1,
            WRITE
        };

    public:
        //encode and decode
        virtual long codec(bool &value) = 0;
        virtual long codec(byte &value) = 0;
        virtual long codec(ubyte &value) = 0;
        virtual long codec(short &value) = 0;
        virtual long codec(ushort &value) = 0;
        virtual long codec(int &value) = 0;
        virtual long codec(uint &value) = 0;
        virtual long codec(int64 &value) = 0;
        virtual long codec(uint64 &value) = 0;
        virtual long codec(float &value) = 0;
        virtual long codec(double &value) = 0;
        //string end by '\0'
        virtual long codec(char *value) = 0;
        virtual long codec(wchar_t *value) = 0;
        //array
        virtual long codec(ubyte *value, uint &buf_len) = 0;
        virtual long codec(string &value) = 0;
        virtual long codec(wstring &value) = 0;
        //offset
        virtual long codec(int &value, uint offset) = 0;
        //custom
        virtual long codec(ICustomCodec custom_codec) = 0;

        virtual uint get_pos() = 0;
        virtual ENUM_CODEC_TYPE get_codec_type() = 0;
        virtual ulong get_buf_len() = 0;
    protected:
        ENUM_CODEC_TYPE   m_type;
    };

RELAX_NAMESPACE_END

#endif //__RX_ICODEC_H__
