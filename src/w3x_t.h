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

/** Utils */
int read_int(stringstream* ss);
short read_short(stringstream* ss);
char read_char(stringstream* ss);
void warning(string message);
int error(string message);
int error(string message, int error_code);

/** Converters */
header_type header_to_struct(string header_content);
w3e_type w3e_to_struct(string contents);
shd_type shd_to_struct(string contents, int map_width, int map_height);
wpm_type wpm_to_struct(string contents);

/** main */
int read_and_interpret_w3x_header(char* archive_file_name);
string get_contents_from_mpq_file(HANDLE hMpq, string file_name);
int main(int argc, char* argv[]);