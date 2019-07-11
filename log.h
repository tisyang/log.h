#ifndef LOG_H
#define LOG_H

// simple log macros in a single header file
// Author by TyK
// Link: https://github.com/lazytinker/log.h

#include <stdio.h>

// Enable terminal color, 0 to disable.
#define LOG_ENABLE_COLOR    1
// Enable log error to stderr, 0 to disable.
// In MCU platform, when only printf is support, should be disabled.
#define LOG_ENABLE_STDERR   1
// Enable time stamp, 0 to disable.
// In MCU platform, when time library is not support, should be disabled.
#define LOG_ENABLE_TIME     1
// Enable time stamp with date, 0 to disable.
#define LOG_ENABLE_DATE     1

// Enable time will cause compiler error in C++.
#ifdef __cplusplus
#undef  LOG_ENABLE_TIME
#define LOG_ENABLE_TIME     0
#endif

#ifdef _WIN32
#undef  LOG_ENABLE_COLOR
#define LOG_ENABLE_COLOR 0
#endif

// If enable terminal color
#if LOG_ENABLE_COLOR
# define COLOR_TRACE   "\x1b[94m"
# define COLOR_DEBUG   "\x1b[36m"
# define COLOR_INFO    "\x1b[32m"
# define COLOR_WARN    "\x1b[33m"
# define COLOR_ERROR   "\x1b[31m"
# define COLOR_RESET   "\x1b[0m"
#else
# define COLOR_TRACE
# define COLOR_DEBUG
# define COLOR_INFO
# define COLOR_WARN
# define COLOR_ERROR
# define COLOR_RESET
#endif

// If enable log error to stderr.
// For some MCU platform, only printf is support.
#if LOG_ENABLE_STDERR
# define LOG_STDOUT(...)     fprintf(stdout, __VA_ARGS__)
# define LOG_STDERR(...)     fprintf(stderr, __VA_ARGS__)
#else
# define LOG_STDOUT(...)     printf(__VA_ARGS__)
# define LOG_STDERR(...)     LOG_STDOUT(__VA_ARGS__)
#endif

// If enable time stamp.
// Time stamp need std time library and C99 support.
#if LOG_ENABLE_TIME
#include <time.h>
// ctime() output format: Www Mmm dd hh:mm:ss yyyy
// Example: Wed Feb 13 16:06:10 2013
// Retrieve time at address +11 with length 8
// Retrieve time with date add address + 4 with length 15
# if LOG_ENABLE_DATE
#  define LOG_TIME_SRC    &ctime(&(time_t){time(NULL)})[4]
#  define LOG_TIME_FMT    "%.15s "
# else
#  define LOG_TIME_SRC    &ctime(&(time_t){time(NULL)})[11]
#  define LOG_TIME_FMT    "%.8s "
# endif
#else
# define LOG_TIME_SRC   ""
# define LOG_TIME_FMT   "%s"
#endif

// Log macros.
// ## __VA_ARGS__ will remove the leading comma if __VA_ARGS__ is empty.
#define LOG_TRACE(fmt, ...) LOG_STDOUT(LOG_TIME_FMT COLOR_TRACE "[TRACE] " COLOR_RESET fmt "\n", LOG_TIME_SRC,  ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) LOG_STDOUT(LOG_TIME_FMT COLOR_DEBUG "[DEBUG] " COLOR_RESET fmt "\n", LOG_TIME_SRC,  ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)  LOG_STDOUT(LOG_TIME_FMT COLOR_INFO  "[INFO ] " COLOR_RESET fmt "\n", LOG_TIME_SRC,  ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  LOG_STDOUT(LOG_TIME_FMT COLOR_WARN  "[WARN ] " COLOR_RESET fmt "\n", LOG_TIME_SRC,  ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) LOG_STDERR(LOG_TIME_FMT COLOR_ERROR "[ERROR] " COLOR_RESET fmt "\n", LOG_TIME_SRC,  ##__VA_ARGS__)


#endif // LOG_H

