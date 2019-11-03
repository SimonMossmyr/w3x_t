#include <iostream>
#include <fstream>
#include <bitset>
#include <sstream>
#include <string>
#include <StormLib.h>

#include "structs.h"

/** Version (semantic) */
#define W3JSON_VERSION_MAJOR 0
#define W3JSON_VERSION_MINOR 0
#define W3JSON_VERSION_PATCH 0

/** error.cc */
void warning(string message);
int error(string message);
int error(string message, int error_code);

/** Converters */

header_type header_to_struct(string header_content);


/** JSON converters */
w3e_type w3e_to_json(string w3e_contents);

/** main */
int read_and_interpret_w3x_header(char* archive_file_name);
int main(int argc, char* argv[]);