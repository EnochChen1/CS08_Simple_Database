#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include "../tokenizer/state_machine_functions.h"
#include "../tokenizer/ftokenize.h"
#include "../tokenizer/stokenize.h"
#include "../queue/MyQueue.h"
#include "../bplustree/map.h"
#include "../bplustree/multimap.h"
#include "../table/typedefs.h"

using namespace std;
class Parser {
    public:
        Parser();
        Parser(const char *s);
        void set_string(char *s);
        bool get_parse_tree();
        void build_keyword_list();
        void make_table();
        bool fail();
        void set_buffer(const char* s);
        mmap_ss parse_tree();


    private:
        MMap<string, string> ptree;
        Map<string, int> keywords_map;
        static int adjacency_table[MAX_ROWS][MAX_COLUMNS];
        Queue<Token*> input_q;
        enum keys {ZERO, SELECT, FROM, WHERE, CREATE, TABLE, FIELDS, MAKE, DROP, INSERT, INTO, VALUES, SYMBOL};
        bool fail_flag;
        char _buffer[MAX_BUFFER];
};

#endif //PARSER_H