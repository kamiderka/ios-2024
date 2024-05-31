#!/bin/bash

pipe=/tmp/testpipe

trap "rm -f $pipe" EXIT

if [[ ! -p $pipe ]]; then
    mkfifo $pipe
fi

while IFS= read -r line; do
    echo "$line" > "$pipe"
done

echo "Shutting down the server..."
