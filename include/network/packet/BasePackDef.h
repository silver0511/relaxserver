/*
 * file_name: BasePackDef.h
 * file_detail: net pack parse
 * created by silver0511
 */

#ifndef __RX_BASEPACKDEF_H__
#define __RX_BASEPACKDEF_H__

#include "common/MemCodec.h"
#include "common/LogMacro.h"

RELAX_NAMESPACE_BEGIN

//base package
struct S_BASE_PACKAGE
{
public:
    S_BASE_PACKAGE(){}

    virtual ~S_BASE_PACKAGE(){}

    int pack(ubyte *buffer, long buf_len)
    {
        try
        {
            MemCodec l_mem_codec(buffer, buf_len, ICodec::WRITE);
            int result = codec(l_mem_codec);
            if(result < 0)
            {
                LOG_TRACE(LOG_CRIT, "pack failed result" << result)
            }

            return result;
        }
        catch (int value)
        {
            LOG_TRACE(LOG_CRIT, "pack catch value = " << value)
            return -1;
        }
    }

    int unpack(ubyte *buffer, long buf_len)
    {
        try
        {
            MemCodec l_mem_codec(buffer, buf_len, ICodec::READ);
            int result = codec(l_mem_codec);
            if(result < 0)
            {
                LOG_TRACE(LOG_CRIT, "unpack failed result = " << result)
            }

            return result;
        }
        catch (int value)
        {
            LOG_TRACE(LOG_CRIT, "unpack catch value = " << value)
            return -1;
        }
    }
public:
    //code and encode
    virtual long codec(ICodec &codec_interface) = 0;
};

//net general head
struct S_GENERAL_HEAD_PACKAGE : public S_BASE_PACKAGE
{
public:
    short m_len;
    short m_msg_type;
    int64 m_route_id;
    short m_pack_session_id;
    byte  m_compress_type;
    byte  m_protocol_type;
public:
    S_GENERAL_HEAD_PACKAGE()
    {
        m_len = 0;
        m_msg_type = 0;
        m_route_id = 0;
        m_pack_session_id = 0;
        m_compress_type = 0;
        m_protocol_type = 0;
    }

    virtual long codec(ICodec &codec_interface)
    {
        int len = 0;
        len += codec_interface.codec(m_len);
        len += codec_interface.codec(m_msg_type);
        len += codec_interface.codec(m_route_id);
        len += codec_interface.codec(m_pack_session_id);
        if(codec_interface.get_codec_type() == ICodec::READ)
        {
            byte l_temp_type;
            len += codec_interface.codec(l_temp_type);
            m_compress_type = l_temp_type >> 4;
            m_protocol_type = l_temp_type & 0xFFFF;
        }
        else
        {
            byte l_temp_type;
            l_temp_type = m_compress_type & 0xFFFF;
            l_temp_type = (l_temp_type << 4) | m_protocol_type;
            len += codec_interface.codec(l_temp_type);
        }

        return len;
    }
};

//general body template
template <typename PARA>
struct S_GENERAL_BODY_PACKAGE : public S_BASE_PACKAGE
{
    PARA m_body;
    S_GENERAL_BODY_PACKAGE() : S_BASE_PACKAGE() {}

    virtual long codec(ICodec &codec_interface)
    {
        return m_body.codec(codec_interface);
    }

    S_GENERAL_BODY_PACKAGE &operator = (const S_GENERAL_BODY_PACKAGE &body_obj)
    {
//        assert(&body_obj != this);
        if(&body_obj == this)
            return *this;
        m_body = body_obj.m_body;
        return *this;
    }
};

//general body pointer template
template <typename PARA>
struct S_GENERAL_BODY_P_PACKAGE : public S_BASE_PACKAGE
{
    PARA    *m_body;
    S_GENERAL_BODY_P_PACKAGE() : S_BASE_PACKAGE() {}
    virtual long codec(ICodec &codec_interface)
    {
        return m_body->codec(codec_interface);
    }

};

#define MAPPING_PACKTYPE(PACK_TYPE) \
    enum E_HOST_TYPE {\
    ENUM_TYPE = PACK_TYPE\
};\


RELAX_NAMESPACE_END

#endif //__RX_BASEPACKDEF_H__
