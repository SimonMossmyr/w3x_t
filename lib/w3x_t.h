#include <iostream>
#include <fstream>
#include <bitset>
#include <sstream>
#include <string>

#include "structs/w3e_type.h"
#include "structs/shd_type.h"
#include "structs/wpm_type.h"
#include "structs/doo_type.h"
#include "structs/units_doo_type.h"
#include "structs/w3i_type.h"
#include "structs/wts_type.h"
#include "structs/mmp_type.h"
#include "structs/w3o_type.h"
#include "structs/wtg_type.h"
#include "structs/trigger_data_type.h"
#include "structs/w3c_type.h"
#include "structs/w3r_type.h"
#include "structs/w3s_type.h"
#include "structs/wct_type.h"
#include "structs/imp_type.h"

#define W3JSON_VERSION_MAJOR 0 // should probably be handled by CMake
#define W3JSON_VERSION_MINOR 0
#define W3JSON_VERSION_PATCH 0

#define W3O_TYPE_INTEGER 0
#define W3O_TYPE_REAL 1
#define W3O_TYPE_UREAL 2
#define W3O_TYPE_STRING 3

/** Utils */
std::string str_to_hex(std::string s);
std::string string_to_hex(const std::string& input);
std::string read_string (std::stringstream* ss);
void write_string(std::stringstream& ss, std::string s);
std::string read_chars (std::stringstream* ss, int amount);
void write_chars(std::stringstream& ss, std::string s, int amount);
int read_int (std::stringstream* ss);
void write_int(std::stringstream& ss, int i);
void write_bools_as_mask(std::stringstream& ss, bool bools[], int amount);
bool read_bool (std::stringstream* ss);
void write_bool(std::stringstream& ss, bool b);
float read_float (std::stringstream* ss);
void write_float(std::stringstream& ss, float* f);
short read_short (std::stringstream* ss);
void write_short(std::stringstream& ss, short s);
char read_char (std::stringstream* ss);
void write_char(std::stringstream& ss, char c);
byte_type read_byte (std::stringstream* ss);
void write_byte(std::stringstream& ss, byte_type b);

/** Converters */
w3e_type            w3e_to_struct           (std::string contents);
shd_type            shd_to_struct           (std::string contents, int map_width, int map_height);
wpm_type            wpm_to_struct           (std::string contents);
doo_type            doo_to_struct           (std::string contents);
units_doo_type      units_doo_to_struct     (std::string contents);
w3i_type            w3i_to_struct           (std::string contents);
wts_type            wts_to_struct           (std::string contents);
mmp_type            mmp_to_struct           (std::string contents);
w3o_type            w3o_to_struct           (std::string contents, bool is_doodad_ability_or_upgrade, std::string file_name);
wtg_type            wtg_to_struct           (std::string content, trigger_data_type trigger_data);
trigger_data_type   trigger_data_to_struct  (std::string contents);
w3c_type            w3c_to_struct           (std::string contents);
w3r_type            w3r_to_struct           (std::string contents);
w3s_type            w3s_to_struct           (std::string contents);
wct_type            wct_to_struct           (std::string contents);
imp_type            imp_to_struct           (std::string contents);

std::string struct_to_w3e(w3e_type w3e);