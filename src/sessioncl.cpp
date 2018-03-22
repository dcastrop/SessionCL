#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#ifdef BOOST_FILESYSTEM
#include <boost/filesystem.hpp>
#else
#include <libgen.h>
#endif

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "llvm/Support/CommandLine.h"

#include "log.h"
#include "sessioncl.h"

#ifdef BOOST_FILESYSTEM
namespace fs = boost::filesystem;
#endif

using namespace std;
using namespace clang::tooling;
using namespace llvm;

/* Command name */
static char* prog_name;

void print_version_and_exit() {
  cout << prog_name << " v" << sessioncl_VERSION_MAJOR
                    << "."  << sessioncl_VERSION_MINOR
                    << "."  << sessioncl_VERSION_PATCH << endl;
  exit(0);
}

static llvm::cl::OptionCategory SessionCLCategory("sessioncl options");
// static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
static cl::opt<bool> verbose("verbose",
                             cl::desc("Set verbose mode"),
                             cl::Optional,
                             cl::cat(SessionCLCategory));


class TraverseASTVisitor
  : public clang::RecursiveASTVisitor<TraverseASTVisitor> {
public:
  bool TraverseDecl(clang::Decl * D) {
    clang::RecursiveASTVisitor<TraverseASTVisitor>::TraverseDecl(D);
    return true;
  }
  bool TraverseStmt(clang::Stmt * S) {
    S -> dump();
    clang::RecursiveASTVisitor<TraverseASTVisitor>::TraverseStmt(S);
    return true;
  }
  bool TraverseType(clang::QualType T) {
    clang::RecursiveASTVisitor<TraverseASTVisitor>::TraverseType(T);
    return true;
  }
};

class TraverseASTConsumer : public clang::ASTConsumer {
public:
  virtual void HandleTranslationUnit(clang::ASTContext &Context) {
   Visitor.TraverseDecl(Context.getTranslationUnitDecl());
  }
private:
  TraverseASTVisitor Visitor;
};

class TraverseASTAction : public clang::ASTFrontendAction {
public:
  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
    clang::CompilerInstance &Compiler, llvm::StringRef InFile) {
    return std::unique_ptr<clang::ASTConsumer>(
       new TraverseASTConsumer);
  }
};

int main (int argc, const char **argv){


#ifdef BOOST_FILESYSTEM

  fs::path command = argv[0];
  const char * commstr = command.filename().string().c_str();
  int len_command = sizeof(char) * (strlen(commstr) + 1);
  prog_name = (char *) malloc (len_command);
  memcpy (prog_name, commstr, len_command);
  prog_name[len_command] = 0;

#else

  MSG("Handling paths using POSIX `dirname` and `basename` functions.");
  MSG("In case of problems try installing boost filesystem and rebuilding.");

  char * commstr = basename(argv[0]);
  int len_command = sizeof(char) * (strlen(commstr) + 1);
  prog_name = (char *) malloc (len_command);
  memcpy (prog_name, commstr, len_command);
  prog_name[len_command] = 0;

#endif

  CommonOptionsParser OptionsParser(argc, argv, SessionCLCategory);
  ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());

  if (verbose.getValue()) {
    set_log_level(LOG_VERBOSE);
  }

  int result = Tool.run(newFrontendActionFactory<TraverseASTAction>().get());

  return result;
}

