/*
 * file_name: Sensitive.cpp
 * file_detail:check sensitive word
 * created by silver0511
 */

#include "common/Sensitive.h"
#include "rjson/JsonParser.h"
#include "common/System.h"

USING_RELAX_NAMESPACE

S_T_NODE::S_T_NODE() : m_end(false), m_level(0), m_fail_pointer(NULL)
{
}

S_T_NODE::~S_T_NODE()
{
    S_MAP_ITER iter;
    for(iter = s_map.begin(); iter != s_map.end(); iter++)
    {
        SAFE_DELETE(iter->second);
    }

    s_map.clear();
}

S_T_NODE *S_T_NODE::find(const string &key_word)
{
    S_MAP_ITER iter = s_map.find(key_word);
    if(iter == s_map.end())
    {
        return NULL;
    }

    return iter->second;
}

S_T_NODE *S_T_NODE::insert(const string &key_word, int level)
{
    S_MAP_ITER iter = s_map.find(key_word);
    if(iter != s_map.end())
    {
        return iter->second;
    }

    S_T_NODE *new_node = new S_T_NODE();
    new_node->m_level = level;
    s_map.insert(S_MAP::value_type(key_word, new_node));
    return new_node;
}

void S_T_NODE::create_fail_pointer(S_T_NODE *parent_node, OUT queue<S_T_NODE *> &trace_queue)
{
    S_T_NODE *l_fail_pointer = m_fail_pointer;
    S_T_NODE::S_MAP_ITER l_iter = s_map.begin();
    for(; l_iter != s_map.end(); ++l_iter)
    {
        S_T_NODE *l_child_node = l_iter->second;
        trace_queue.push(l_child_node);

        /**
         * if: current child node value can be founded in it's fail pointer child
         * then: set current child's fail pointer to that node
         * else: set current child's fail pointer to parent node while fail pointer is null
         */
        while(NULL != l_fail_pointer)
        {
            S_T_NODE *l_fail_node = l_fail_pointer->find(l_iter->first);
            if(NULL != l_fail_node)
            {
                l_child_node->set_fail_pointer(l_fail_node);
                break;
            }

            l_fail_pointer = l_fail_pointer->get_fail_pointer();
        }

        if(NULL == l_fail_pointer)
        {
            l_child_node->set_fail_pointer(parent_node);
        }
    }
}

void S_T_NODE::set_end()
{
    m_end = true;
}

bool S_T_NODE::is_end()
{
    return m_end;
}

int S_T_NODE::size()
{
    return s_map.size();
}

Sensitive::Sensitive() : m_replace_word(DEF_DEFAULT_REPLACE_WORD)
{
}

Sensitive::~Sensitive()
{
}

void Sensitive::set_replace_word(const string &word)
{
    m_replace_word = word;
}

bool Sensitive::exists(const string &text)
{
    int cur_index = 0;
    while(cur_index < text.size())
    {
        int offset = cur_index;
        int l_word_size = System::check_utf_8(text[offset]);
//        if(check(&m_parent_node, text, offset))
//        {
//            return true;
//        }

        cur_index = l_word_size;
    }

    return false;
}

int Sensitive::replace(const string &in_text, string &out_text)
{
    int c_count = 0;
//    int cur_index = 0;
//    bool is_sensitive = false;
//    bool is_last_sensitive = false;
//    while(cur_index < in_text.size())
//    {
//        int offset = cur_index;
//        int l_word_size = System::check_utf_8(in_text[offset]);
//        if(!check(&m_parent_node, in_text, offset))
//        {
//            out_text += in_text.substr(cur_index, l_word_size);
//            cur_index += l_word_size;
//            is_last_sensitive = false;
//            c_count++;
//        }
//        else
//        {
//            is_sensitive = true;
//            if(!is_last_sensitive)
//            {
//                out_text += m_replace_word;
//                c_count += m_replace_word.size();
//            }
//
//            if(cur_index == offset)
//            {
//                printf("[Sensitive] invalid offset: %d, text: %s \n", offset, in_text.c_str());
//                cur_index += l_word_size;
//            }
//            else
//            {
//                cur_index = offset;
//            }
//            is_last_sensitive = true;
//        }
//    }

    return c_count;
}

