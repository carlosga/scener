#!/bin/bash
#
# https://matt.sh/howto-c
#
# clang-format accepts multiple files during one run, but let's limit it to 12
# here so we (hopefully) avoid excessive memory usage.
find ./source \( -name \*.c -or -name \*.cpp -or -name \*.cc \)|xargs -n1 -P4 clang-tidy-3.9 -header-filter=source/.* -checks=cppcoreguidelines-*,readability-*
