#include "table.h"
using namespace std;
    int Table::serial_no = 0;
Table::Table() {
    //set everything to null or 0
    table_name = "";
    bin_name = "";
    text_name = "";
    _record = FileRecord();
    _field_map = Map<string, long>();
    // last_record = -1;
}

Table::Table(const string& name, const vector<string> fields) {

    serial_no++;
    table_name = name;
    last_record = -1;
    empty = true;
    _field_vector = fields;
    //making a new table, with no table
    //_field_vector.push_back(string(fields.size()));
    // _record = FileRecord(fields);
    // recordno = _record.read(_f); //gets the record number from the binary_files read(), then write into binary file
    fstream file;
    bin_name = name + ".bin";
    // open_fileRW(file, _name.c_str()); //open the binary file to write in stuff
    open_fileW(file, bin_name.c_str()); // open 
    text_name = name + ".txt";
    ofstream field_names_file;
    field_names_file.open(text_name); //create text file
    // field_names_file.open(field_names + "_fields.txt");
    for(int i = 0; i < fields.size(); i++) {    //fill out the _field_vector vector<string>
        _field_map.insert(fields[i], i);//build map for fields and number each one is
        _indices.push_back(new mmap_sl()); //build lookup maps by creating a vector for indices
        field_names_file << fields[i] << endl; //insert field_names into text file
    }
    field_names_file.close(); //closes files here
    file.close();
}

Table::Table(const string& name) {
    //call reindex
    table_name = name;
    empty = true;
    bin_name = name + ".bin";
    text_name = name + ".txt";   //doing the names
    ifstream is;
    is.open(text_name); //opens textfile
    if(is.is_open()) {
        string emp = "";
        for(int i = 0; getline(is, emp); i++) { //adds the field names from the text file
            _field_vector.push_back(emp); //to the field name vector, field map, and the indices
            _field_map.insert(_field_vector[i],i);
            _indices.push_back(new mmap_sl());
        }
    }
    is.close(); //close
    reindex();  //call reindex to rebuild the index
}

void Table::insert_into(const vector<string> row) {
    // fstream file;
    // open_fileRW(file, _name.c_str());
    // // open_fileRW(file, (_name+to_string(serial_no)+".bin").c_str());  //open binary file
    // _record = FileRecord(row);      //insert row as a record
    // long recordno = _record.write(file);   //write record into binary file and get record no from it
    // _results.push_back(last_record);
    // for(int i = 0; i < row.size(); i++) {
    //     _indices[i] -> get(row[i]).push_back(last_record);
    // }
    // last_record++;
    // file.close();    
    fstream f;
    bin_name = table_name + ".bin";
    open_fileRW(f, (bin_name).c_str()); //open the original file
    _record = FileRecord(row); //get the rows
    _record.write(f);   //get record numbers from the rows
    last_record++; //increment the number of records
    _results.push_back(last_record); //push back into vectorlong of record numbers
    for(int i = 0; i < row.size(); i++) {
         _indices[i] -> get(row[i]).push_back(last_record);//add the record number to the indices
    }
    f.close(); //then close the file
}

Table Table::select_all() {
    _results.clear(); //clears vectorlong of record nos just incase there is things I don't need
    for(int i = 0; i <= last_record; i++) {
        _results.push_back(i); // then fill it back up
    }
    Table t(table_name + to_string(serial_no), _field_vector); //then create a select table, with the specific name and all the fields

    fstream file;
    FileRecord r2;
    bin_name = table_name + ".bin";
    // open_fileRW(file, _name.c_str()); //open the binary file to write in stuff
    open_fileRW(file, bin_name.c_str());
    for(int i = 0; i < _results.size(); i++) {
        r2.read(file, _results[i]); //reads the original file, and gets the rows from the specific record numbers given
        vectorstr recordedvalues;
        for(int j = 0; j < _field_vector.size(); j++) {
            recordedvalues.push_back(r2._record[j]); //pushes the record into recorded values
        }
        t.insert_into(recordedvalues); //inserts the vectorstr into the table
        recordedvalues.clear(); //clears it so it can be used for the next one
    }
    file.close();//close file
    return t;
}

