#pragma once

#include <stddef.h>

void log(const char *__restrict format, ...);
void warn(const char *__restrict format, ...);
void error(const char *__restrict format, ...);
void debug(const char *__restrict format, ...);
