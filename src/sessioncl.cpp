#include <clang-c/Index.h>
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

using namespace std;

ostream& operator<<(ostream& stream, const CXString& str)
{
  stream << clang_getCString(str);
  clang_disposeString(str);
  return stream;
}

// Constants
const int BUF_SIZE = 1;

/* Flag set by ‘--verbose’. */
static int     verbose_flag = 0;
/* Flag set by ‘--help’. */
static int     help_flag = 0;

static int     num_inputs = 0;
static char ** path_input_files;

void print_usage_and_exit(char *prog_name) {
  cout << "Usage: " << prog_name << " [options] <file>..." << endl;
  cout << endl;
  cout << "  Options:" << endl;
  cout << "    "      << "-V, --verbose  Verbose mode." << endl;
  cout << "    "      << "-h, --help     Print help message." << endl;
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

  while ((opt = getopt_long ( argc
                            , argv
                            , "-Vh"
                            , program_options
                            , &option_index )) != -1){
    switch (opt){
      case 0:
        if (program_options[option_index].flag != NULL) {
        }
        break;
      case 'h':
        help_flag = 1;
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
        print_usage_and_exit(argv[0]);
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
    print_usage_and_exit(argv[0]);
  }

}
//
///* Instead of reporting ‘--verbose’
//and ‘--brief’ as they are encountered,
//we report the final status resulting from them. */
//if (verbose_flag)
//puts ("verbose flag is set");
//
///* Print any remaining command line arguments (not options). */
//if (optind < argc)
//{
//printf ("non-option ARGV-elements: ");
//while (optind < argc)
//printf ("%s ", argv[optind++]);
//putchar ('\n');
//}
//
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
