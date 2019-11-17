#include <iostream>
#include <fstream>
#include <bitset>
#include <sstream>
#include <string>

#include "structs/header_type.h"
#include "structs/w3e_type.h"
#include "structs/shd_type.h"
#include "structs/wpm_type.h"
#include "structs/doo_type.h"
#include "structs/units_doo_type.h"
#include "structs/w3i_type.h"
#include "structs/wts_type.h"
#include "structs/w3o_type.h"
#include "structs/wtg_type.h"
#include "structs/trigger_data_type.h"
#include "structs/w3c_type.h"
#include "structs/w3r_type.h"
#include "structs/w3s_type.h"
#include "structs/wct_type.h"
#include "structs/imp_type.h"

using namespace std;

#define W3JSON_VERSION_MAJOR 0 // should probably be handled by CMake
#define W3JSON_VERSION_MINOR 0
#define W3JSON_VERSION_PATCH 0

#define W3O_TYPE_INTEGER 0
#define W3O_TYPE_REAL 1
#define W3O_TYPE_UREAL 2
#define W3O_TYPE_STRING 3

/** Utils */
string          read_string (stringstream* ss);
string          read_chars  (stringstream* ss, int amount);
int             read_int    (stringstream* ss);
bool            read_bool   (stringstream* ss);
float           read_float  (stringstream* ss);
short           read_short  (stringstream* ss);
char            read_char   (stringstream* ss);
byte_type       read_byte   (stringstream* ss);

/** Converters */
header_type         header_to_struct        (string header_content);
w3e_type            w3e_to_struct           (string contents);
shd_type            shd_to_struct           (string contents, int map_width, int map_height);
wpm_type            wpm_to_struct           (string contents);
doo_type            doo_to_struct           (string contents);
units_doo_type      units_doo_to_struct     (string contents);
w3i_type            w3i_to_struct           (string contents);
wts_type            wts_to_struct           (string contents);
w3o_type            w3o_to_struct           (string contents, bool is_doodad_ability_or_upgrade, string file_name);
wtg_type            wtg_to_struct           (string content, trigger_data_type trigger_data);
trigger_data_type   trigger_data_to_struct  (string contents);
w3c_type            w3c_to_struct           (string contents);
w3r_type            w3r_to_struct           (string contents);
w3s_type            w3s_to_struct           (string contents);
wct_type            wct_to_struct           (string contents);
imp_type            imp_to_struct           (string contents);
