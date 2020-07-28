#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
void debug(char const *fmt, ...)  __attribute__((__format__(__printf__, 1, 2)));
#else
#define debug(err, ...)
#endif

#endif /* DEBUG_H */
