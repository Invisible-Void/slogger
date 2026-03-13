#include <slogger.h>

SLoggerManager* _slogger_manager;


/******************
 * USER FUNCTIONS *
 ******************/

// initializes the slogger manager and the base configuration
// returns 1 on SUCCESS and 0 on FAILURE (instead of true and false)
int slogger_initialize() {
    _slogger_manager = (SLoggerManager*) malloc(sizeof(SLoggerManager));
    if (_slogger_manager == NULL) {
        return 0;
    }

    _slogger_manager->size = 0;
    _slogger_manager->capacity = 2;
    _slogger_manager->loggers = (SLogger**) malloc(sizeof(SLogger*) * _slogger_manager->capacity);
    if (_slogger_manager->loggers == NULL) {
        free(_slogger_manager);
        return 0;
    }

    _slogger_manager->config = _slogger_create_config(stderr, WARNING);
    if (_slogger_manager->config == NULL) {
        free(_slogger_manager->loggers);
        free(_slogger_manager);
        return 0;
    }
    //_slogger_manager->config->filename = (char*) malloc(sizeof())

    return 1;
}

// deallocates all the loggers and global variables
// returns 1 on SUCCESS and 0 on FAILURE (instead of true and false)
void slogger_uninitialize() {
    if (_slogger_manager == NULL) {
        return;
    }

    // free the base configuration
    _slogger_delete_config(_slogger_manager->config);

    // free all the loggers and the logger array
    if (_slogger_manager->loggers != NULL) {
        for (size_t i = 0; i < _slogger_manager->size; i++) {
            free(_slogger_manager->loggers+i);
        }
        free(_slogger_manager->loggers);
    }

}



/**********************
 * INTERNAL FUNCTIONS *
 **********************/



// creates a new config with filename and level
// returns config* on SUCCESS or NULL on FAILURE
SLoggerConfig* _slogger_create_config(FILE* stream, SLogLevel level) {
    SLoggerConfig* config = (SLoggerConfig*) malloc(sizeof(SLoggerConfig));
    if (config == NULL) {
        return NULL;
    }

    config->stream = stream;
    config->level = level;

    return config;
}

SLoggerConfig* _slogger_clone_config(const SLoggerConfig* config) {
    // NOTE: passing config->stream could be dangerous because streams are freed multiple times?
    return _slogger_create_config(config->stream, config->level);
}

// deletes config and frees all it's resources
void _slogger_delete_config(SLoggerConfig* config) {
    if (config == NULL) {
        return;
    }

    if (config->stream != stdin && config->stream != stdout && config->stream != stderr) {
        fclose(config->stream);
    }

    free(config);
}

// adds logger to manager and adjusts capacity if needed
SLogger* _slogger_manager_add_logger(SLogger* logger) {
    if (_slogger_manager == NULL) {
        return NULL;
    }

    // resize capacity if needed
    if (_slogger_manager->size >= capacity) {
        _slogger_manager->capacity *= 2;
        SLogger** loggers = (SLogger**) realloc(_slogger_manager->loggers, sizeof(SLogger*) * _slogger_manager->capacity);
        if (loggers == NULL) {
            // TODO: free logger properly
            free(logger);
            return NULL
        }
        _slogger_manager->loggers = loggers;
    }

    // add base config to logger and logger to manager
    logger->config = _slogger_clone_config(_slogger_manager->config);
    *(_slogger_manager->loggers+_slogger_manager->size) = logger;
    _slogger_manager->size += 1;

}

// removes logger from manager and adjusts capcity where appropriate
SLogger* _slogger_manager_del_logger(SLogger* logger) {
    if (_slogger_manager == NULL) {
        return NULL;
    }

    if (_slogger_manager->loggers == NULL) {
        return NULL;
    }

    size_t i;
    for (i = 0; i < _slogger_manager->size; i++) {
        SLogger* current_logger = *(_slogger_manager->loggers+_slogger_manager->size);
        if (current_logger == logger) {
            free(current_logger->name);
            _slogger_delete_config(current_logger->config);
            free(current_logger);
            break;
        }
    }
    _slogger_manager->size -= 1;
    memmove(_slogger_manager->loggers+i, _slogger_manager->loggers+i+1, sizeof(SLogger*) * (_slogger_manager->size - i));

}


/*
// SLogLevel* gives the ability to say every NULL value stayes unchanged (standards remain for this field)
void slogger_base_config(FILE* log, SLogLevel* level); // changes slogger base configuration

void slogger_get_logger(const char* name);
void slogger_logger_config(const char* name, FILE* log, SLogLevel* level);




SLogger* slogger_manager_get_logger_index(size_t index);
SLogger* slogger_manager_get_logger_name(char* name);

*/



