#ifndef SQL_H
#define SQL_H
#include <iostream>
#include <iomanip>
#include "../parser/parser.h"
#include "../table/table.h"
#include "../table/typedefs.h"
using namespace std;
class SQL {
    public:
        SQL();
        Table command(string line);
        vectorlong select_recnos();
    private:
        Table t;
        vectorlong _recnos_vector;
};   



#endif //SQL