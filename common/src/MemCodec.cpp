/*
 * file_name: MemCodec.cpp
 * file_detail:implementation memory decoder and encoder
 * created by silver0511
 */

#include "common/MemCodec.h"

USING_RELAX_NAMESPACE

MemCodec::MemCodec(ubyte *buffer, ulong buf_len, ICodec::ENUM_TYPE type)
{
    m_buffer = buffer;
    m_buf_len = buf_len;
    m_type = type;
    m_cur_pos = 0;

    if(m_type != READ && m_type != WRITE)
        throw (-1);

    //host is big endian or little endian
    m_big_endian = false;
    ushort l_value = 0x1234;
    ubyte *lp_first_char = (ubyte *)&l_value;
    if(*lp_first_char == 0x12)
        m_big_endian = true;
}

MemCodec::~MemCodec()
{
    m_buffer = NULL;
    m_buf_len = 0;
    m_cur_pos = 0;
}

long MemCodec::codec(bool &value)
{
    long l_size = sizeof(bool);
    if(m_buf_len < (m_cur_pos + l_size))
        throw(-1);

    if(m_type == READ)
        memcpy(&value, m_buffer + m_cur_pos, l_size);
    else
        memcpy(m_buffer + m_cur_pos, &value, l_size);

    m_cur_pos += l_size;

    return l_size;
}

long MemCodec::codec(byte &value)
{
    long l_size = sizeof(byte);
    if(m_buf_len < (m_cur_pos + l_size))
        throw(-1);

    if(m_type == READ)
        memcpy(&value, m_buffer + m_cur_pos, l_size);
    else
        memcpy(m_buffer + m_cur_pos, &value, l_size);

    m_cur_pos += l_size;

    return l_size;
}

long MemCodec::codec(ubyte &value)
{
    long l_size = sizeof(ubyte);
    if(m_buf_len < (m_cur_pos + l_size))
        throw(-1);

    if(m_type == READ)
        memcpy(&value, m_buffer + m_cur_pos, l_size);
    else
        memcpy(m_buffer + m_cur_pos, &value, l_size);

    m_cur_pos += l_size;

    return l_size;
}

long MemCodec::codec(short &value)
{
    long l_size = sizeof(short);
    if(m_buf_len < (m_cur_pos + l_size))
        throw(-1);

    short l_temp_val = 0;
    if(m_type == READ)
    {
        memcpy(&l_temp_val, m_buffer + m_cur_pos, l_size);
        value = func_ntoh<short>(l_temp_val);
    }
    else
    {
        l_temp_val = func_hton<short>(value);
        memcpy(m_buffer + m_cur_pos, &l_temp_val, l_size);
    }

    m_cur_pos += l_size;

    return l_size;
}

long MemCodec::codec(ushort &value)
{
    long l_size = sizeof(ushort);
    if(m_buf_len < (m_cur_pos + l_size))
        throw(-1);

    ushort l_temp_val = 0;
    if(m_type == READ)
    {
        memcpy(&l_temp_val, m_buffer + m_cur_pos, l_size);
        value = func_ntoh<ushort>(l_temp_val);
    }
    else
    {
        l_temp_val = func_hton<ushort>(value);
        memcpy(m_buffer + m_cur_pos, &l_temp_val, l_size);
    }

    m_cur_pos += l_size;

    return l_size;
}

long MemCodec::codec(int &value)
{
    long l_size = sizeof(int);
    if(m_buf_len < (m_cur_pos + l_size))
        throw(-1);

    int l_temp_val = 0;
    if(m_type == READ)
    {
        memcpy(&l_temp_val, m_buffer + m_cur_pos, l_size);
        value = func_ntoh<int>(l_temp_val);
    }
    else
    {
        l_temp_val = func_hton<int>(value);
        memcpy(m_buffer + m_cur_pos, &l_temp_val, l_size);
    }

    m_cur_pos += l_size;

    return l_size;
}

long MemCodec::codec(uint &value)
{
    long l_size = sizeof(uint);
    if(m_buf_len < (m_cur_pos + l_size))
        throw(-1);

    uint l_temp_val = 0;
    if(m_type == READ)
    {
        memcpy(&l_temp_val, m_buffer + m_cur_pos, l_size);
        value = func_ntoh<uint>(l_temp_val);
    }
    else
    {
        l_temp_val = func_hton<uint>(value);
        memcpy(m_buffer + m_cur_pos, &l_temp_val, l_size);
    }

    m_cur_pos += l_size;

    return l_size;
}

