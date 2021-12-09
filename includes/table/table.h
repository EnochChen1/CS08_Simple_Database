    #ifndef TABLE_H
    #define TABLE_H
    #include <iostream>
    #include <iostream>
    #include <fstream>
    #include <string>
    #include <vector>
    #include <cstring>
    #include "typedefs.h"
    #include "../binary_files/file_record.h"
    #include "../binary_files/utilities.h"
    #include "../bplustree/map.h"
    #include "../bplustree/multimap.h"
    #include "../bplustree/bplustree.h"
    #include "../queue/myQueue.h"
    #include "../token/child_tokens.h"
    #include "../rpn/rpn.h"
    #include "../shunting_yard/shunting_yard.h"
    using namespace std;

    class Table {
    public: 
        Table();
        Table(const string& name, const vector<string>& fields);
        Table(const string& name);
        void insert_into(const vector<string>& row);
        Table select_all();
        Table select(const vector<string>& fields, const string& which_field, const string& operators, const string& inside_field);
        Table select(const vectorstr& fields, const vectorstr& infix);
        Table select(const vectorstr& fields, const Queue<Token*>& postfix);
        vectorstr get_fields() const;
        vectorlong select_recnos() const;
        void reindex();
        void set_fields(const vectorstr& fields);
        // void table_for_simple_select(Table &t, vectorlong records, FileRecord r2, fstream &ft);
        friend ostream& operator <<(ostream& outs, const Table & t) {
            fstream f;
            FileRecord r2;
            //open the file for reading and writing.
            string table_name = t.table_name;
            // cout << table_name << endl;
            // cout << t.bin_name << endl;
            // cout << t.text_name << endl;
            // cout << t._field_vector << endl;
            // cout << t._results << endl;
            open_fileRW(f, t.bin_name.c_str() );
            int selected_index = 0;
            for(int i = 0; i < t._field_vector.size(); i++) {
                if(t._field_map.contains(t._field_vector[i])) {
                    selected_index = t._field_map.at(t._field_vector[i]);   //makes sure I get the correct field_name and column
                    r2.record_holder.push_back(selected_index); //order of the field_names that is given to me
                }
            }
            outs << setw(25) << "record: ";
            for(int i = 0; i < t._field_vector.size(); i++) {
                outs << setw(25) << t._field_vector[i];//prints field_vector as field names
            }
            outs << endl;
            for(int i = 0; i< t._results.size(); i++) {
                r2.read(f, t._results[i]);
                outs << setw(25) << i << setw(25) << r2 << endl;    //prints out records in table
            }

            /*int i = 0;
            long bytes = r2.read(f, i); //empty envelop to be filled by the FileRecord object
            while (bytes>0){
                cout<<setw(25)<<"record "<<i<<": "<<r2<<endl;
                i++;
                bytes = r2.read(f, i);
            }*/
            f.close();
            return outs;
        }
    // private:
        string table_name;
        string bin_name;
        string text_name;
        FileRecord _record;
        vector<MMap<string, long> *> _indices;
        //vector<MMap<string, long> > _field_names;
        vectorstr _field_vector;
        vectorlong _results;
        Map<string, long> _field_map;
        static int serial_no;
        int last_record;
        bool empty;
    };

    #endif //TABLE_H

