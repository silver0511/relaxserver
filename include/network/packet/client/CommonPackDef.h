/*
 * file_name: CommonPackDef.h
 * file_detail: net pack parse
 * created by silver0511
 */

#ifndef __RX_COMMONPACKDEF_H__
#define __RX_COMMONPACKDEF_H__

#include "network/packet/BasePackDef.h"

RELAX_NAMESPACE_BEGIN

template <class T>
struct S_BASE_PB_PACKAGE
{
protected:
    T m_obj;

public:
    S_BASE_PB_PACKAGE() {}
    virtual ~S_BASE_PB_PACKAGE() {}

public:
    virtual long codec(ICodec &codec_interface)
    {
        if(codec_interface.get_codec_type() == ICodec::WRITE)
        {
            return codec_interface.codec(bind(&S_BASE_PB_PACKAGE::encode, this, placeholders::_1, placeholders::_2));
        }
        else
        {
            return codec_interface.codec(bind(&S_BASE_PB_PACKAGE::decode, this, placeholders::_1, placeholders::_2));
        }
    }

    virtual string dump() const { return ""; }

private:
    long encode(ubyte *buffer, ulong available_len)
    {
        int l_byte_size = m_obj.ByteSize();
        if(l_byte_size > (int)available_len)
        {
            LOG_TRACE(LOG_ERR, "buffer is not enough need = " << l_byte_size << " remain = " << available_len);
            return -1;
        }

        m_obj.SerializeToArray(buffer, l_byte_size);
        return (long)l_byte_size;
    }

    long decode(ubyte *buffer, ulong available_len)
    {
        if(!m_obj.ParseFromArray(buffer, (int)available_len))
            return -1;
        return available_len;
    }
};

RELAX_NAMESPACE_END

#endif //__RX_COMMONPACKDEF_H__