long MemCodec::codec(int64 &value)
{
    long l_size = sizeof(int64);
    if(m_buf_len < (m_cur_pos + l_size))
        throw(-1);

    int64 l_temp_val = 0;
    if(m_type == READ)
    {
        memcpy(&l_temp_val, m_buffer + m_cur_pos, l_size);
        value = func_ntoh<int64>(l_temp_val);
    }
    else
    {
        l_temp_val = func_hton<int64>(value);
        memcpy(m_buffer + m_cur_pos, &l_temp_val, l_size);
    }

    m_cur_pos += l_size;

    return l_size;
}

long MemCodec::codec(uint64 &value)
{
    long l_size = sizeof(uint64);
    if(m_buf_len < (m_cur_pos + l_size))
        throw(-1);

    uint64 l_temp_val = 0;
    if(m_type == READ)
    {
        memcpy(&l_temp_val, m_buffer + m_cur_pos, l_size);
        value = func_ntoh<uint64>(l_temp_val);
    }
    else
    {
        l_temp_val = func_hton<uint64>(value);
        memcpy(m_buffer + m_cur_pos, &l_temp_val, l_size);
    }

    m_cur_pos += l_size;

    return l_size;
}

long MemCodec::codec(float &value)
{
    long l_size = sizeof(float);
    if(m_buf_len < (m_cur_pos + l_size))
        throw(-1);

    float l_temp_val = 0;
    if(m_type == READ)
    {
        memcpy(&l_temp_val, m_buffer + m_cur_pos, l_size);
        value = func_ntoh<float>(l_temp_val);
    }
    else
    {
        l_temp_val = func_hton<float>(value);
        memcpy(m_buffer + m_cur_pos, &l_temp_val, l_size);
    }

    m_cur_pos += l_size;

    return l_size;
}

long MemCodec::codec(double &value)
{
    long l_size = sizeof(double);
    if(m_buf_len < (m_cur_pos + l_size))
        throw(-1);

    double l_temp_val = 0;
    if(m_type == READ)
    {
        memcpy(&l_temp_val, m_buffer + m_cur_pos, l_size);
        value = func_ntoh<double>(l_temp_val);
    }
    else
    {
        l_temp_val = func_hton<double>(value);
        memcpy(m_buffer + m_cur_pos, &l_temp_val, l_size);
    }

    m_cur_pos += l_size;

    return l_size;
}

long MemCodec::codec(char *value)
{
    long l_head_size = sizeof(ushort);
    if(m_buf_len < (m_cur_pos + l_head_size))
        throw(-1);

    ushort l_head_val = 0;
    if(m_type == READ)
    {
        //read head
        memcpy(&l_head_val, m_buffer + m_cur_pos, l_head_size);

        m_cur_pos += l_head_size;

        //read body
        if(m_buf_len < (m_cur_pos + l_head_val))
            throw (-2);

        memcpy(value, m_buffer + m_cur_pos, l_head_val);
        value[l_head_val] = 0;
    }
    else
    {
        l_head_val = (ushort)strlen(value);
        if(m_buf_len < (m_cur_pos + l_head_val + l_head_size))
            throw (-2);

        //write head
        memcpy(m_buffer + m_cur_pos, &l_head_val, l_head_size);

        m_cur_pos += l_head_size;

        //write body
        memcpy(m_buffer + m_cur_pos, value, l_head_val);
    }

    m_cur_pos += l_head_val;

    return (l_head_val + l_head_size);
}

long MemCodec::codec(wchar_t *value)
{
    long l_head_size = sizeof(ushort);
    if(m_buf_len < (m_cur_pos + l_head_size))
        throw(-1);

    ushort l_head_val = 0;
    if(m_type == READ)
    {
        //read head
        memcpy(&l_head_val, m_buffer + m_cur_pos, l_head_size);

        m_cur_pos += l_head_size;

        //read body
        if(m_buf_len < (m_cur_pos + l_head_val * sizeof(wchar_t)))
            throw (-2);

        l_head_val = l_head_val * sizeof(wchar_t);
        memcpy((char *)value, m_buffer + m_cur_pos, l_head_val);
        value[l_head_val] = 0;
    }
    else
    {
        l_head_val = (ushort)wcslen((const wchar_t *)value);
        if(m_buf_len < (m_cur_pos + l_head_val * sizeof(wchar_t) + l_head_size))
            throw (-2);

        //write head
        memcpy(m_buffer + m_cur_pos, &l_head_val, l_head_size);

        m_cur_pos += l_head_size;

        l_head_val = l_head_val * sizeof(wchar_t);
        //write body
        memcpy(m_buffer + m_cur_pos, (char *)value, l_head_val);
    }

    m_cur_pos += l_head_val;

    return (l_head_val + l_head_size);
}

