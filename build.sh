#!/bin/sh

# @author Cloudgen Wong
# @date 2023-03-06

FNAME=heartbeat
TARGET_DIR=target
TARGET=${TARGET_DIR}/${FNAME}

# create the target directory if it doesn't exist
mkdir -p ${TARGET_DIR}

# clean the target folder for any previous compilation
rm -rf ${TARGET}

gcc -Wall -Werror \
    src/display-signal-message.c \
    src/handle-exit.c \
    src/log-message.c \
    src/main.c \
    src/make-directory.c \
    src/remove-old-log.c \
    -o ${TARGET}

# Make the binary executable
chmod +x ${TARGET}

if [ $? -ne 0 ]; then
    echo "Build failed. Please check the error messages above."
    exit 1
else
    if [ "$1" == install ]; then
        # Install the binary to /usr/bin/
        cp ${TARGET} /usr/bin/ || { echo "Installation failed."; exit 1; }
        echo "Build successful! Please run '${FNAME}'"
    elif [ "$1" == clean ]; then
        rm -rf ${TARGET_DIR}/*
        echo "Folder ${TARGET_DIR} has been cleared!"
    else
        echo "Build successful! Please run '${TARGET}'"
    fi
    exit 0
fi