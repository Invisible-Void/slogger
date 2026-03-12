#ifndef SLOGGER_H
#define SLOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum SLogLevel {
    DEBUG = 0,
    INFO,
    WARNING,
    ERROR
} SLogLevel;

typedef struct SLoggerConfig {
    char* filename;
    SLogLevel level;
} SLoggerConfig;

typedef struct SLogger {
    char* name;
    SLoggerConfig* config;
} SLogger;


typedef struct SLoggerManager {
    SLogger** loggers;
    size_t capacity;
    size_t size;
    SLoggerConfig* config;
} SLoggerManager;


extern SLoggerManager* _slogger_manager;


/******************
 * USER FUNCTIONS *
 ******************/

int slogger_initialize(); // initializes the slogger manager and the base configuration
void slogger_uninitialize(); // deallocates all the loggers and global variables

// SLogLevel* gives the ability to say every NULL value stayes unchanged (standards remain for this field)
void slogger_base_config(FILE* log, SLogLevel* level); // changes slogger base configuration

void slogger_get_logger(const char* name);
void slogger_logger_config(const char* name, FILE* log, SLogLevel* level);





/**********************
 * INTERNAL FUNCTIONS *
 **********************/

SLogger* slogger_manager_get_logger_index(size_t index);
SLogger* slogger_manager_get_logger_name(char* name);

SLogger* slogger_manager_add_logger(SLogger* logger); // adds logger to manager and adjusts capacity if needed
SLogger* slogger_manager_del_logger(SLogger* logger); // removes logger from manager and adjusts capcity where appropriate



#endif // SLOGGER_H