void Sensitive::load_from_file(const string& file_name)
{
    printf("[Sensitive load_from_file] parse json start: %lld \n", System::get_micro_time());
    RJ_CREATE_EMPTY_DOCUMENT(l_document)
    bool result = JsonParse::parse_file(l_document, file_name.c_str());
    if(!result || l_document.IsNull())
    {
        printf("[Sensitive load_from_file] read json file invalid \n");
        return;
    }

    RJsonValue &json_data_list = JsonParse::get_child(l_document, "data");
    RJ_SIZE_TYPE data_count = JsonParse::count(json_data_list);
    if(data_count <= 0)
    {
        printf("[Sensitive load_from_file] read json data not exist \n");
        return;
    }

    for (RJ_SIZE_TYPE index = 0; index < data_count; ++index)
    {
        string s_text = "";
        RJsonValue& json_value_list = JsonParse::at_child(json_data_list, index);
        RJsonValue& json_value = JsonParse::at_child(json_value_list, 0);
        if(json_value.IsInt())
        {
            s_text = std::to_string(json_value.GetInt());
        }
        else if(json_value.IsString())
        {
            s_text = json_value.GetString();
        }

        insert(s_text);
    }

    printf("[Sensitive load_from_file]  parse json end: %lld, parent_node size: %d \n", System::get_micro_time(), m_parent_node.size());
    create_fail_pointer();
    printf("[Sensitive load_from_file]  create failer point end: %lld \n", System::get_micro_time());
}

void Sensitive::load_from_memory(vector<string> word_list)
{
    printf("[Sensitive load_from_memory] parse start: %lld \n", System::get_micro_time());

    for (int index = 0; index < word_list.size(); ++index)
    {
        insert(word_list[index]);
    }

    printf("[Sensitive load_from_memory] parse end: %lld, parent_node size: %d \n", System::get_micro_time(), m_parent_node.size());
    create_fail_pointer();
    printf("[Sensitive load_from_memory]  create failer point end: %lld \n", System::get_micro_time());
}

void Sensitive::insert(const string &text)
{
    int l_index = 0;
    S_T_NODE *l_cur_node = &m_parent_node;
    string l_single_word;
    int l_level = 1;
    while(l_index < text.size())
    {
        l_single_word = get_single_word(text, l_index);
        l_cur_node = l_cur_node->insert(l_single_word, l_level);
        l_level++;
    }
    if(text.size() > 0 && l_cur_node != &m_parent_node)
    {
        l_cur_node->set_end();
    }
}

void Sensitive::create_fail_pointer()
{
    queue<S_T_NODE *> l_trace_queue;
    l_trace_queue.push(&m_parent_node);

    S_T_NODE *l_cur_node = NULL;
    while (!l_trace_queue.empty())
    {
        l_cur_node = l_trace_queue.front();
        l_trace_queue.pop();
        l_cur_node->create_fail_pointer(&m_parent_node, l_trace_queue);
    }
}


string Sensitive::get_single_word(const string &text, int &offset)
{
    int l_word_size = System::check_utf_8(text[offset]);
    string l_word = text.substr(offset, l_word_size);
    offset += l_word_size;
    return l_word;
}

bool Sensitive::check(S_T_NODE *s_t_node, const string &in_text, int &start_index, int &offset, OUT string &out_text)
{
    return true;
//    if(s_t_node->is_end())
//    {
//        //is sensitive
//        return true;
//    }
//
//    string l_single_word = get_single_word(text, offset);
//
//    S_T_NODE *l_child_node = s_t_node->find(l_single_word);
//    if(NULL == l_child_node)
//    {
//        S_T_NODE *l_fail_node = s_t_node->get_fail_pointer();
//        if(l_fail_node == NULL)
//        {
//            //is not sensitive
//            return false;
//        }
//
//        start_index += l_fail_node->m_level;
//        return check(l_fail_node, text, start_index, offset);
//    }
//
//    return check(l_child_node, text, offset);
}
