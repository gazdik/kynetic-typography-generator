#ifndef SRC_MACROS_H_
#define SRC_MACROS_H_

#include <cstdarg>
#include <cstdio>

template <typename T>
void UNUSED(T &&)
{ }

#define LOG(format, ...)  log(__FILE__, __LINE__, __func__, format, ##__VA_ARGS__)
#define LOGERROR(format, ...) logerror(__FILE__, __LINE__, __func__, format, ##__VA_ARGS__)
#define LOGWARN(format, ...) logwarn(__FILE__, __LINE__, __func__, format, ##__VA_ARGS__)
#define LOGINFO(format, ...) loginfo(__FILE__, __LINE__, __func__, format, ##__VA_ARGS__)
#define LOGDEV(format, ...) logdev(__FILE__, __LINE__, __func__, format, ##__VA_ARGS__)


inline void log(const char *file, const int line, const char *func, const char *format, ...)
{
    using namespace std;
    va_list args;

    fprintf(stdout, "LOG %s:%d (%s) | ", file, line, func);
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
    fprintf(stdout, "\n");
}

inline void logerror(const char *file, const int line, const char *func, const char *format, ...)
{
    using namespace std;
    va_list args;

    fprintf(stderr, "\x1b[37;41mERROR %s:%d (%s) | ", file, line, func);
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "\x1b[0m \n");
}

inline void logwarn(const char *file, const int line, const char *func, const char *format, ...)
{
    using namespace std;
    va_list args;

    fprintf(stdout, "\x1b[31;1mWARNING %s:%d (%s) | ", file, line, func);
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
    fprintf(stdout, "\x1b[0m \n");
}

inline void loginfo(const char *file, const int line, const char *func, const char *format, ...)
{
    using namespace std;
    va_list args;

    fprintf(stdout, "\x1b[36mINFO %s:%d (%s) | ", file, line, func);
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
    fprintf(stdout, "\x1b[0m \n");
}

inline void logdev(const char* file, const int line, const char* func, const char* format, ...)
{
    using namespace std;
    va_list args;

    fprintf(stdout, "\x1b[32;1mDEV %s:%d (%s) | ", file, line, func);
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
    fprintf(stdout, "\x1b[0m \n");
}

#endif /* SRC_MACROS_H_ */
