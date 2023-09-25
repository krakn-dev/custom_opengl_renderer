#!/usr/bin/env sh
cd $(dirname $0)

cmake -S . -B build

make -C build

./build/strworld
