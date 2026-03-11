#include <slogger.h>

SLoggerManager* _slogger_manager;

void slogger_initialize() {
    _slogger_manager = (SLoggerManager*) malloc(sizeof(SLoggerManager));
}



