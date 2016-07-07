#!/usr/bin/env bash
#
# https://matt.sh/howto-c
#
# clang-format accepts multiple files during one run, but let's limit it to 12
# here so we (hopefully) avoid excessive memory usage.
find ./source \( -name \*.c -or -name \*.cpp -or -name \*.cc -or -name \*.h -or -name \*.hpp \) |xargs -n12 -P4 clang-format-3.8 -i %1
