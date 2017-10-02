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

#define PANIC(s)    log(LOG_PANIC, s); exit(LOG_PANIC)
#define ERROR(s)    log(LOG_ERROR, s); exit(LOG_ERROR)
#define MSG(s)      log(LOG_INFO, s)
#define WARN(s)     log(LOG_WARN, s)
#define DEBUG(s)    log(LOG_DEBUG, s)
#define LOG(s)      log(LOG_VERBOSE, s)

typedef int log_level;

extern log_level g_loglevel;

const char *log_msg(log_level);
void log(log_level, const char *,...);

#endif
