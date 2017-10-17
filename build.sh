#!/bin/sh

[ ! -d ./build ] && ./configure.sh
cd ./build
make
cd ..

