/*
 * file_name: MemCodec.h
 * file_detail:implementation memory decoder and encoder
 *             it is prepare for network translate
 * created by silver0511
 */

#ifndef __RX_MEMCODEC_H__
#define __RX_MEMCODEC_H__

#include "common/ICodec.h"

RELAX_NAMESPACE_BEGIN

    class MemCodec : public ICodec
    {
    public:
        MemCodec();
        MemCodec(ubyte *buffer, ulong buf_len, ENUM_TYPE type);
        ~MemCodec();

    public:
        //encode and decode
        virtual long codec(bool &value);
        virtual long codec(byte &value);
        virtual long codec(ubyte &value);
        virtual long codec(short &value);
        virtual long codec(ushort &value);
        virtual long codec(int &value);
        virtual long codec(uint &value);
        virtual long codec(int64 &value);
        virtual long codec(uint64 &value);
        virtual long codec(float &value);
        virtual long codec(double &value);
        //string end by '\0'
        virtual long codec(char *value);
        virtual long codec(wchar_t *value);
        //array
        virtual long codec(ubyte *value, uint &buf_len);
        virtual long codec(string &value);
        virtual long codec(wstring &value);

        //return current cursor pos
        virtual uint get_pos() { return m_cur_pos; }
        virtual ubyte *get_buf(){ return m_buffer; }

    private:
        //user for [int64, ulong, ushort ......]
        template <typename T>
        inline T func_ntoh(T net_value)
        {
            if(!m_big_endian)
            {
                return net_value;
            }

            T l_big_end_val = 0;
            char *lp_big_char = (char *)&l_big_end_val;
            char *lp_net_char = (char *)&net_value;
            int l_len = sizeof(T);

            for(int i = 0; i < l_len; i++)
            {
                lp_big_char[i] = lp_net_char[l_len - i - 1];
            }

            return l_big_end_val;
        }

        template <typename T>
        inline T func_hton(T host_value)
        {
            if(!m_big_endian)
            {
                return host_value;
            }

            T l_host_end_val = 0;
            char *lp_big_char = (char *)&host_value;
            char *lp_little_char = (char *)&l_host_end_val;
            int l_len = sizeof(T);

            for(int i = 0; i < l_len; i++)
            {
                lp_little_char[i] = lp_big_char[l_len - i - 1];
            }

            return l_host_end_val;
        }

    private:
        ubyte   *m_buffer;
        ulong   m_cur_pos;
        ulong   m_buf_len;
        bool    m_big_endian;
    };

RELAX_NAMESPACE_END



#endif //__RX_MEMCODEC_H__
