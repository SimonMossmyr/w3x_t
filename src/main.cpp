#include <StormLib.h>
#include <iostream>
#include <fstream>
#include <bitset>

#define DEFAULT_CHAR_BUFFER_SIZE 512

/** Map flag indices */
#define MAP_FLAG_HIDE_MINIMAP_IN_PREVIEW_SCREENS 0
#define MAP_FLAG_MODIFY_ALLY_PRIORITIES 1
#define MAP_FLAG_MELEE_MAP 2
#define MAP_FLAG_PLAYABLE_MAPS_SIZE_WAS_LARGE_AND_HAS_NEVER_BEEN_REDUCED_TO_MEDIUM 3
#define MAP_FLAG_MASKED_AREAS_ARE_PARTIALLY_VISIBLE 4
#define MAP_FLAG_FIXED_PLAYER_SETTING_FOR_CUSTOM_FORCES 5
#define MAP_FLAG_USE_CUSTOM_FORCES 6
#define MAP_FLAG_USE_CUSTOM_TECHTREE 7
#define MAP_FLAG_USE_CUSTOM_ABILITIES 8
#define MAP_FLAG_USE_CUSTOM_UPGRADES 9
#define MAP_FLAG_MAP_PROPERTIES_MENU_OPENED_AT_LEAST_ONCE_SINCE_MAP_CREATION 10
#define MAP_FLAG_SHOW_WATER_WAVES_ON_CLIFF_SHORES 11
#define MAP_FLAG_SHOW_WATER_WAVES_ON_ROLLING_SHORES 12

using namespace std;

int read_w3x_header(char* archive_file_name) {
    ifstream ifs;
    ifs.open(archive_file_name);
    if (!ifs.good()) {
        return 0;
    }

    /** Read file ID (first 4 bytes) */
    char file_id[4 + 1];
    ifs.read(file_id, 4);
    file_id[4] = '\0';

    /** Fast-forward the input file stream by 4 bytes */
    ifs.ignore(4);

    /** Read map name */
    char map_name[128];
    ifs.getline(map_name, 128, '\0');

    /** Read map flags (4 bytes, only lowest 13 bits mean something) */
    uint32_t map_flags_raw_binary = 0;
    ifs.read(reinterpret_cast<char *>(&map_flags_raw_binary), sizeof(map_flags_raw_binary)); // black magic
    int map_flags[13];
    for (int i = 32-13; i < 32; i++) {
        map_flags[i-(32-13)] = (map_flags_raw_binary >> i-(32-13)) & 1;
    }

    /** Read maximum number of players */
    uint32_t max_number_of_players = 0;
    ifs.read(reinterpret_cast<char*>(&max_number_of_players), sizeof(max_number_of_players));
    
    ifs.close();
    return 1;
}

void warning(string message) {
    cout << "\033[1;33mWarning\033[0m: " << message << " (Code " << GetLastError() << ")" << endl;
}

int error(string message) {
    cout << "\033[1;31mError\033[0m: " << message << " (Code " << GetLastError() << ")" << endl;
    return 1; 
}

int error(string message, int error_code) {
    SetLastError(error_code);
    return error(message);
}

int main(int argc, char* argv[])
{    
    char* archive_file_name = argv[1];

    /** Read W3X Header */
    if(!read_w3x_header(archive_file_name)) {
        return error("Could not read archive header.", 1);
    }

    /** Open w3x as MPQ archive */
    HANDLE hMpq = NULL;
    if(!SFileOpenArchive(archive_file_name, 0, MPQ_OPEN_READ_ONLY, &hMpq)) {
        return error("Archive could not be opened.");
    }

    /** Open archive listfile */
    HANDLE listfile_handle = NULL;
    if(!SFileOpenFileEx(hMpq, "(listfile)", SFILE_OPEN_FROM_MPQ, &listfile_handle)) {
        return error("Listfile could not be opened.");
    }

    /** Find size of listfile */
    DWORD size_of_listfile_high = -1;
    DWORD size_of_listfile = 0;
    size_of_listfile = SFileGetFileSize(listfile_handle, &size_of_listfile_high);
    if (size_of_listfile == SFILE_INVALID_SIZE || size_of_listfile_high != 0) {
        return error("Size of listfile could not be determined.");
    }

    /** Read contents of listfile */
    char listfile_contents[size_of_listfile + 1]; // extra byte for null termination
    DWORD number_of_chars_actually_read = 0;
    if(!SFileReadFile(listfile_handle, &listfile_contents, size_of_listfile, &number_of_chars_actually_read, NULL)) {
        return error("Could not read contents of listfile.");
    }
    listfile_contents[size_of_listfile] = '\0';


    return 0;
}
