
# SLogger
### SLogger is a simple logging library written in and for the c programming language!
### It's just a very simple logger and it's just a personal project, i don't actually expect someone to use this logger. So if you want to use this logger use it at your own risk :)
### If you see some things that could be optimised please let me know :D

---

## How to compile this library?

To create a static library
```bash
make static
```

To create a shared library
```bash
make shared
```



## How to use this library?

Initializing the library
```c
if (!slogger_initialize()) {
    return 1; // error while initializing
}
```

Uninitializing the library
```c
slogger_uninitialize();
```

Getting a logger
```c
SLogger* mylogger = slogger_get_logger("mylogger");
```


Changing the logger configuration
```c
// if an argument is NULL that setting won't be changed
// after passing a stream to this function the library is responsible for freeing it
SLogLevel level = DEBUG;
slogger_logger_config(mylogger, stdout, &level); // stdout could be any FILE* stream
```


Logging something
```c
slogger_log(mylogger, WARNING, "Something went wrong!"); // would log [WARNING] (mylogger) Something went wrong!

slogger_log_debug(mylogger, "Debug message!"); // shortcut for slogger_log(..., DEBUG, ...);
```


Log Levels
```
DEBUG -> INFO -> WARNING -> ERROR
```

## Example

```c
#include <slogger.h>

int main() {

    slogger_initialize();

    // standard stream is stderr and standard type is WARNING
    SLogger* mylogger = slogger_get_logger("mylogger");

    FILE* log_file = fopen("my.log", "w");
    if (log_file == NULL) {
        return 1; // failed to open file
    }

    // change stream to opened file
    slogger_logger_config(mylogger, log_file, NULL);


    slogger_log_debug(mylogger, "This is a debug message"); // does not print in current configuration because DEBUG < WARNING
    slogger_log_error(mylogger, "Some kind of error occured!"); // this will be printed in the my.log file because ERROR >= WARNING


    slogger_uninitialize(); // frees all internal allocations and closes all used streams

    return 0;
}
```