Table Table::select(vector<string> fields, string which_field, string operators, string inside_field) {
    _results.clear();
    //open the file for reading and writing.
    Table copied(table_name, fields);
    copied._field_vector = _field_vector;
    copied._results.clear();
    long field_pos = copied._field_map[which_field]; //below operators essentially do stuff that relational does
    if(operators == "=") {
        copied._results = (*copied._indices[field_pos])[inside_field];
    }
    else if(operators == "<") {
        mmap_sl::Iterator it_begins = _indices[_field_map.at(which_field)] -> begin();
        mmap_sl::Iterator it_ends = _indices[_field_map.at(which_field)] -> lower_bound(inside_field);
        for(; it_begins != it_ends; it_begins++) {
            for(int i = 0; i < (*it_begins).value_list.size(); i++) {
                copied._results.push_back((*it_begins).value_list[i]);
            }
        }
    }
    else if(operators == ">") {
    mmap_sl::Iterator it_begins = _indices[_field_map.at(which_field)] -> upper_bound(inside_field);
    mmap_sl::Iterator it_ends = _indices[_field_map.at(which_field)] -> end();
        for(; it_begins != it_ends; it_begins++) {
            for(int i = 0; i < (*it_begins).value_list.size(); i++) {
                copied._results.push_back((*it_begins).value_list[i]);
            }
        }
    }
    else if(operators == "<=") {
    mmap_sl::Iterator it_begins = _indices[_field_map.at(which_field)] -> begin();
    mmap_sl::Iterator it_ends = _indices[_field_map.at(which_field)] -> upper_bound(inside_field);
        for(; it_begins != it_ends; it_begins++) {
            for(int i = 0; i < (*it_begins).value_list.size(); i++) {
                copied._results.push_back((*it_begins).value_list[i]);
            }
        }
    }
    else if(operators == ">=") {
    mmap_sl::Iterator it_begins = _indices[_field_map.at(which_field)] -> lower_bound(inside_field);
    mmap_sl::Iterator it_ends = _indices[_field_map.at(which_field)] -> end();
        for(; it_begins != it_ends; it_begins++) {
            for(int i = 0; i < (*it_begins).value_list.size(); i++) {
                copied._results.push_back((*it_begins).value_list[i]);
            }
        }
    }
     fstream file;
    FileRecord r2;
    bin_name = table_name + ".bin";
    // open_fileRW(file, _name.c_str()); //open the binary file to write in stuff
    open_fileRW(file, bin_name.c_str());
    for(int i = 0; i < _results.size(); i++) {
        r2.read(file, _results[i]);
        vectorstr recordedvalues ;
        for(int j = 0; j < fields.size(); j++) {
            recordedvalues.push_back(r2._record[j]);
        }
        copied.insert_into(recordedvalues);
        recordedvalues.clear();
    }
    
    return copied;
    
        // typename mmap_sl::Iterator it = _indices[which_field].begin();
        // Table t(_name, fields);
        // for(it = _indices[which_field].lower_bound(inside_field); it != _indices[which_field].upper_bound(inside_field); it++) {
        //     fstream file;
        //     open_fileRW(file, _name.c_str());
        //     long recordno = _indices[which_field][inside_field];
        //     _record.read(file, recordno);
        // }
        // for(int i = 0; i< _results.size(); i++) {
        //     cout << _results[i] << " " << __LINE__ << endl;
        // }
        
}

Table Table::select(const vectorstr fields, const vectorstr& infix) {
    Queue<Token *> _infix_queue = conversion_to_queue_from_infix(infix); //gets an infix vector str
    ShuntingYard sy(_infix_queue); //creates shuntingyard object
    Queue<Token *> postfix = sy.postfix(); //then converts infix to postfix

    return select(fields, postfix); //calls select with postfix
}
Table Table::select(const vectorstr fields, const Queue<Token*>& postfix) {
    _results.clear();
    //open the file for reading and writing.
    RPN reversed(postfix);  //rpn constructor
    _results = reversed.eval(_field_map, _indices);
    Table t(table_name + to_string(serial_no), fields);   //creates a copy of the table
    
    fstream file;
    FileRecord r2;
    bin_name = table_name + ".bin";

    // open_fileRW(file, _name.c_str()); //open the binary file to write in stuff
    open_fileRW(file, bin_name.c_str()); //opened original file
    // cout << "_results.size(): "<< _results.size() << endl;
    for(int i = 0; i < _results.size(); i++) {
        
        r2.read(file, _results[i]);
        vectorstr recordedvalues ;
        for(int j = 0; j < fields.size(); j++) {
            recordedvalues.push_back(r2._record[_field_map.at(fields[j])]);//get records from original file
        }
        t.insert_into(recordedvalues); //add it into the new table, which then adds it to the new file
        // recordedvalues.clear();
    }
    file.close();
    return t;
}
vectorlong Table::select_recnos() {
    return _results;    //returns the vectorlong of record numbers
}

