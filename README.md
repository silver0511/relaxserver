# relaxserver

##introduction
1. a high performance network base framework
2. only for linux


##naming conventions
1. class: uppercase and split with uppercase each word[eg.class Sensitive]
2. struct: uppercase and split with "_" each word[eg. struct S_T_NODE]
3. function: lowercase and split with "_" each word[eg. void check_utf_8()]
4. class members: start with "m_" and lowercase and split with "_" each word[eg. S_T_NODE* m_fail_pointer]
5. parameter: lowercase and split with "_" each word[eg. S_T_NODE* find(const string &key_word)]
6. temporary variable: start with "l_" and lowercase and split with "_" each word[eg. string l_single_word]
7. static variable: start with "s_" and lowercase and split with "_" each word[eg. static int s_word_size]
8. enum: start with "E_" and uppercase and split with "_" each word[eg. enum E_TYPE]

##step
###debug
1. ./build_clean.sh
2. ./build_prepare.sh debug
3. ./build.sh debug
4. ./run_test.sh debug
###release
1. ./build_clean.sh
2. ./build_prepare.sh release
3. ./build.sh release
4. ./run_test.sh release

##start
cd ./bin/debug[release]
./start