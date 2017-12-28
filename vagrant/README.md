Use Vagrant to setup testing VM
===============================

You'll need to install VirtualBox (from [virtualbox.org](https://virtualbox.org))
and vagrant (`apt-get` is fine).

Before building the VM, download the Intel SDK for OpenCL and Intel CPU-only
OpenCL drivers and put in this directory. The two archive should extract to
`intel_sdk_for_opencl_2017_7.0.0.2568_x64/` and
`opencl_runtime_16.1.2_x64_rh_6.4.0.37/` respectively. If the names do not
match, edit the `install.bash` script accordingly to run the install script.

The `Vagrantfile` in this directory is the configuration for the Virtualbox VM
(i.e. Ubuntu 16.04 LTS) with provisioning shell script `install.bash` to setup
the machine, installing the package dependencies, namely:

- Linux kernel source, DKMS
- LSB core
- JRE 8 (for OpenCL SDK)
- clang + LLVM (dev)

Simply use vagrant to setup a virtual machine:

    $ vagrant up # in this directory with Vagrantfile

Then use ssh to access the machine:

    $ vagrant ssh
