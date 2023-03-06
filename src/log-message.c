#include "project.h"
#include "log-message.h"

/**
 * @brief Write a message to the log file with timestamp and process ID.
 * 
 * This function writes a message to the log file with timestamp and process ID.
 * The log file is located in LOG_DIR directory with the format APP-YYYY-MM-DD.log.
 *
 * @param msg The message to be written to the log file.
 *
 * @return void
 *
 * @details The function uses local time to get the timestamp for the log entry.
 * It then creates a filename using APP, the current year, month, and day. If the file
 * does not exist, it will be created. If the file cannot be opened, an error message
 * will be printed to stderr and the function will return. The log file is opened in "append" mode.
 * If the file cannot be opened, an error message is printed to the console and the function
 * returns without writing the log message. The log message includes a timestamp and process ID,
 * and is written in the following format:
 * 
 *     YYYY-MM-DD HH:MM:SS APP_NAMEAPP_VERSION #PID ] message
 * 
 * Where:
 * - YYYY-MM-DD is the date on which the log message was written
 * - HH:MM:SS is the time at which the log message was written
 * - APP_NAME and APP_VERSION are preprocessor macros defined in config.h
 * - PID is the process ID of the process that wrote the log message
 * - message is the debug log message provided as an argument to the function
 *
 * @note #include <stdio.h>, for FILE, fopen, fprintf, fclose, perror
 * @note #include <stdlib.h>, for pid_t, getpid
 * @note #include <time.h>, for time, localtime, strftime
 * @note #include "project.h", for the following define
 * @note #define LOG_DIR "/var/log/myapp", the directory where log files are stored
 * @note #define APP "myapp", the name of the application
 * @note #define APP_NAME "myapp", the name of the application
 * @note #define APP_VERSION "1.0", the version of the application
 *
 * @see log_message_init() to initialize the log file directory.
 *
 * @author Cloudgen Wong
 * @date 2023-03-06
 */
void log_message(const char *msg) {
  char filename[1024];
  char timestamp[100];
  pid_t pid = getpid();
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  strftime(filename, sizeof(filename), LOG_DIR "/" APP "-%Y-%m-%d.log", &tm);

  FILE *fp = fopen(filename, "a");
  if (fp == NULL) {
    perror("Failed to open log file");
    return;
  }
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &tm);
  fprintf(fp, "%s %s%s #%d ] %s\n",timestamp, APP_NAME, APP_VERSION, pid, msg);
  fclose(fp);
}

/**
 * @brief Write debug log messages to a file with a timestamp and process ID
 * 
 * This function writes a debug log message to a file named "APP-YYYY-MM-DD-debug.log"
 * located in the directory specified by the LOG_DIR macro. The log message includes a 
 * timestamp and process ID.
 * 
 * @param msg The debug log message to be written to the log file.
 * 
 * @return void
 * 
 * @details The debug log message is written to a file named "APP-YYYY-MM-DD-debug.log"
 * in the directory specified by the LOG_DIR macro. The log file is opened in "append" mode.
 * If the file cannot be opened, an error message is printed to the console and the function
 * returns without writing the log message. The log message includes a timestamp and process ID,
 * and is written in the following format:
 * 
 *     YYYY-MM-DD HH:MM:SS APP_NAMEAPP_VERSION #PID ] message
 * 
 * Where:
 * - YYYY-MM-DD is the date on which the log message was written
 * - HH:MM:SS is the time at which the log message was written
 * - APP_NAME and APP_VERSION are preprocessor macros defined in config.h
 * - PID is the process ID of the process that wrote the log message
 * - message is the debug log message provided as an argument to the function
 * 
 * @note #include <stdio.h>, for FILE, fopen, fclose, fprintf, perror
 * @note #include <stdlib.h>, for pid_t
 * @note #include <unistd.h>, for getpid
 * @note #include <time.h>, for time, localtime, strftime
 * 
 * @see log_message
 * 
 * @date 2023-03-05
 * @author Cloudgen Wong
 */
void debug_log_message(const char *msg) {
  char filename[1024];
  char timestamp[100];
  pid_t pid = getpid();
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  strftime(filename, sizeof(filename), LOG_DIR "/" APP "-%Y-%m-%d-debug.log", &tm);

  FILE *fp = fopen(filename, "a");
  if (fp == NULL) {
    perror("Failed to open log file");
    return;
  }
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &tm);
  fprintf(fp, "%s %s%s #%d ] %s\n",timestamp, APP_NAME, APP_VERSION, pid, msg);
  fclose(fp);
}
