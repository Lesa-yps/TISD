#!/bin/bash 

if [ -z "$1" ] || [ -z "$2" ]; then
	echo 'Error: 2 files must be entered.'
        exit 2
fi

file21=$(mktemp "${TMPDIR:-/tmp/}$(basename "$0").XXXXXXXXXXXX")
file22=$(mktemp "${TMPDIR:-/tmp/}$(basename "$0").XXXXXXXXXXXX")

function mass {
was=0
a=''
while read -r -n 1 ch; 
do
	if [[ $ch == '' ]]; then
			ch=' '
		fi
	if [[ $was == 0 ]]; then
		if [[ $ch =~ ["Result: "] ]]; then
			if [[ ${#a} -eq 8 ]]; then
				a="${a:1}$ch"
			else
				a="$a$ch"
			fi
			if [[  $a  == "Result: " ]]; then
				was=1
				fi	
		else
			a=''
		fi
	else
		if [[ $m == 1 ]]; then
			echo -n "$ch" >> "$file21"
		else
			echo -n "$ch" >> "$file22"
		fi
	fi
done <<< "$line"
}

m=1
flag=0
while IFS= read -r line
do	
	if [[ $flag == 1 ]]; then
		echo "$line" >> "$file21"
	elif [[ $line =~ .*Result:.* ]]; then
		mass
		flag=1
	fi
done < "$1"
m=2
flag=0
while IFS= read -r line
do	
	if [[ $flag == 1 ]]; then
		echo "$line" >> "$file22"
	elif [[ $line =~ .*Result:.* ]]; then
		mass
		flag=1
	fi
done < "$2"

if cmp -s "$file21" "$file22" ; then
	rm "$file21"
	rm "$file22"
	exit 0
else
	rm "$file21"
	rm "$file22"
	exit 1
fi
