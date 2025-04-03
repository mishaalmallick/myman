// C0F4DFE8B340D81183C208F70F9D2D797908754D
#include "Field.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include "getopt.h"


using namespace std; 

class Table {
    public:
    vector<vector<Field>> total_Table;
    unordered_map<string, size_t> column_numbers;
    vector<string> col_names;
    vector<string> col_types; 
    unordered_map<Field, vector<size_t>> hash;
    map<Field, vector<size_t>, less<Field>> bst;
    string bstcol = " ";
    string hashcol = " "; 
    Table() {};
};

bool quietMode = false;
unordered_map<string, Table> database; //total Tables 

void create(){
    string table_name;
    size_t N;
    string col_name; 
    string col_type; 


    cin >> table_name; // take in table name 
    auto it = database.find(table_name); // see if table exists 
    if(it == database.end()){ // if table doesn't exist
        cin >> N; // total amount columns
        Table new_table; //create new table
        database.emplace(table_name, std::move(new_table)); // add the table!
        database[table_name].total_Table.reserve(N);
        database[table_name].col_types.reserve(N);
        database[table_name].col_names.reserve(N);
        database[table_name].column_numbers.reserve(N);
        database[table_name].hash.reserve(N);
        for(size_t i = 0; i < N; i++){
            cin >> col_type; 
            database[table_name].col_types.push_back(col_type); // each type, in order, for column types

        }
        for(size_t i = 0; i < N; i++){
            cin >> col_name; // column numbers and there indices
            database[table_name].column_numbers[col_name] = i; // indices 
            database[table_name].col_names.push_back(col_name); // col names 
        }
        cout << "New table " << table_name << " with column(s) ";
        for(size_t i = 0; i < N; i++){
            cout << database[table_name].col_names[i] << " "; // list columns
        }
        cout << "created" << "\n";

    } else {
        cout << "Error during CREATE: Cannot create already existing table " <<  table_name << "\n";
        return;
    }
}

void quit(){
    cout << "Thanks for being silly!" << "\n";
    exit(0); // end program 
}

void comment(){
    string comment;
    cin.ignore();
    getline(cin, comment); // if comment take it in 
}

void removeTable(const string &TableName){ 
    auto it = database.find(TableName);
    if(it != database.end()){
        database.erase(TableName); // erase table name if found 
        cout << "Table " << TableName << " removed" << "\n";
    } else {
        cout << "Error during REMOVE: " << TableName << " does not name a table in the database " << "\n";
        return;
    }
}

void insert(){
    string table_name; 
    size_t N; 
    string ROWS;

    cin >> table_name; // get table name
    cin >> N; // get number of rows 
    cin >> ROWS; 
    

    auto it = database.find(table_name);
    if(it != database.end()){ // if table exists 
        size_t K = database[table_name].total_Table.size(); 
         // current amount of rows; 
        for(size_t i = 0; i < N; i++){ // until the amount of rows 
            vector<Field> total_added; // row 
            total_added.reserve(N);
            for(size_t j = 0; j < database[table_name].col_names.size(); j++){ // until amount of columns in the table (guaranteed)
                if(database[table_name].col_types[j] == "string"){ // if string 
                    string value;
                    cin >> value; 
                    Field new_val(value);
                    total_added.push_back(new_val); // push back val 
                }
                if(database[table_name].col_types[j] == "double"){
                    double value;
                    cin >> value; 
                    Field new_val(value);
                    total_added.push_back(new_val);
                }
                if(database[table_name].col_types[j] == "int"){
                    int value;
                    cin >> value; 
                    Field new_val(value);
                    total_added.push_back(new_val);
                }
                if(database[table_name].col_types[j] == "bool"){
                    bool value;
                    cin >> value; 
                    Field new_val(value);
                    total_added.push_back(new_val);
                }
            }
            database[table_name].total_Table.push_back(total_added);
           
            
        }
        cout << "Added " << N << " rows to " << table_name << " from position " <<  K << " to " << K + N - 1 << "\n";
  
    } else {
        cout << "Error during INSERT: " << table_name << " does not name a table in the database " << "\n";
        return;
    }
}

