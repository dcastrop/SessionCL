#ifndef __OCL2SESSION__
#define __OCL2SESSION__

#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"

#include "cltypes/ast.hpp"

namespace ocl2session {
  class Action : public clang::ASTFrontendAction {
  public:
    virtual std::unique_ptr<clang::ASTConsumer>
      CreateASTConsumer(clang::CompilerInstance &Compiler,
                        llvm::StringRef InFile);
  };
}

#endif
