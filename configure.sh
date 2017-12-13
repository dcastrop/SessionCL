#!/bin/zsh

[ ! -e ./build ] && mkdir build
pushd build
cmake ..
popd
