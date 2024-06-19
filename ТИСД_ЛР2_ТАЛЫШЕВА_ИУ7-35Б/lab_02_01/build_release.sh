#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -c ./*.c -lfort
gcc -o app.exe ./*.o -lm
