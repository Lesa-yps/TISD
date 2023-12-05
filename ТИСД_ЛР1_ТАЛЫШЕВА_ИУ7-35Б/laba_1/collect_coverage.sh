#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion --coverage -c ./*.c
gcc -o app.exe --coverage  ./*.o -lm

touch file.txt

for file in func_tests/data/*; do
  if [ -f "$file" ]; then
    if [[ "${file}" == func_tests/data/pos_??_in.txt ]]; then
      if [ -f "${file:0:23}args.txt" ]; then
        ./app.exe "$args" < "$file" > file.txt
      else
        echo "Файл ${file:0:23}args.txt не существует"
      fi
    fi
    if [[ "${file}" == func_tests/data/neg_??_in.txt ]]; then
      if [ -f "${file:0:23}args.txt" ]; then
        args=$(< "${file:0:23}args.txt")
        ./app.exe "$args" < "$file" > file.txt
      else
        echo "Файл ${file:0:23}args.txt не существует"
      fi
    fi
  fi
done

gcov ./main.c
