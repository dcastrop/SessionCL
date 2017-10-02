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

// Using LibCLang for two reasons:
//    1) Apparently, this is the "stable/backwards-compatible interface"
//    2) It provides a high-level interface to the clang AST ... which is what
//    we want? We don't really want access to the full details of the CLang AST
//    to infer a "session type" from OpenCL code.
#include <clang-c/Index.h>

#include "log.h"
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

std::string getCursorKindName( CXCursorKind cursorKind )
{
  CXString kindName  = clang_getCursorKindSpelling( cursorKind );
  std::string result = clang_getCString( kindName );

  clang_disposeString( kindName );
  return result;
}

std::string getCursorSpelling( CXCursor cursor )
{
  CXString cursorSpelling = clang_getCursorSpelling( cursor );
  std::string result      = clang_getCString( cursorSpelling );

  clang_disposeString( cursorSpelling );
  return result;
}

CXChildVisitResult visitAST( CXCursor cursor, CXCursor /* parent */, CXClientData clientData )
{
  CXSourceLocation location = clang_getCursorLocation( cursor );
  if( clang_Location_isFromMainFile( location ) == 0 )
    return CXChildVisit_Continue;

  CXCursorKind cursorKind = clang_getCursorKind( cursor );

  unsigned int curLevel  = *( reinterpret_cast<unsigned int*>( clientData ) );
  unsigned int nextLevel = curLevel + 1;

  std::cout << std::string( curLevel, '-' ) << " " << getCursorKindName(
  cursorKind ) << " (" << getCursorSpelling( cursor ) << ")\n";

  clang_visitChildren( cursor,
                       visitAST,
                       &nextLevel );

  return CXChildVisit_Continue;
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
        if ((files
              = (char **)realloc
                           ( path_input_files
                           , (num_inputs + 1)* sizeof (char *))) == NULL){
          PANIC("Cannot allocate memory for input file list");
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
      PANIC("Cannot allocate memory for input file list");
    }
    path_input_files = files;
    path_input_files[num_inputs]
      = (char *)calloc(sizeof(char), strlen(argv[i])+1);
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

  // EXAMPLE LIBLANG CODE
  for (int i = 0; i < num_inputs; i++ ) {

    MSG("Processing %s", path_input_files[i]);

    CXIndex index = clang_createIndex(0, 0);
    CXTranslationUnit unit = clang_parseTranslationUnit(
      index,
      path_input_files[i], nullptr, 0,
      nullptr, 0,
      CXTranslationUnit_None);
    if (unit == nullptr){
      ERROR("Unable to parse translation unit. Quitting.");
    }

    unsigned level = 0;
    CXCursor cursor = clang_getTranslationUnitCursor(unit);
    clang_visitChildren(
      cursor,
      visitAST,
      &level);

    clang_disposeTranslationUnit(unit);
    clang_disposeIndex(index);
  }

}

