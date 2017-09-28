# Basic CLang tests

## Printing the AST in a human-readable way

* The example `test.cpp` contains a small function definition.

* The following command prints the `test.cpp` AST in a human-readable way.

```bash
$ clang -Xclang -ast-dump -fsyntax-only test.cpp
```

## AST description

* CLang full AST (i.e. clang top level declaration) is represented using
  `TranslationUnitDecl`:
  - FIXME

## AST matcher
