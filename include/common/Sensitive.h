//
// Created by shiyunjie on 2017/8/16.
//

#ifndef __RX_SENSITIVE_H__
#define __RX_SENSITIVE_H__
#include "common/platform.h"

RELAX_NAMESPACE_BEGIN

#define DEF_SENSITIVE_CONFIG "./config/sensitive_words.json"
#define DEF_REPLACE_WORD 	"*"

    class S_T_NODE
    {
    public:
        S_T_NODE();
        ~S_T_NODE();
        S_T_NODE* find(const string &key_word);
        S_T_NODE* insert(const string &key_word);
        void set_end();
        bool is_end();
        int size();
        typedef rx_hash_map<string, S_T_NODE*> S_MAP;
        typedef rx_hash_map<string, S_T_NODE*>::iterator S_MAP_ITER;
//private:
        S_MAP s_map;
        bool m_end;
    };

    class Sensitive
    {
    public:
        Sensitive();
        ~Sensitive();

    public:
        bool exists(const string &text);
        int replace(const string &in_text, string &out_text);

    private:
        void init();
        int check_utf_8(char word);
        bool check(S_T_NODE *s_t_node, const string &text, int &offset);

    private:
        S_T_NODE    m_parent_node;
    };

RELAX_NAMESPACE_END

#endif //__RX_SENSITIVE_H__
