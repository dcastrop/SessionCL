
#ifdef BOOST_FILESYSTEM
#include <boost/filesystem.hpp>
#endif

#include <clang-c/Index.h>
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "sessioncl.h"

#ifdef BOOST_FILESYSTEM
namespace fs = boost::filesystem;
#endif
using namespace std;

ostream& operator<<(ostream& stream, const CXString& str)
{
  stream << clang_getCString(str);
  clang_disposeString(str);
  return stream;
}

// Constants
const int BUF_SIZE = 1;

/* Command name */
static char* prog_name;

/* Flag set by ‘--verbose’. */
static int     verbose_flag = 0;
/* Flag set by ‘--version’. */
static int     version_flag = 0;
/* Flag set by ‘--help’. */
static int     help_flag = 0;
/* Input files */
static int     num_inputs = 0;
static char ** path_input_files;

void print_usage_and_exit() {
  cout << "Usage: " << prog_name << " [options] <file>..." << endl;
  cout << endl;
  cout << "  Options:" << endl;
  cout << "    " << "-V, --verbose  Verbose mode." << endl;
  cout << "    " << "-h, --help     Print help message and exit." << endl;
  cout << "    " << "-v, --version  Print version number and exit." << endl;
  exit(0);
}

void print_version_and_exit() {
  cout << prog_name << " v" << sessioncl_VERSION_MAJOR
                    << "."  << sessioncl_VERSION_MINOR
                    << "."  << sessioncl_VERSION_PATCH << endl;
  exit(0);
}

int main (int argc, char **argv){
  int opt;
  char **files;

  static struct option program_options[] = {
      {"verbose", no_argument,       &verbose_flag, 1},
      {"help"   , no_argument,       &help_flag   , 1},
      {NULL, 0, NULL, 0}
    };
  int option_index = 0;

  #ifdef BOOST_FILESYSTEM
  fs::path command = argv[0];
  int len_command = strlen(command.filename().string().c_str())+1;
  prog_name = (char *) malloc (sizeof(char) * len_command);
  memcpy (prog_name
         , command.filename().string().c_str()
         , sizeof(char) * len_command);
  #else
  cout << "FIXME: boost filesystem required." << endl;
  exit(-1);
  #endif

  while ((opt = getopt_long ( argc
                            , argv
                            , "-hvV"
                            , program_options
                            , &option_index )) != -1){
    switch (opt){
      case 0:
        if (program_options[option_index].flag != NULL) {
          if (help_flag) {
            print_usage_and_exit();
          }
          if (version_flag) {
            print_version_and_exit();
          }
        }
        break;
      case 'h':
        help_flag = 1;
        print_usage_and_exit();
        break;
      case 'v':
        version_flag = 1;
        print_version_and_exit();
        break;
      case 'V':
        verbose_flag = 1;
        break;
      case '\1':
        if ((files = (char **)realloc
                                ( path_input_files
                                , (num_inputs + 1)* sizeof (char *))) == NULL){
          cout << "Panic! Error allocating input file list" << endl;
          exit(-1);
        }
        path_input_files = files;
        path_input_files[num_inputs] =
          (char *)calloc(sizeof(char), strlen(optarg)+1);
        memcpy( path_input_files[num_inputs]
              , optarg
              , sizeof(char) * (strlen(optarg) + 1));

        num_inputs++;
        break;
      default:
        print_usage_and_exit();
        break;
    }
  }
  for (int i = optind; i < argc; i++) {
    if ((files = (char **)realloc
                             ( path_input_files
                             , (num_inputs+1) * sizeof (char *))) == NULL){
      cout << "Panic! Error allocating input file list" << endl;
      exit(-1);
    }
    path_input_files = files;
    path_input_files[num_inputs] = (char *)calloc(sizeof(char), strlen(argv[i])+1);
    memcpy( path_input_files[num_inputs]
          , argv[i]
          , sizeof(char) * strlen(argv[i]));

    num_inputs++;
  }

  if (help_flag) {
    print_usage_and_exit();
  }

  if (version_flag) {
    print_usage_and_exit();
  }

}


//  CXIndex index = clang_createIndex(0, 0);
//  CXTranslationUnit unit = clang_parseTranslationUnit(
//    index,
//    "header.hpp", nullptr, 0,
//    nullptr, 0,
//    CXTranslationUnit_None);
//  if (unit == nullptr)
//  {
//    cerr << "Unable to parse translation unit. Quitting." << endl;
//    exit(-1);
//  }
//
//  CXCursor cursor = clang_getTranslationUnitCursor(unit);
//  clang_visitChildren(
//    cursor,
//    [](CXCursor c, CXCursor parent, CXClientData client_data)
//    {
//      cout << "Cursor '" << clang_getCursorSpelling(c) << "' of kind '"
//        << clang_getCursorKindSpelling(clang_getCursorKind(c)) << "'\n";
//      return CXChildVisit_Recurse;
//    },
//    nullptr);
//
//  clang_disposeTranslationUnit(unit);
//  clang_disposeIndex(index);
//}
