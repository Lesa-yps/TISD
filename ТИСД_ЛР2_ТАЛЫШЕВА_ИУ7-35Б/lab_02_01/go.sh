#!/bin/bash

./build_debug_asan.sh
./build_debug_msan.sh
./build_debug_ubsan.sh
./check_scripts.sh
./clean.sh
./collect_coverage.sh

./func_tests/scripts/func_tests.sh

