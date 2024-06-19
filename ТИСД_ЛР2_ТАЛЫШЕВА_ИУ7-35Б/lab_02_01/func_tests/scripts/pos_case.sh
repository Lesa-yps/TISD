#!/bin/bash

touch file.txt
file_contents=$(cat "$2")
# shellcheck disable=SC2086
./app.exe $file_contents > file.txt
a=$?
if [[ $a != 0 ]]; then
	exit 1
else
	./func_tests/scripts/comparator.sh file.txt "$1"
	exit $?
fi
