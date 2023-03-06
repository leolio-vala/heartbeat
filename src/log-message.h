#ifndef LOG_MESSAGE_H
#define LOG_MESSAGE_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void log_message(const char *msg);
void debug_log_message(const char *msg);

#endif /* LOG_MESSAGE_H */
