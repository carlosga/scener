#!/usr/bin/env bash
find ./source \( -name \*.c -or -name \*.cpp -or -name \*.cc \)|xargs -n1 -P4 clang-tidy-3.8 -header-filter=source/.* -checks=cppcoreguidelines-*,modernize-*,readability-*,misc-*
