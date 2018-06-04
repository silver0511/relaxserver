//
// Created by shiyunjie on 2017/8/16.
// change tired map to acautomation[tired + kmp]
//

#ifndef __RX_SENSITIVE_H__
#define __RX_SENSITIVE_H__
#include "common/platform.h"

RELAX_NAMESPACE_BEGIN

#define DEF_DEFAULT_FILE_NAME        "./config/sensitive_words.json"
#define DEF_DEFAULT_REPLACE_WORD 	 "*"

    struct S_T_NODE
    {
    private:
        S_T_NODE();
        ~S_T_NODE();
        S_T_NODE* find(const string &key_word);
        S_T_NODE* insert(const string &key_word, int level);
        void create_fail_pointer(S_T_NODE* parent_node, OUT queue<S_T_NODE *> &trace_queue);
        S_T_NODE* get_fail_pointer() {return m_fail_pointer;}
        void set_fail_pointer(S_T_NODE* node) {m_fail_pointer = node;}
        void set_end();
        bool is_end();
        int size();
    private:
        typedef rx_hash_map<string, S_T_NODE*> S_MAP;
        typedef rx_hash_map<string, S_T_NODE*>::iterator S_MAP_ITER;
        S_MAP s_map;
        bool m_end;
        int m_level;
        S_T_NODE* m_fail_pointer;

        friend class Sensitive;
    };

    class Sensitive
    {
    public:
        Sensitive();
        ~Sensitive();

    public:
        void load_from_file(const string &file_name = DEF_DEFAULT_FILE_NAME);
        void load_from_memory(vector<string> word_list);
        void set_replace_word(const string& word);
        void create_fail_pointer();
        bool exists(const string &text);
        int replace(const string &in_text, string &out_text);

    private:
        void insert(const string &text);
        string get_single_word(const string &text, int &offset);
        bool check(S_T_NODE *s_t_node, const string &text, int &offset);

    private:
        S_T_NODE    m_parent_node;
        string      m_replace_word;
    };

RELAX_NAMESPACE_END

#endif //__RX_SENSITIVE_H__
