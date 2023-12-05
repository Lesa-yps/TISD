#!/bin/bash

touch file.txt
file_contents=$(cat "$2")
# shellcheck disable=SC2086
./app.exe $file_contents
a=$?
if [[ $a != 0 ]]; then
	exit 1
else
        ./func_tests/scripts/comparator.sh  ./func_tests/data/file.txt "$1"
	exit $?
fi
