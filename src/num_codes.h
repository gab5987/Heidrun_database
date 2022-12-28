#ifndef _numcodes
#define _numcodes

// Database operations
#define CREATE_TABLE 0
#define INSERT_ROW 1
#define SELECT 2
#define UPDATE 3
#define DELETE 4
#define DROP_TABLE 5
#define DROP_DATABASE 6

// Everything`s fine codes
#define OK 0

// Error codes
#define ERROR_CANT_CREATE_DB -1
#define ERROR_DB_ALREADY_EXISTS -2
#define ERROR_TABLE_ALREADY_EXISTS -3
#define ERROR_TABLE_NOT_FOUND -4

// Error messages
#define MSG_CANT_CREATE_DB "Failed to create database"
#define MSG_DB_ALREADY_EXISTS "Database already exists"
#define MSG_TABLE_NOT_FOUND "Table not found"
#define MSG_TABLE_ALREADY_EXISTS "Table already exists"

#endif