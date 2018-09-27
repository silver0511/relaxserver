/*
 * file_name: System.h
 * file_detail:base system tool
 * created by silver0511
 */


#ifndef __RX_SYSTEM_H__
#define __RX_SYSTEM_H__
#include "common/platform.h"

RELAX_NAMESPACE_BEGIN

    class System
    {
    public:
        System();
        ~System();
        /**
         * thread sleep
         * @param ms_time time of millisecond
         */
        static void sleep(ulong ms_time);
        /**
         * @return time of microsecond
         */
        static int64 get_micro_time();
        /**
         * @return time of millisecond
         */
        static int64 get_ms_time();
        /**
         * @return time of second
         */
        static time_t get_time();
        /**
         * @return milli count
         */
        static int get_ms_count();
        /**
         * @param s_local_time OUT struct of localtime
         */
        static void get_local_time(OUT tm &s_local_time);
        /**
         * init random seed
         */
        static void init_random();
        /**
         * check utf-8 size
         * @param word check condition
         * @return one word size
         */
        static int check_utf_8(char word);
        /**
         * get word vector from a text
         * @param text original text
         * @param word_vec OUT param all of the words that the text has
         */
        static void get_word_vec(const string &text, OUT vector<string> &word_vec);
        /**
         * read buffer from file
         * @param file_name
         * @param for_string is string
         * @param buf_len buffer new len
         */
        static ubyte* read_from_file(const char *file_name, bool for_string, int &buf_len);
    private:
    };

RELAX_NAMESPACE_END

#endif //__RX_SYSTEM_H__
