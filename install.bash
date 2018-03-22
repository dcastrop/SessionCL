#!/bin/bash

apt-get update \
    && apt-get install -y linux-source dkms lsb-core openjdk-8-jre \
       clang llvm-4.0-dev libclang-4.0-dev cmake build-essential environment-modules \
       libgtest-dev \
       libboost-filesystem-dev

/vagrant/opencl_runtime_16.1.2_x64_rh_6.4.0.37/install.sh \
    -s /vagrant/opencl_runtime_16.1.2_x64_rh_6.4.0.37/silent.cfg

/vagrant/intel_sdk_for_opencl_2017_7.0.0.2568_x64/install.sh \
    -s /vagrant/intel_sdk_for_opencl_2017_7.0.0.2568_x64/silent.cfg

update-alternatives --set cc /usr/bin/clang
update-alternatives --set c++ /usr/bin/clang++

mkdir -p /tmp/gtest && \
    cd /tmp/gtest && \
    cmake -DCMAKE_BUILD_TYPE=RELEASE /usr/src/gtest && \
    make && \
    mv libgtest* /usr/lib && \
    cd /tmp && \
    rm -rf /tmp/gtest
