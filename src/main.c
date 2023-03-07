#include <stdio.h>          /* for fprintf, stderr */ 
#include <stdlib.h>         /* for exit */
#include <unistd.h>         /* for sleep */
#include <signal.h>         /* for signal, SIGINT, SIGTERM */
#include "handle-exit.h"
#include "log-message.h"
#include "make-directory.h"
#include "project.h"
#include "remove-old-log.h"

/**
 * @brief The main function of the program.
 * 
 * @details This function creates a directory to be monitored and enters an infinite loop to check for changes
 * to the directory. It logs each iteration of the loop using the `log_message` function, and exits gracefully 
 * when a SIGINT or SIGTERM signal is received.
 * 
 * @note #include <stdio.h>, for fprintf, stderr
 * @note #include <stdlib.h>, for exit
 * @note #include <unistd.h>, for sleep
 * @note #include <signal.h>, for signal, SIGINT, SIGTERM
 * 
 * @return int Returns 0 if the program runs successfully.
 * 
 * @see handle_exit
 * @see make_directory
 * @see remove_old_logs
 * 
 * @author Cloudgen Wong
 * @date 2023-03-07
 */
int main(int argc, char *argv[]) {
  char started = 0;

  if (make_directory(LOG_DIR) != 0) {
    fprintf(stderr, "«Thread_main» Creating directory to be monitored ..Error..\n");
    // No log to keep
    return 1;
  }
  signal(SIGINT, handle_exit);
  signal(SIGTERM, handle_exit);
  if (argc > 1 && (strcmp(argv[1], "-v") == 0 ||  strcmp(argv[1], "--version") == 0)){
    printf("%s (%s)\nHomepage: https://github.com/leolio-vala/heartbeat\n\n", APP_NAME, APP_VERSION );
  } else if (argc == 1) {
    while (1) {
      if ( !started ) {
        log_message("«Thread_main» ============ Started ============");
        started = 1;
      } else {
        log_message(".");
      }
      remove_old_logs(LOG_DIR);
      sleep(300);
    }
  }
  return 0;
}
