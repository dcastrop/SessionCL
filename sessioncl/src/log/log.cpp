#include "log.h"

namespace logger {
  log_level g_loglevel = LOG_WARN;

  const char *lvl_msg(log_level lvl) {
    switch (lvl) {
      case LOG_PANIC:
        return "PANIC";
      case LOG_ERROR:
        return "ERROR";
      case LOG_INFO:
        return "INFO";
      case LOG_WARN:
        return "WARNING";
      case LOG_DEBUG:
        return "DEBUG";
      case LOG_VERBOSE:
        return "VERB";
      default:
        return "";
    }
  }

  void write(log_level lvl, const char *fmt,...){
    va_list args;
    if (lvl <= g_loglevel) {
      va_start(args, fmt);

      fprintf(stderr, "%s: ", lvl_msg(lvl));
      vfprintf(stderr, fmt, args);
      fprintf(stderr,"\n");

      va_end(args);
    }
  }

  void set_log_level(log_level lvl){
    g_loglevel = lvl;
  }
}
