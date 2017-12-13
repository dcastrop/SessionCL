#!/bin/zsh

[ ! -d ./build ] && ./configure.sh
pushd ./build
make
popd

