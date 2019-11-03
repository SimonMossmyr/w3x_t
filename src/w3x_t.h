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

/** Header keys */
#define HEADER_FLAG_HIDE_MINIMAP_IN_PREVIEW_SCREENS 0
#define HEADER_FLAG_MODIFY_ALLY_PRIORITIES 1
#define HEADER_FLAG_MELEE_MAP 2
#define HEADER_FLAG_PLAYABLE_MAP_SIZE_WAS_LARGE_AND_HAS_NEVER_BEEN_REDUCED_TO_MEDIUM 3
#define HEADER_FLAG_MASKED_AREAS_ARE_PARTIALLY_VISIBLE 4
#define HEADER_FLAG_FIXED_PLAYER_SETTING_FOR_CUSTOM_FORCES 5
#define HEADER_FLAG_USE_CUSTOM_FORCES 6
#define HEADER_FLAG_USE_CUSTOM_TECHTREE 7
#define HEADER_FLAG_USE_CUSTOM_ABILITIES 8
#define HEADER_FLAG_USE_CUSTOM_UPGRADES 9
#define HEADER_FLAG_MAP_PROPERTIES_MENU_OPENED_AT_LEAST_ONCE_SINCE_MAP_CREATION 10
#define HEADER_FLAG_SHOW_WATER_WAVES_ON_CLIFF_SHORES 11
#define HEADER_FLAG_SHOW_WATER_WAVES_ON_ROLLING_SHORES 12

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