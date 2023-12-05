#!/bin/bash

for file in *; do
	if [ -f "$file" ]; then
		if [[ "${file}" != *.sh && "${file}" != *.c && "${file}" != *.h ]]; then
			rm "$file"
		fi
	fi
done
