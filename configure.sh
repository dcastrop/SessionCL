#!/bin/zsh

[ ! -e ./build ] && mkdir build
pushd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
popd
