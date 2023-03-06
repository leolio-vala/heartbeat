#include "remove-old-log.h"
#include "log-message.h"

/**
 * @brief A thread function to periodically remove old log files from the specified directory
 * 
 * This function is called by a pthread_create() call in the main function. It takes a void pointer argument
 * which is cast to a const char pointer representing the directory path where log files are located.
 * The function then enters an infinite loop where it calls the remove_old_logs() function every 10 minutes
 * to remove old log files from the specified directory.
 * 
 * @param arg A void pointer argument representing the directory path where log files are located
 * 
 * @return void pointer
 * 
 * @details This function is called by a pthread_create() call in the main function to create a new thread.
 * The function sleeps for 10 minutes (600 seconds) and then calls the remove_old_logs() function to remove
 * old log files from the specified directory. It then repeats this process indefinitely until the program
 * is terminated.
 * 
 * @note #include <unistd.h> for sleep() function
 * 
 * @see remove_old_logs()
 * 
 * @date 2023-03-05
 * @author Cloudgen Wong
 */ 
void *thread_remove_old_logs(void *arg){
  log_message("«Thread_remove_old_logs» ..Started..");
  const char *dir = (const char *)arg;
  while(1) {
    remove_old_logs(dir);
    sleep(600);
  }
}

/**
 * @brief Removes old log files in the specified directory.
 * 
 * This function scans the specified directory and removes any log files
 * that are more than one week old. The age of each file is determined by
 * its last modification time. If an error occurs while opening the
 * directory or removing a file, an error message will be printed to
 * standard error.
 * 
 * @param dir The path to the directory to scan.
 * 
 * @note #include <stdio.h>, for fprintf, stderr
 * @note #include <stdlib.h>, for malloc, free
 * @note #include <sys/types.h>, for DIR, opendir, readdir, closedir
 * @note #include <sys/stat.h>, for stat
 * @note #include <time.h>, for time, difftime
 * 
 * @return void
 * 
 * @details This function is used by the thread function `thread_remove_old_logs`
 * to periodically remove old log files in the background.
 * 
 * @see thread_remove_old_logs
 * 
 * @date 2023-03-06
 * @author Cloudgen Wong
 */

void remove_old_logs(const char *dir) {
  char *s = NULL;
  int len;
  DIR *d = opendir(dir);
  if (d == NULL) {
    len = snprintf(NULL, 0, "«Thread_file_monitor» Error opening directory: %s", dir);
    s = malloc(len + 1);
    snprintf(s, len + 1, "«Thread_file_monitor» Error opening directory: %s", dir);
    fprintf(stderr, "%s\n", s);
    free(s);
    return;
  }
  time_t now = time(NULL);
  struct dirent *entry;
  while ((entry = readdir(d)) != NULL) {
    if (entry->d_type == DT_REG) {
      char path[1024];
      sprintf(path, "%s/%s", dir, entry->d_name);

      struct stat statbuf;
      if (stat(path, &statbuf) == 0) {
        double age = difftime(now, statbuf.st_mtime);
        if (age > 60 * 60 * 24 * 7) {
          if (remove(path) != 0) {
            printf("Error removing file: %s\n", path);
          }
        }
      }
    }
  }
  closedir(d);
}
