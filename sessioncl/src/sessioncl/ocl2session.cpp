#include "clang/AST/RecursiveASTVisitor.h"

#include "ocl2session.hpp"

namespace{
  class Ocl2SessionVisitor
    : public clang::RecursiveASTVisitor<Ocl2SessionVisitor> {
  public:
    bool TraverseDecl(clang::Decl * D) {
      clang::RecursiveASTVisitor<Ocl2SessionVisitor>::TraverseDecl(D);
      return true;
    }
    bool TraverseStmt(clang::Stmt * S) {
      S -> dump();
      clang::RecursiveASTVisitor<Ocl2SessionVisitor>::TraverseStmt(S);
      return true;
    }
    bool TraverseType(clang::QualType T) {
      clang::RecursiveASTVisitor<Ocl2SessionVisitor>::TraverseType(T);
      return true;
    }
  };

  class Ocl2SessionConsumer : public clang::ASTConsumer {
  public:
    virtual void HandleTranslationUnit(clang::ASTContext &Context) {
     Visitor.TraverseDecl(Context.getTranslationUnitDecl());
    }
  private:
    Ocl2SessionVisitor Visitor;
  };
}

namespace ocl2session {
  std::unique_ptr<clang::ASTConsumer>
      Action::CreateASTConsumer(clang::CompilerInstance &Compiler,
                                           llvm::StringRef InFile) {
      return std::unique_ptr<clang::ASTConsumer>(new Ocl2SessionConsumer);
  }
}
