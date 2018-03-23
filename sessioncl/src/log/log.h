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

#define PANIC(...)    log::write(LOG_PANIC  , ##__VA_ARGS__); exit(LOG_PANIC)
#define ERROR(...)    log::write(LOG_ERROR  , ##__VA_ARGS__); exit(LOG_ERROR)
#define MSG(...)      log::write(LOG_INFO   , ##__VA_ARGS__)
#define WARN(...)     log::write(LOG_WARN   , ##__VA_ARGS__)
#define LDEBUG(...)   log::write(LOG_DEBUG  , ##__VA_ARGS__)
#define LOG(...)      log::write(LOG_VERBOSE, ##__VA_ARGS__)

namespace logger {
  typedef int log_level;

  extern log_level g_loglevel;

  const char *log_msg(log_level);
  void write(log_level, const char *,...);
  void set_log_level(log_level);
}

#endif
