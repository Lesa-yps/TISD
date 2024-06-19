#!/bin/bash

find . -type f ! -name "*.sh" ! -name "*.c" ! -name "*.h" ! -name "*.txt" ! -name "*.md" ! -name "Makefile" ! -name ".gitignore" -exec rm {} \;

