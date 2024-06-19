#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=undefined -fno-omit-frame-pointer -g -c ./*.c

clang -fsanitize=undefined -fno-omit-frame-pointer -g -o app.exe ./*.o -lm