void print(){
    string table_name;
    size_t N;
    string col_name;
    vector<string> column_names_to_keep_track;
    vector<size_t> column_numbers_to_print;
    vector<vector<Field>> coutt;
    
    
    

    string WHERE;
    string spec_colname;
    string operation;

    double val;
    string val1;
    bool val2;
    int val3;
    string type;
    
    cin >> table_name; // get in table name 
    cin >> N; // number of columns 
    auto it = database.find(table_name);
    bool bst = false;
    bool hash = false;
    size_t total = 0; 

    



    if(it != database.end()){ // if the table exists 
        coutt.resize(database[table_name].total_Table.size());
        for(size_t i = 0; i < N; i++){
            cin >> col_name; // take in the columns that need to be printed, put them into a vector 
            if(database[table_name].column_numbers.find(col_name) == database[table_name].column_numbers.end()){
                cout << "Error during PRINT: " << col_name << "does not name a column in " << table_name << "\n";
                return; 
            }
            column_names_to_keep_track.push_back(col_name);
        }
        cin >> WHERE; 
        
        if(WHERE != "ALL"){
            cin >> spec_colname; // col name where you need to consider the value 
            cin >> operation; // operation 
            
        

            if(spec_colname == database[table_name].bstcol){
                bst = true; 
                
            }
            if(database[table_name].column_numbers.find(spec_colname) == database[table_name].column_numbers.end()){
                cout << "Error during PRINT: " << spec_colname << " does not name a column in " << table_name << "\n";
                return; 
            }
            if(database[table_name].column_numbers.find(spec_colname) == database[table_name].column_numbers.end()) {
                cout << "Error: Column " << spec_colname << " does not exist in " << table_name << "\n";
                return;
            }
            size_t col_num_spec = database[table_name].column_numbers[spec_colname]; // column number of where you need to consider the value 
            if(database[table_name].col_types[col_num_spec] == "string"){// is the column a string, double, or value?
                cin >> val1;
                type = "string";
            }
            if(database[table_name].col_types[col_num_spec] == "double"){
                cin >> val;
                type = "double";
                
            }
            if(database[table_name].col_types[col_num_spec] == "bool"){
                cin >> val2;
                type = "bool";
          
            }
            if(database[table_name].col_types[col_num_spec] == "int"){
                cin >> val3;
                type = "int";
            }

            for(size_t i = 0; i < N; i++){
                string name = column_names_to_keep_track[i]; 
                size_t num = database[table_name].column_numbers[name];
                column_numbers_to_print.push_back(num); // keep track of the column number to print 
            }
               


            if(type == "bool" && !bst && !hash){ // if its a bool 
                for(size_t i = 0; i < database[table_name].total_Table.size(); i++){
                   // for each row in the table 
                    if(operation == ">"){
                        if(database[table_name].total_Table[i][col_num_spec] > val2){
                             // if it fits the value and operation
                            for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                size_t column_number = column_numbers_to_print[j]; // push back all the columns that need to be printed 
                                coutt[i].push_back(database[table_name].total_Table[i][column_number]);
                            }
                        }
                    }
                    if(operation == "="){
                        if(database[table_name].total_Table[i][col_num_spec] == val2){
                           
                           
                            for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                size_t column_number = column_numbers_to_print[j];
                                coutt[i].push_back(database[table_name].total_Table[i][column_number]);
                                
                            }
                        }

                    }
                    if(operation == "<"){
                        if(database[table_name].total_Table[i][col_num_spec] < val2){
                            
                            for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                size_t column_number = column_numbers_to_print[j];
                                coutt[i].push_back(database[table_name].total_Table[i][column_number]);
                            }
                        }

                    }
                }
            }

            if(type == "int" && !bst && !hash){ // if its an int  
                for(size_t i = 0; i < database[table_name].total_Table.size(); i++){ // for each row in the table 
                    if(operation == ">"){
                        if(database[table_name].total_Table[i][col_num_spec] > val3){
                            // if it fits the value and operation
                            for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                size_t column_number = column_numbers_to_print[j]; // push back all the columns that need to be printed 
                                coutt[i].push_back(database[table_name].total_Table[i][column_number]);
                            }
                        }
                    }
                    if(operation == "="){
                        if(database[table_name].total_Table[i][col_num_spec] == val3){
                        
                            for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                size_t column_number = column_numbers_to_print[j];
                                coutt[i].push_back(database[table_name].total_Table[i][column_number]);
                            }
                        }

                    }
                    if(operation == "<"){
                        if(database[table_name].total_Table[i][col_num_spec] < val3){
                          
                            for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                size_t column_number = column_numbers_to_print[j];
                                coutt[i].push_back(database[table_name].total_Table[i][column_number]);
                            }
                        }

                    }
                }
            }

            if(type == "double" && !bst && !hash){ // if its an int  
                for(size_t i = 0; i < database[table_name].total_Table.size(); i++){ // for each row in the table 
                    if(operation == ">"){
                        if(database[table_name].total_Table[i][col_num_spec] > val){ 
                        // if it fits the value and operation
                            for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                size_t column_number = column_numbers_to_print[j]; // push back all the columns that need to be printed 
                                coutt[i].push_back(database[table_name].total_Table[i][column_number]);
                            }
                        }
                    }
                    if(operation == "="){
                        if(database[table_name].total_Table[i][col_num_spec] == val){
                          
                            for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                size_t column_number = column_numbers_to_print[j];
                                coutt[i].push_back(database[table_name].total_Table[i][column_number]);
                            }
                        }

                    }
                    if(operation == "<"){
                        if(database[table_name].total_Table[i][col_num_spec] < val){
                            
                            for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                size_t column_number = column_numbers_to_print[j];
                                coutt[i].push_back(database[table_name].total_Table[i][column_number]);
                            }
                        }

                    }
                }
            }

            if(type == "string"&& !bst && !hash){ // if its an int  
                for(size_t i = 0; i < database[table_name].total_Table.size(); i++){ // for each row in the table 
                    if(operation == ">"){
                
                        if(database[table_name].total_Table[i][col_num_spec] > val1){ // if it fits the value and operation
                            for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                size_t column_number = column_numbers_to_print[j]; // push back all the columns that need to be printed 
                                coutt[i].push_back(database[table_name].total_Table[i][column_number]);
                            }
                        }
                    }
                    if(operation == "="){
                       
                        if(database[table_name].total_Table[i][col_num_spec] == val1){
                            for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                               
                                size_t column_number = column_numbers_to_print[j];
                                
                                coutt[i].push_back(database[table_name].total_Table[i][column_number]);
                               
                            }
                        }

                    }
                    if(operation == "<"){
                  
                        if(database[table_name].total_Table[i][col_num_spec] < val1){
                            for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                size_t column_number = column_numbers_to_print[j];
                                coutt[i].push_back(database[table_name].total_Table[i][column_number]);
                            }
                        }

                    }
                }
            }

            if(bst){
                if(type == "double"){
                    auto it = database[table_name].bst.begin();
                    
                    if(operation == ">"){
                        for(size_t i = 0; i < database[table_name].total_Table.size(); i++){
                            while(it != database[table_name].bst.end()){   
                            if(it->first > val){
                                for(size_t k = 0; k < it->second.size(); k++){
                                    for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                        size_t column_number = column_numbers_to_print[j];
                                        coutt[i].push_back(database[table_name].total_Table[it->second[k]][column_number]);
                                        
                                    }
                                }
                                i++;
                            }
                            ++it;
                        } 
                    }
                    }
                    if(operation == "="){
                        for(size_t i = 0; i < database[table_name].total_Table.size(); i++){
                            while(it != database[table_name].bst.end()){   
                            if(it->first > val){
                                for(size_t k = 0; k < it->second.size(); k++){
                                    for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                        size_t column_number = column_numbers_to_print[j];
                                        coutt[i].push_back(database[table_name].total_Table[it->second[k]][column_number]);
                                        
                                    }
                                }
                                i++;
                            }
                            ++it;
                        } 
                    }
                    }
                    if(operation == "<"){
                        for(size_t i = 0; i < database[table_name].total_Table.size(); i++){
                            while(it != database[table_name].bst.end()){   
                            if(it->first > val){
                                for(size_t k = 0; k < it->second.size(); k++){
                                    for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                        size_t column_number = column_numbers_to_print[j];
                                        coutt[i].push_back(database[table_name].total_Table[it->second[k]][column_number]);
                                        
                                    }
                                }
                                i++;
                            }
                            ++it;
                        } 
                    }
                    }
                }
                if(type == "string"){
                    auto it = database[table_name].bst.begin();
                    if(operation == ">"){
                        for(size_t i = 0; i < database[table_name].total_Table.size(); i++){
                            while(it != database[table_name].bst.end()){   
                            if(it->first > val1){
                                for(size_t k = 0; k < it->second.size(); k++){
                                    for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                        size_t column_number = column_numbers_to_print[j];
                                        coutt[i].push_back(database[table_name].total_Table[it->second[k]][column_number]);
                                        
                                    }
                                }
                                i++;
                            }
                            ++it;
                        } 
                    }
                    }
                    if(operation == "="){
                        for(size_t i = 0; i < database[table_name].total_Table.size(); i++){
                            while(it != database[table_name].bst.end()){   
                            if(it->first > val1){
                                for(size_t k = 0; k < it->second.size(); k++){
                                    for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                        size_t column_number = column_numbers_to_print[j];
                                        coutt[i].push_back(database[table_name].total_Table[it->second[k]][column_number]);
                                        
                                    }
                                }
                                i++;
                            }
                            ++it;
                        } 
                    }
                    }
                    if(operation == "<"){
                        for(size_t i = 0; i < database[table_name].total_Table.size(); i++){
                            while(it != database[table_name].bst.end()){   
                            if(it->first > val1){
                                for(size_t k = 0; k < it->second.size(); k++){
                                    for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                        size_t column_number = column_numbers_to_print[j];
                                        coutt[i].push_back(database[table_name].total_Table[it->second[k]][column_number]);
                                        
                                    }
                                }
                                i++;
                            }
                            ++it;
                        } 
                    }
                    }
                }
                if(type == "bool"){
                    auto it = database[table_name].bst.begin();
                    if(operation == ">"){
                        for(size_t i = 0; i < database[table_name].total_Table.size(); i++){
                            while(it != database[table_name].bst.end()){   
                            if(it->first > val3){
                                for(size_t k = 0; k < it->second.size(); k++){
                                    for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                        size_t column_number = column_numbers_to_print[j];
                                        coutt[i].push_back(database[table_name].total_Table[it->second[k]][column_number]);
                                        
                                    }
                                }
                                i++;
                            }
                            ++it;
                        } 
                    }
                    }
                    if(operation == "="){
                        for(size_t i = 0; i < database[table_name].total_Table.size(); i++){
                            while(it != database[table_name].bst.end()){   
                            if(it->first == val2){
                                for(size_t k = 0; k < it->second.size(); k++){
                                    for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                        size_t column_number = column_numbers_to_print[j];
                                        coutt[i].push_back(database[table_name].total_Table[it->second[k]][column_number]);
                                        
                                    }
                                }
                                i++;
                            }
                            ++it;
                        } 
                    }
                    }
                    
                    if(operation == "<"){
                        for(size_t i = 0; i < database[table_name].total_Table.size(); i++){
                            while(it != database[table_name].bst.end()){   
                            if(it->first < val2){
                                for(size_t k = 0; k < it->second.size(); k++){
                                    for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                        size_t column_number = column_numbers_to_print[j];
                                        coutt[i].push_back(database[table_name].total_Table[it->second[k]][column_number]);
                                        
                                    }
                                }
                                i++;
                            }
                            ++it;
                        } 
                    }
                    }
                }
                if(type == "int"){
                    auto it = database[table_name].bst.begin();
                   
                    if(operation == ">"){
                            for(size_t i = 0; i < database[table_name].total_Table.size(); i++){
                                while(it != database[table_name].bst.end()){   
                                if(it->first > val3){
                                    for(size_t k = 0; k < it->second.size(); k++){
                                        for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                            size_t column_number = column_numbers_to_print[j];
                                            coutt[i].push_back(database[table_name].total_Table[it->second[k]][column_number]);
                                            
                                        }
                                    }
                                    i++;
                                }
                                ++it;
                            } 
                        }
                    }
                 
                    if(operation == "="){
                        for(size_t i = 0; i < database[table_name].total_Table.size(); i++){
                            while(it != database[table_name].bst.end()){   
                            if(it->first == val3){
                                for(size_t k = 0; k < it->second.size(); k++){
                                    for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                        size_t column_number = column_numbers_to_print[j];
                                        coutt[i].push_back(database[table_name].total_Table[it->second[k]][column_number]);
                                        
                                    }
                                }
                                i++;
                            }
                            ++it;
                        } 
                    }
                    }
                    
                    if(operation == "<"){
                        for(size_t i = 0; i < database[table_name].total_Table.size(); i++){
                            while(it != database[table_name].bst.end()){   
                            if(it->first < val3){
                                for(size_t k = 0; k < it->second.size(); k++){
                                    for(size_t j = 0; j < column_numbers_to_print.size(); j++){
                                        size_t column_number = column_numbers_to_print[j];
                                        coutt[i].push_back(database[table_name].total_Table[it->second[k]][column_number]);
                                        
                                    }
                                }
                                i++;
                            }
                            ++it;
                        } 
                    }
                    }
                }
            }


            
            for(size_t i = 0; i < N; i++){
                if(!quietMode){
                    cout << column_names_to_keep_track[i] << " ";
                }
                
            }
            if(!quietMode){
                cout << " \n";
            }
           
            bool printed = false;
          
            for(size_t i = 0; i < coutt.size(); i++){
                if (coutt[i].empty()) continue; 
                printed = false;
                for(size_t j = 0; j < coutt[i].size(); j++){
                    if(!quietMode){
                        cout << coutt[i][j] << " ";
                    }
                   
                    printed = true;
                }
                if(printed){
                    total++;
                    if(!quietMode){
                        cout << "\n";
                    }
                    
                }
                
            }
        
            
        } else {
               
            
            for(size_t i = 0; i < N; i++){
                string name = column_names_to_keep_track[i]; 
                size_t num = database[table_name].column_numbers[name];
                column_numbers_to_print.push_back(num); // keep track of the column number to print 
            }
            for(size_t i = 0; i < column_names_to_keep_track.size(); i++){
                if(!quietMode){
                    
                        cout << column_names_to_keep_track[i] << " ";
                    
                    
                }
                
            }
            if(!quietMode){
                cout << "\n";
            }
            
            for(size_t i = 0; i < database[table_name].total_Table.size(); i++){
                total++;
                for(size_t j = 0; j < N; j++){
                    if(!quietMode){
                        cout << database[table_name].total_Table[i][column_numbers_to_print[j]] << " ";
                    }
                    
                }
                if(!quietMode){
                    cout << "\n";
                }
                
            }
        
        }
        cout << "Printed " << total << " matching rows" << " from " << table_name << "\n";
} else {
    cout << "Error during PRINT: " << table_name << " does not name a table in the database " << "\n";
}
}

