#ifndef __LOGGER__
#define __LOGGER__

#include <stdio.h>
#include <stdarg.h>

#define LOG_PANIC   -2
#define LOG_ERROR   -1
#define LOG_INFO    0
#define LOG_WARN    1
#define LOG_DEBUG   2
#define LOG_VERBOSE 3

#define PANIC(...)    log(LOG_PANIC  , ##__VA_ARGS__); exit(LOG_PANIC)
#define ERROR(...)    log(LOG_ERROR  , ##__VA_ARGS__); exit(LOG_ERROR)
#define MSG(...)      log(LOG_INFO   , ##__VA_ARGS__)
#define WARN(...)     log(LOG_WARN   , ##__VA_ARGS__)
#define LDEBUG(...)   log(LOG_DEBUG  , ##__VA_ARGS__)
#define LOG(...)      log(LOG_VERBOSE, ##__VA_ARGS__)

typedef int log_level;

extern log_level g_loglevel;

const char *log_msg(log_level);
void log(log_level, const char *,...);
void set_log_level(log_level);

#endif
