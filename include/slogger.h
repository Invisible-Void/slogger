#ifndef SLOGGER_H
#define SLOGGER_H

#include <assert.h>
#include <stdarg.h>
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
    FILE* stream;
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

SLogger* slogger_get_logger(const char* name);
void slogger_logger_config(SLogger* logger, FILE* log, SLogLevel* level);


void slogger_log(SLogger* logger, SLogLevel level, const char* message, ...);

// shortcuts for slogger_log
#define slogger_log_debug(LOGGER, MESSAGE, ...) slogger_log(LOGGER, DEBUG, MESSAGE, ##__VA_ARGS__)
#define slogger_log_info(LOGGER, MESSAGE, ...) slogger_log(LOGGER, INFO, MESSAGE, ##__VA_ARGS__)
#define slogger_log_warning(LOGGER, MESSAGE, ...) slogger_log(LOGGER, WARNING, MESSAGE, ##__VA_ARGS__)
#define slogger_log_error(LOGGER, MESSAGE, ...) slogger_log(LOGGER, ERROR, MESSAGE, ##__VA_ARGS__)



/**********************
 * INTERNAL FUNCTIONS *
 **********************/

SLogger* _slogger_manager_get_logger_index(size_t index);
SLogger* _slogger_manager_get_logger_name(char* name);

SLogger* _slogger_manager_add_logger(SLogger* logger); // adds logger to manager and adjusts capacity if needed
void _slogger_manager_del_logger(SLogger* logger); // removes logger from manager and adjusts capcity where appropriate


SLoggerConfig* _slogger_create_config(FILE* stream, SLogLevel level);
void _slogger_delete_config(SLoggerConfig* config);

SLogger* _slogger_create_logger(const char* name);
void _slogger_delete_logger(SLogger* logger);
SLogger* _slogger_get_logger(const char* name);

char* _slogger_level_to_string(SLogLevel level);

int _slogger_stream_used(FILE* stream);
void _slogger_close_stream(FILE* stream);


#endif // SLOGGER_H