void delete_func(){
    string tablename;
    string WHERE;
    string col_name;
    string operation;
    int val;
    bool val1;
    double val2;
    string val3;
    string type; 
    int total_deleted = 0; 
    cin >> tablename;
    cin >> WHERE;
    cin >> col_name;
    cin >> operation;
    auto it = database.find(tablename);
    
  

    if(it == database.end()){
        cout << "Error during DELETE: Cannot create already existing table " << tablename << "\n";
        return; 
    }
    auto it2 = database[tablename].column_numbers.find(col_name);
    if(it2 == database[tablename].column_numbers.end()){
        cout << "Error during DELETE: "<< col_name << " does not name a column in " << tablename << "\n";
        return;
    }
    size_t spec_col = database[tablename].column_numbers[col_name]; // the column with operation 
    


    if(database[tablename].col_types[spec_col] == "string"){ // input of string 
        type = "string"; 
        cin >> val3;
    }
    if(database[tablename].col_types[spec_col] == "bool"){
        type = "bool";
        cin >> val1;
    }
    if(database[tablename].col_types[spec_col] == "double"){
        type = "double";
        cin >> val2;
    }
    if(database[tablename].col_types[spec_col] == "int"){
        type = "int";
        cin >> val;
    }

    if(type == "string"){
        if(operation == ">"){
            for(size_t i = database[tablename].total_Table.size(); i-- > 0; ){ 
                if(database[tablename].total_Table[i][spec_col] > val3){
                    database[tablename].total_Table.erase(next(database[tablename].total_Table.begin(), static_cast<long>(i)));
                    total_deleted++;
                }
            }
        }
        if(operation == "="){
            for(size_t i = database[tablename].total_Table.size(); i-- > 0; ){
                if(database[tablename].total_Table[i][spec_col] == val3){
                    database[tablename].total_Table.erase(next(database[tablename].total_Table.begin(), static_cast<long>(i)));
                    total_deleted++;
                }
            }
        }
        if(operation == "<"){
            for(size_t i = database[tablename].total_Table.size(); i-- > 0; ){
                if(database[tablename].total_Table[i][spec_col] < val3){
                    database[tablename].total_Table.erase(next(database[tablename].total_Table.begin(), static_cast<long>(i)));
                    total_deleted++;
                }
            }
        }
    }
    if(type == "int"){
        if(operation == ">"){
            for(size_t i = database[tablename].total_Table.size(); i-- > 0; ){
                if(database[tablename].total_Table[i][spec_col] > val){
                    database[tablename].total_Table.erase(next(database[tablename].total_Table.begin(), static_cast<long>(i)));
                    total_deleted++;
                }
            }
        }
        if(operation == "="){
            for(size_t i = database[tablename].total_Table.size(); i-- > 0; ){
                if(database[tablename].total_Table[i][spec_col] == val){
                    database[tablename].total_Table.erase(next(database[tablename].total_Table.begin(), static_cast<long>(i)));
                    total_deleted++;
                }
            }
        }
        if(operation == "<"){
            for(size_t i = database[tablename].total_Table.size(); i-- > 0; ){
                if(database[tablename].total_Table[i][spec_col] < val){
                    database[tablename].total_Table.erase(next(database[tablename].total_Table.begin(), static_cast<long>(i)));
                    total_deleted++;
                }
            }
        }
    }
    if(type == "double"){
        if(operation == ">"){
            for(size_t i = database[tablename].total_Table.size(); i-- > 0; ){
                if(database[tablename].total_Table[i][spec_col] > val2){
                    database[tablename].total_Table.erase(next(database[tablename].total_Table.begin(), static_cast<long>(i)));
                    total_deleted++;
                }
            }
        }
        if(operation == "="){
            for(size_t i = database[tablename].total_Table.size(); i-- > 0; ){
                if(database[tablename].total_Table[i][spec_col] == val2){
                    database[tablename].total_Table.erase(next(database[tablename].total_Table.begin(), static_cast<long>(i)));
                    total_deleted++;
                }
            }
        }
        if(operation == "<"){
            for(size_t i = database[tablename].total_Table.size(); i-- > 0; ){
                if(database[tablename].total_Table[i][spec_col] < val2){
                    database[tablename].total_Table.erase(next(database[tablename].total_Table.begin(), static_cast<long>(i)));
                    total_deleted++;
                }
            }
        }
    }
    if(type == "bool"){
        if(operation == ">"){
            for(size_t i = database[tablename].total_Table.size(); i-- > 0; ){
                
                if(database[tablename].total_Table[i][spec_col] > val1){
                    database[tablename].total_Table.erase(next(database[tablename].total_Table.begin(), static_cast<long>(i)));
                    total_deleted++;
                }
            }
        }
        if(operation == "="){
            for(size_t i = database[tablename].total_Table.size(); i-- > 0; ){
                if(database[tablename].total_Table[i][spec_col] == val1){
                    
                    database[tablename].total_Table.erase(next(database[tablename].total_Table.begin(), static_cast<long>(i)));
                    total_deleted++;
                }
            }
        }
        if(operation == "<"){
            for(size_t i = database[tablename].total_Table.size(); i-- > 0; ){
                if(database[tablename].total_Table[i][spec_col] < val1){
                    database[tablename].total_Table.erase(next(database[tablename].total_Table.begin(), static_cast<long>(i)));
                    total_deleted++;
                }
            }
        }

        
    }
   
    if(!database[tablename].bst.empty()){
        
        database[tablename].bst.clear();
        for(size_t i = 0; i < database[tablename].total_Table.size(); i++){
            database[tablename].bst[database[tablename].total_Table[i][spec_col]].push_back(i);
            database[tablename].bstcol = col_name;
        }
    }

    if(!database[tablename].hash.empty()){
        database[tablename].hash.clear();
        for(size_t i = 0; i < database[tablename].total_Table.size(); i++){
            database[tablename].hash[database[tablename].total_Table[i][spec_col]].push_back(i);
            database[tablename].hashcol = col_name;
        }
    }
    cout << "Deleted " << total_deleted << " rows from " << tablename << "\n";



    

}

