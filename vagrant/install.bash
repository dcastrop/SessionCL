#!/bin/bash

apt-get update \
    && apt-get install -y linux-source dkms lsb-core openjdk-8-jre \
       clang llvm-dev cmake build-essential environment-modules

/vagrant/opencl_runtime_16.1.2_x64_rh_6.4.0.37/install.sh \
    -s /vagrant/opencl_runtime_16.1.2_x64_rh_6.4.0.37/silent.cfg

/vagrant/intel_sdk_for_opencl_2017_7.0.0.2568_x64/install.sh \
    -s /vagrant/intel_sdk_for_opencl_2017_7.0.0.2568_x64/silent.cfg

update-alternatives --set cc /usr/bin/clang
update-alternatives --set c++ /usr/bin/clang++
