#!/bin/bash

pipe=/tmp/serverPipe

trap "rm -f $pipe" EXIT

if [[ ! -p $pipe ]]; then
    mkfifo $pipe
fi

while true; do
    if read line < "$pipe"; then
        echo "$line"
    fi
done

echo "Shutting down the server..."
