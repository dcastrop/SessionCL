#!/bin/bash

[ ! -d ./build ] && ./configure.sh
pushd ./build
make
popd