void Table::reindex() {
    /*fstream field_names_file;
    string line;
    _name = name;
    open_fileRW(field_names_file, (_name +to_string(serial_no) + "_fields.txt").c_str()); //create text file
    // open_fileRW(field_names_file, (_name + "_fields.txt").c_str());
    while(getline(field_names_file,line)) {
        if(line.size() > 0) {
            _field_vector.push_back(line);
        }
    }
    field_names_file.close(); //close text file
    for(int i = 0; i < _field_vector.size(); i++) {
        _field_map.insert(_field_vector[i], i);
    }
    for(int i = 0; i < _field_vector.size(); i++) {  //first for loop goes through each multimap
        _indices.push_back(new MMap<string, long> ()); //build lookup maps by creating a vector for indices
    }
    fstream file;
    FileRecord r2;
    //open the file for reading and writing.
    open_fileRW(file, (_name+to_string(serial_no)+".bin").c_str());
    // open_fileRW(file, _name.c_str());
    long recordno = 0;
    long bytes = r2.read(file, recordno); //empty envelop to be filled by the FileRecord object
    while (bytes>0){
        recordno++;
        bytes = r2.read(file, recordno);
        vectorstr insertion;
        insertion.push_back(to_string(r2._record[recordno][bytes]));
        cout << insertion << "insertion" << endl;
        for(int i = 0; i < _field_vector.size(); i++) {
            _indices[i]->insert(insertion[i], recordno);     
        }
        //one more thing after is to associate recordno with what is inside my vector string in a new table btree
        //insert into, do something to indices, do the same thing 
        //fileRecord class has a member variable that has the information I need to put into insertion
    }
    file.close();

    // open_fileRW(_f, _name.c_str());
    // string second_line;
    // while(getline(_f, second_line)) {
    //     if(second_line.size() > 0) {
    //         _record = FileRecord(second_line);
    //         for(int i = 0; i < _field_vector.size(); i++) {  //first for loop goes through each multimap
    //                 _indices[i].insert();
    //         } // need to insert stuff from binary_files to the index
    //     }
    // }
    */
   FileRecord file;
   fstream f;
   long byte = 0;
   last_record = -1;
    string bin_name = table_name + ".bin";
   open_fileRW(f, (bin_name).c_str());//opens the table bin file
   f.seekg(0, f.end); //gets it from 0 to file end
   byte = f.tellg(); //byte is current read position
   last_record = (byte/sizeof(file._record))-1; //then we get the record
   _results.clear();
   for(int i = 0; i <= last_record; i++) {
       file.read(f, i);
       _results.push_back(i);
       for(int j = 0; j < _field_vector.size(); j++) {
         _indices[j] -> get(file._record[j]).push_back(i); //put the record number into the indices from reading the file record number
        }
   }
   f.close();
   empty = false;
}

void Table::set_fields(const vectorstr fields) {
    _field_vector = fields; //used in SQL
}

vectorstr Table::get_fields() {
    return _field_vector; //used in SQL
}
// void Table::set_fields(const vectorstr fields) {
//     _field_vector = fields;
//     for(int i = 0; i < _field_vector.size(); i++) {  //first for loop goes through each multimap
//         _indices.push_back(new MMap<string, long> ()); //build lookup maps by creating a vector for indices
//     }
//     for(int i = 0; i < fields.size(); i++) {    //build map for fields and number each one is
//         _field_map.insert(fields[i], i);
//     }
// }

/*void Table::table_for_simple_select(Table &t, vectorlong records, FileRecord r2, fstream &ft) {
    int i = 0;
    long bytes = r2.read(ft, i); //empty envelop to be filled by the FileRecord object
    while (bytes>0) {
        if (find(records.begin(), records.end(), i) != records.end()) {
            vectorstr row;
            int n = 0;
            while(r2._record[n][0] != '\0') {
                row.push_back(r2._record[n]);
            }
            t.insert_into(row);
        }
        i++;
        bytes = r2.read(ft, i);
    }
}
*/