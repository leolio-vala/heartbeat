#include "handle-exit.h"

/**
 * @brief Handle exit signal.
 *
 * This function handles the exit signal and displays a message accordingly.
 *
 * @param sig The signal to be handled.
 *
 * @note #include <stdlib.h>, for exit
 *
 * @see display_signal_message
 * @see exit
 *
 * @return void
 *
 * @details This function is called when the program receives an exit signal. It displays a message indicating the type of signal received and exits the program.
 *
 * @date 2023-03-05
 * @author Cloudgen Wong
 */
void handle_exit(int sig) {
  display_signal_message(sig);
  exit(0);
}
