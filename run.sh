#!/usr/bin/env sh
cd $(dirname $0)

rm ./build/strworld

cmake -S . -B build

make -C build

./build/strworld
