#!/bin/bash 

if [ -z "$1" ] || [ -z "$2" ]; then
	echo 'Error: 2 files must be entered.'
        exit 2
fi

file31=$(mktemp "${TMPDIR:-/tmp/}$(basename "$0").XXXXXXXXXXXX")
file32=$(mktemp "${TMPDIR:-/tmp/}$(basename "$0").XXXXXXXXXXXX")

function mass {
flag=0
str=''
while read -r -n 1 ch; do
		if [[ $ch =~ [0-9] ]]; then
			str=$str$ch
		elif [[ $ch =~ [+-] ]]; then
			if [[ $str =~ ^[+-]?[0-9][0-9]*[.]?[0-9]*$ ]]; then
					if [[ $m == 1 ]]; then
						echo "$str" >> "$file31"
					else
						echo "$str" >> "$file32"
					fi
					flag=0
			fi
			str=$ch
		elif [[ $ch == '.' ]]; then
			if [[ $str =~  ^[+-]?[0-9][0-9]*$ ]]; then
					if [[ $flag == 0 ]]; then
						str=$str$ch
						flag=1
					else
						if [[ $m == 1 ]]; then
							echo "$str" >> "$file31"
						else
							echo "$str" >> "$file32"
						fi
						str=''
						flag=0
					fi
			fi	
		else
			if [[ $str =~ ^[+-]?[0-9][0-9]*[.]?[0-9]*$ ]]; then
					if [[ $m == 1 ]]; then
						echo "$str" >> "$file31"
					else
						echo "$str" >> "$file32"
					fi
			fi
			flag=0
			str=''
		fi
done <<< "$line"
}

m=1
while IFS= read -r line
do	
	mass
done < "$1"
m=2
while IFS= read -r line
do	
	mass
done < "$2"

if cmp -s "$file31" "$file32" ; then
	rm "$file31"
	rm "$file32"
	exit 0
else
	rm "$file31"
	rm "$file32"
	exit 1
fi
