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
    size_t count;
    SLoggerConfig* config;
} SLoggerManager;


extern SLoggerManager* _slogger_manager;


/******************
 * USER FUNCTIONS *
 ******************/

void slogger_initialize(); // initializes the slogger manager and the base configuration
void slogger_uninitialize(); // deallocates all the loggers and global variables

// SLogLevel* gives the ability to say every NULL value stayes unchanged (standards remain for this field)
void slogger_base_config(FILE* log, SLogLevel* level); // changes slogger base configuration

void slogger_get_logger(const char* name);
void slogger_logger_config(const char* name, FILE* log, SLogLevel* level);





/**********************
 * INTERNAL FUNCTIONS *
 **********************/




#endif // SLOGGER_H



