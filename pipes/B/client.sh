#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <clientName>"
    exit 1
fi

pipe=/tmp/serverPipe
clientName="$1"
 

if [[ ! -p $pipe ]]; then
    echo "Reader not running"
    exit 1
fi


while IFS= read -r line; do
    echo "Writing to pipe: $line"
    echo "$clientName: $line" > "$pipe"
done
