#ifndef __LOGGER__
#define __LOGGER__

#define LOG_INFO    0
#define LOG_DEBUG   1
#define LOG_VERBOSE 2

#define DEBUG(s)    log(LOG_DEBUG, s)
#define DEBUG(s)    log(LOG_DEBUG, s)

extern int verbose_flag;

void log(int, const char *,...);

#endif
