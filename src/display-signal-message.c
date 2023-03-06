#include "display-signal-message.h"

/**
 * @brief Displays a message indicating a signal has been received and logs it
 *
 * @param sig The signal received
 *
 * @note Requires snprintf() to format the message string
 * @note #include <stdlib.h> for malloc() and free()
 * @note #include <stdio.h> for snprintf()
 * 
 * @see log_message()
 * 
 * @date 2023-03-05
 * @author Cloudgen Wong
 */
void display_signal_message(int sig){
  char *s = NULL;
  int len = 0;
  len = snprintf(NULL, 0, "«Thread_main» Signal '%d' ..Terminated..", sig);
  s = (char *) malloc(len + 1);
  snprintf(s, len + 1, "«Thread_main» Signal '%d' ..Terminated..", sig);
  log_message(s);
  free(s);
}