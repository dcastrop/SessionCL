# Session Types for OpenCL

## src

Under directory ./src, there is a basic prototype that uses `libclang` to
to parse a C program, and traverses the `CLang` AST representation of the
program.

## Utils

### Printing the AST in a human-readable way

* The `test` directory contains small C program examples.  **So far, no OpenCL
  program was added to the repository**.

* The following command prints the `test.cpp` AST in a human-readable way.
  Useful for testing purposes

```bash
$ clang -Xclang -ast-dump -fsyntax-only <test_file>.cpp
```

### AST description

* CLang full AST (i.e. clang top level declaration) is represented using
  `TranslationUnitDecl`:
  - FIXME

### AST matcher
