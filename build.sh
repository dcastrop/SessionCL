#!/bin/sh

[ ! -f ./build ] && ./configure.sh
cd ./build
make
cd ..

