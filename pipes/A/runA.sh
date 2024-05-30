#!/bin/bash


gcc -o reciever reciever.c

if [ ! -e fifo1 ]; then
    mkfifo fifo1 
fi

./reciever prog3 < fifo1 &

./reciever prog1 < input.txt | tee fifo1 | ./reciever prog2