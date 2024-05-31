#!/bin/bash

pipe=/tmp/testpipe

if [[ ! -p $pipe ]]; then
    echo "Reader not running"
    exit 1
fi


while IFS= read -r line; do
    echo "Writing to pipe: $line"
    echo "$line" > "$pipe"
done