long MemCodec::codec(ubyte *value, uint &buf_len)
{
    uint l_head_size = sizeof(uint);
    if(m_buf_len < (m_cur_pos + l_head_size))
        throw(-1);

    if(m_type == READ)
    {
        //read_head
        memcpy(&buf_len, m_buffer + m_cur_pos, l_head_size);

        m_cur_pos += l_head_size;

        //read body
        if(m_buf_len < (m_cur_pos + buf_len))
            throw (-2);

        memcpy(value, m_buffer + m_cur_pos, buf_len);
    }
    else
    {
        if(m_buf_len < (m_cur_pos + buf_len + l_head_size))
            throw (-2);

        //write head
        memcpy(m_buffer + m_cur_pos, &buf_len, l_head_size);
        m_cur_pos += l_head_size;

        //write body
        memcpy(m_buffer + m_cur_pos, value, buf_len);
    }

    m_cur_pos += buf_len;

    return (buf_len + l_head_size);
}

long MemCodec::codec(string &value)
{
    long l_head_size = sizeof(ushort);
    if(m_buf_len < (m_cur_pos + l_head_size))
        throw(-1);

    ushort l_head_val = 0;
    if(m_type == READ)
    {
        //read head
        memcpy(&l_head_val, m_buffer + m_cur_pos, l_head_size);

        m_cur_pos += l_head_size;

        //read body
        if(m_buf_len < (m_cur_pos + l_head_val))
            throw (-2);

        char *l_char_value = new char[l_head_val + 1];
        zero_memory(l_char_value, l_head_val + 1);
        memcpy(l_char_value, m_buffer + m_cur_pos, l_head_val);
        value = l_char_value;
        SAFE_DELETE_ARRAY(l_char_value);
    }
    else
    {
        l_head_val = (ushort)value.size();
        if(m_buf_len < (m_cur_pos + l_head_val + l_head_size))
            throw (-2);

        //write head
        memcpy(m_buffer + m_cur_pos, &l_head_val, l_head_size);

        m_cur_pos += l_head_size;

        //write body
        memcpy(m_buffer + m_cur_pos, value.c_str(), l_head_val);
    }

    m_cur_pos += l_head_val;

    return (l_head_val + l_head_size);
}

long MemCodec::codec(wstring &value)
{
    long l_head_size = sizeof(ushort);
    if(m_buf_len < (m_cur_pos + l_head_size))
        throw(-1);

    ushort l_head_val = 0;
    if(m_type == READ)
    {
        //read head
        memcpy(&l_head_val, m_buffer + m_cur_pos, l_head_size);

        m_cur_pos += l_head_size;

        //read body
        if(m_buf_len < (m_cur_pos + l_head_val * sizeof(wchar_t)))
            throw (-2);

        wchar_t* l_wchar_value = new wchar_t[l_head_val + 1];
        l_wchar_value[l_head_val] = 0;
        l_head_val = l_head_val * sizeof(wchar_t);
        memcpy((char *)l_wchar_value, m_buffer + m_cur_pos, l_head_val);
        value = l_wchar_value;
        SAFE_DELETE_ARRAY(l_wchar_value);
    }
    else
    {
        l_head_val = (ushort)wcslen(value.c_str());
        if(m_buf_len < (m_cur_pos + l_head_val * sizeof(wchar_t) + l_head_size))
            throw (-2);

        //write head
        memcpy(m_buffer + m_cur_pos, &l_head_val, l_head_size);

        m_cur_pos += l_head_size;

        l_head_val = l_head_val * sizeof(wchar_t);
        //write body
        memcpy(m_buffer + m_cur_pos, (char *)value.c_str(), l_head_val);
    }

    m_cur_pos += l_head_val;

    return (l_head_val + l_head_size);
}