void join() {
    string tablename1, tablename2, CAPS, colname1, colname2;
    size_t N;
    cin >> tablename1 >> CAPS >> tablename2 >> CAPS;

    auto found1 = database.find(tablename1);
    auto found2 = database.find(tablename2);
    if (found1 == database.end() || found2 == database.end()) {
        return;
    }

    cin >> colname1 >> CAPS >> colname2 >> CAPS >> CAPS >> N;

    vector<string> colnamesh;
    vector<int> table_colnumstoprint;
    vector<size_t> col_nums_keep_track;

    for (size_t i = 0; i < N; i++) {
        string colnamestoprint;
        int table_colnums;
        cin >> colnamestoprint >> table_colnums;
        colnamesh.push_back(colnamestoprint);
        table_colnumstoprint.push_back(table_colnums);

        if (table_colnums == 1) {
            auto finding = database[tablename1].column_numbers.find(colnamestoprint);
            if (finding == database[tablename1].column_numbers.end()) return;
            col_nums_keep_track.push_back(finding->second);
        }
        if (table_colnums == 2) {
            auto finding = database[tablename2].column_numbers.find(colnamestoprint);
            if (finding == database[tablename2].column_numbers.end()) return;
            col_nums_keep_track.push_back(finding->second);
        }
    }

   
    size_t spec_colname1 = database[tablename1].column_numbers[colname1];
    size_t spec_colname2 = database[tablename2].column_numbers[colname2];

    
    map<Field, vector<size_t>> table2;
    for (size_t i = 0; i < database[tablename2].total_Table.size(); i++) {
        table2[database[tablename2].total_Table[i][spec_colname2]].push_back(i);
    }


    vector<pair<size_t, size_t>> matched_rows;
    

    
    for (size_t i = 0; i < database[tablename1].total_Table.size(); i++) {
        
        auto found = table2.find(database[tablename1].total_Table[i][spec_colname1]); // vector of rows 
        if (found != table2.end()) {
            for (size_t row2 : found->second) {
                matched_rows.push_back({i, row2}); // 
                
            }
        }
    }



    for (const auto& col : colnamesh) {
        cout << col << " ";
    }
    cout << "\n";


        int total = 0; 
        for (const auto& [row1, row2] : matched_rows) {
            for (size_t j = 0; j < colnamesh.size(); j++) {
                if (table_colnumstoprint[j] == 1) {
                    if(!quietMode){
                        cout << database[tablename1].total_Table[row1][col_nums_keep_track[j]] << " ";
                    }
                    
                    total++;
                } else {
                    if(!quietMode){
                        cout << database[tablename2].total_Table[row2][col_nums_keep_track[j]] << " ";
                    }
                  
                    total++;
                }
            }
            if(!quietMode){
                cout << "\n";
            }
           
        }

        cout << "Printed " << total << " rows from joining " << tablename1 << " to " << tablename2 << "\n";
     

}


