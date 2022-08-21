#!/bin/bash

git submodule sync && git submodule update --init && git submodule update --remote --recursive --force

# git pull --recurse-submodules --force && git submodule update --remote --recursive --force
