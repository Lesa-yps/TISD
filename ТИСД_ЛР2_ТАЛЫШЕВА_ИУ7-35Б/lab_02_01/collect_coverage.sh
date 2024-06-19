#!/bin/bash

gcc -fprofile-arcs -ftest-coverage -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -c ./*.c
gcc -fprofile-arcs -ftest-coverage -o app.exe ./*.o -lm

for file in ./func_tests/data/*; do
	if [ -f "$file" ]; then
		if [[ "${file}" == ./func_tests/data/pos_??_in.txt ]]; then
			file_contents=$(cat "${file:0:25}""args.txt")
			# shellcheck disable=SC2086
			./app.exe $file_contents > file.txt
		fi
		if [[ "${file}" == ./func_tests/data/neg_??_in.txt ]]; then
			file_contents=$(cat "${file:0:25}""args.txt")
			# shellcheck disable=SC2086
			./app.exe $file_contents > file.txt
		fi
	fi
done

gcov ./*.c


