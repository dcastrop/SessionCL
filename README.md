Session Types for Deadlock Detection in OpenCL
================================================================================

## Directory tree

The contents of this project are under `sessioncl`:

***FIXME: removed outdated stuff. Rewrite for consistency***

```
.
├── build.sh
├── clean.sh
├── CMakeLists.txt
├── configure.sh
├── README.md
├── src
└── test
```

* `build.sh` configures and compiles the project into directory `build`. If the
  directory does not exist, it is created by `configure.sh`.

* `clean.sh` removes directory `build`, and all of its contents.

* `cmake` is a directory that contains `CMake` modules, as specified in
  `CMakeLists.txt`.

  * `cmake/FindLibClang.cmake` is a `CMake` module that searches the `libclang`
    library in the system.

* `CMakeLists.txt` the basic `CMake` project file.

* `configure.sh` runs `cmake` command, and generates the contents under
  directory `build`. If the directory does not exist, it is created.

* `README.md` project README file

* `src` source code for this project.

* `test` test C programs.

## Configuring, Building, Installing

This project uses the CMake build automation tools. The scripts `clean.sh`,
`configure.sh` and `build.sh` have been added for simplicify.

1. `./clean.sh` will remove the directory `build`.

2. `./configure.sh` creates directory `build` (if needed), and generates the
   build (Makefile) files using `cmake`.

3. `./build.sh` runs `./configure.sh` (if needed), and builds the project.
   The output binary file is placed in `./build/sessioncl`

## Running

Use the command `./build/sessioncl [ -h | --help ]` for more information about
the options. The basic usage is:

`Usage: ./sessioncl [options] <file>...`

***TODO:*** add usage description as we start filling project with details.

## Testing

***FIXME*** not yet done.

## Internals

The source files are the following:

```
.
├── log.hpp
├── sessioncl.cpp
└── sessioncl.h.in
```

Under directory ./src, there is a basic prototype that uses `libclang` to
to parse a C program, and traverses the `CLang` AST representation of the
program.


## General CLang and OpenCL information.

General information, useful for manually testing/debugging the sessioncl tool.
Includes information about the clang AST, and (Altera) OpenCL.

### clang and libclang

#### Printing the AST in a human-readable way

* The `test` directory contains small C program examples.  **So far, no OpenCL
  program was added to the repository**.

* The following command prints the `test.cpp` AST in a human-readable way.
  Useful for testing purposes

```bash
$ clang -Xclang -ast-dump -fsyntax-only <test_file>.cpp
```

#### AST description

* CLang full AST (i.e. clang top level declaration) is represented using
  `TranslationUnitDecl`:
  - ***TODO***

#### AST matcher



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

The VM is in https://imperiallondon-my.sharepoint.com/personal/cn06_ic_ac_uk/Documents/package.box?csf=1&e=849709fd054947eba048a72e76feb2f5

Simply use vagrant to setup a virtual machine (from scratch):

    $ vagrant up # in this directory with Vagrantfile

Or use the precompiled VM:

    $ vagrant init package.box # from link above

Then use ssh to access the machine:

    $ vagrant ssh
