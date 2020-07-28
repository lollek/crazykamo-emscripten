#include <stdarg.h>
#include <stdio.h>

#include "debug.h"

#ifdef DEBUG

void debug(char const* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
}

#endif
