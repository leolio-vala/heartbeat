# Heartbeat Command for Docker

This project provides a command line tool called "heartbeat" which can be installed in any Docker image as the last command of an entrypoint. The purpose of this command is to ensure that the Docker container does not exit after it finishes executing all the commands specified in the entrypoint. It also keeps track of the minimum activity by writing a log message every 300 seconds. The logs older than 7 days are automatically removed.

## Usage

To use this command, simply include it as the last command in your Docker entrypoint. For example:

~~~
ENTRYPOINT ["mycommand", "arg1", "arg2", "&&", "heartbeat"]
~~~

This will ensure that the Docker container stays alive after mycommand finishes executing.

## Build

This project is written in C programming language. To build the project, you will need to have a C compiler installed on your system.

~~~
./build.sh
~~~

or using "make-master" which requires full installation of automake
~~~
./make-master build
~~~

## Implementation

The main function of the program creates a directory to be monitored and enters an infinite loop to check for changes to the directory. It logs each iteration of the loop using the log_message function, and exits gracefully when a SIGINT or SIGTERM signal is received.

## Docket exposed folder

The daemon program expected to keep operation data under folder: /data

## Credits

This project was created by Cloudgen Wong. For any questions or concerns, please contact the author at info@leolio.page
