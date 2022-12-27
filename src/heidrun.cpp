#include "heidrun.hpp"

int8_t Heidrun_db::begin() {
    if(!SD.begin(4)) SD.begin();
    return 0;
}

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

int8_t Heidrun_db::createTable(char *dbName, char *tableName, char *columns) {
    String buff = "/" + String(dbName) + ".db" + "/" + String(tableName);
    String tableFile = buff + "/" + String(tableName) + ".tbl";

    if(!SD.exists(tableFile)) {
        SD.mkdir(buff);

        File tbl = SD.open(tableFile, FILE_WRITE);
        tbl.println(columns);

        tbl.close();
        return OK;
    }
    else return ERROR_TABLE_ALREADY_EXISTS;
}