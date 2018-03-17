#!/bin/bash

git pull --recurse-submodules --force && git submodule update --remote --recursive --force
