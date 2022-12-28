#include "heidrun.hpp"


#define _OVERWRITE_INDEX(actualIndex)  idx.println(String(actualIndex));
#define __COMMOM_FILES__    String buff = "/" + String(dbName) + ".db" + "/" + String(tableName); \
                            String tableFile = buff + "/" + String(tableName) + ".tbl"; \
                            String indexFile = buff + "/" + String(tableName) + ".idx";


std::vector <String> split(String str, char separator) {
    std::vector <String> internal;
    String buff = "";
    for(auto i = 0; i < str.length(); i++) {
        if(str[i] != separator) buff += str[i];
        else if(str[i] == separator && buff != "") {
            internal.push_back(buff);
            buff = "";
        }
    }
    if(buff != "") internal.push_back(buff);

    return internal;
}

// Initialize the SD Card
// returns OK if everything went fine, ERROR_SD_CARD_NOT_FOUND if the SD Card was not found
int8_t Heidrun_db::begin() {
    if(!SD.begin(4)) SD.begin();
    return 0;
}

// Create a database
// dbName: name of the database
// returns OK if everything went fine, ERROR_DB_ALREADY_EXISTS if the database already exists
int8_t Heidrun_db::createDatabase(char *dbName) {
    String buff = "/" + String(dbName) + ".db";
    if(!SD.exists(buff)) {
        SD.mkdir(buff);

        File db = SD.open( buff + "/index.db" , FILE_WRITE);

        db.println("Heidrun Format 0");
        db.close();
        return OK;
    }
    else return ERROR_DB_ALREADY_EXISTS;
}

// Create a table in a database
// dbName: name of the database, tableName: name of the table, columns: columns of the table
// columns must be in the format: "column1, column2, column3, column4"
// returns OK if everything went fine, ERROR_TABLE_ALREADY_EXISTS if the table already exists
Heidrun_query createTable(char *dbName, char *tableName, char *columns) {
    __COMMOM_FILES__

    if(!SD.exists(tableFile)) {
        SD.mkdir(buff);

        File tbl = SD.open(tableFile, FILE_WRITE);
        tbl.println(columns + ' ');
        tbl.close();

        File idx = SD.open(indexFile, FILE_WRITE);
        _OVERWRITE_INDEX(0);
        idx.close();

        std::vector<String> result = {"OK"};
        return Heidrun_query(result, OK);
    }
    else {
        std::vector<String> result = {MSG_TABLE_ALREADY_EXISTS};
        return Heidrun_query(result, ERROR_TABLE_ALREADY_EXISTS);
    }
}

// Insert a row in a table
// dbName: name of the database, tableName: name of the table, values: values of the row
// returns OK if everything went fine, ERROR_TABLE_NOT_FOUND if the table was not found
Heidrun_query insertRow(char *dbName, char *tableName, char *values) {
    __COMMOM_FILES__

    if(!SD.exists(tableFile)) {
        std::vector<String> result = {MSG_TABLE_NOT_FOUND};
        return Heidrun_query(result ,ERROR_TABLE_NOT_FOUND);
    }

    File idx = SD.open(indexFile, FILE_READ);
    uint32_t actualIndex = idx.parseInt();
    idx.close();
    Serial.println(actualIndex);

    File row = SD.open(buff + "/" + String(actualIndex + 1) + ".row", FILE_WRITE);
    row.println(values + ' ');
    row.close();

    idx = SD.open(indexFile, FILE_WRITE);
    _OVERWRITE_INDEX(actualIndex + 1);
    idx.close();

    std::vector<String> result = { "OK" };
    return Heidrun_query(result, OK);
}

// Select a row in a table
// dbName: name of the database, tableName: name of the table, values: values of the row
// returns OK if everything went fine, ERROR_TABLE_NOT_FOUND if the table was not found
Heidrun_query selectRow(char *dbName, char *tableName, char *values) {
    __COMMOM_FILES__

    if(!SD.exists(tableFile)) {
        std::vector<String> result = {MSG_TABLE_NOT_FOUND};
        return Heidrun_query(result, ERROR_TABLE_NOT_FOUND);
    }

    std::vector<String> tokens = split(String(values), ' ');

    File row = SD.open(buff + "/" + tokens[tokens.size() - 1] + ".row", FILE_READ);
    std::vector<String> rowTokens = split(row.readString(), ' ');
    row.close();

    File tbl = SD.open(tableFile, FILE_READ);
    std::vector<String> tableTokens = split(tbl.readString(), ' ');
    tbl.close();

    std::vector<String> result;
    for(auto i = 0; i < tokens.size() - 1; i++) {
        for(auto j = 0 ; j < tableTokens.size(); j++) {
            if(tokens[i] == tableTokens[j]) {
                result.push_back(rowTokens[j]);
            }
        }
    }

    return Heidrun_query(result, OK);
}

#define ERROR_INVALID_OPERATION -1

// Run a SQL command
// dbName: name of the database, dbTable: name of the table, op: operation to be done, items: items to be used
Heidrun_query Heidrun_db::run_sql(char *dbName, char *dbTable, uint8_t op, char* items) {    
    switch(op) {
        case CREATE_TABLE:
            return createTable(dbName, dbTable, items);
        case INSERT_ROW:
            return insertRow(dbName, dbTable, items);
        case SELECT:
            return selectRow(dbName, dbTable, items);
        default: {
            std::vector<String> result = {"falha"};
            return Heidrun_query(result, ERROR_INVALID_OPERATION);
        }
    }
}