void generate(){
    string tablename;
    string indextype;
    string CAPS;
    string colname;

    cin >> tablename;
   
    cin >> indextype;
 
    cin >> CAPS;
    cin >> CAPS;
    cin >> colname; 
 

    auto it = database.find(tablename);
    if(it == database.end()){
        cout << "Error during GENERATE: Cannot create already existing table " << tablename << "\n";
        return;
    }

    auto col_it = database[tablename].column_numbers.find(colname);
    if (col_it == database[tablename].column_numbers.end()) {
        cout << "Error: " << colname << " is not a column in " << tablename << "\n";
        return;
    }

    
    size_t col_index = database[tablename].column_numbers[colname];


    if(!database[tablename].hash.empty()){
        database[tablename].hash.clear();
  
        
    }

    if(!database[tablename].bst.empty()){
        database[tablename].bst.clear();
    }
    if(colname == database[tablename].hashcol){
        database[tablename].hash.clear();
        database[tablename].hashcol = " ";
    }

    if(colname == database[tablename].bstcol){
        database[tablename].bst.clear();
        database[tablename].bstcol = " ";
    }


    
    if(indextype == "hash"){
        for(size_t i = 0; i < database[tablename].total_Table.size(); i++){
        
        
            database[tablename].hash[database[tablename].total_Table[i][col_index]].push_back(i);
            database[tablename].hashcol = colname;
        }
  

        cout << "Generated " << indextype << " index for table " << tablename << " on column " << colname << ". with " << database[tablename].hash.size() << " distinct keys " << "\n";
        
    }

    if(indextype == "bst"){
        for(size_t i = 0; i < database[tablename].total_Table.size(); i++){
            database[tablename].bst[database[tablename].total_Table[i][col_index]].push_back(i);
            database[tablename].bstcol = colname;
        }
        cout << "Generated " << indextype << " for table " << tablename << " on column " << colname << ", with " << database[tablename].bst.size() << " distinct keys " << "\n";
    }

    

}


void get_opt(int argc, char**argv) {
    int optindex = 0;
    int option = 0;
    
    
    opterr = false;
    
    struct option comOpts[] = { {"quiet", no_argument, nullptr, 'q'},
        {"help", no_argument, nullptr, 'h'}};
    
    while ((option = getopt_long(argc, argv, "qh", comOpts, &optindex)) != -1) {
        switch (option) {
                case 'h':
                    cout << "Help!\n";
                    break;
                case 'q':
                    quietMode = true;
                break;
        }
    }
}


int main(int argc, char** argv) {
        std::ios_base::sync_with_stdio(false);  
        get_opt(argc, argv);
     
        
        string command;
        
        do {
            string temp;
  
            cout << "% ";
            cin >> command;
            
            
            if (command.at(0) == '#') {
                getline(cin, temp);
            }
            
            else if (command == "CREATE") {
                create();
            }
            

            else if (command == "INSERT") {
         
                cin >> temp;
                insert();
            }
            
            else if (command == "REMOVE") {
                cin >> temp;
                removeTable(temp);
            }
            else if (command == "GENERATE") {
                cin >> temp; 
                generate();
                
            }
            else if (command == "PRINT") {
                cin >> temp;
                print();
            }
            
            else if (command == "DELETE") {
        
                cin >> temp;
                delete_func();
            }
  
            else if (command == "JOIN") {
                join();
            }
         } while (command != "QUIT");
    
        if (command == "QUIT") {
            quit();
        }
    
        
        return 0;
    }
    

