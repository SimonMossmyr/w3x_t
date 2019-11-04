#include "w3x_t.h"

header_type header_to_struct(string header_contents) {

    stringstream ss = stringstream(header_contents);
    header_type header;

    /** File ID  */
    char file_id[4 + 1];
    ss.read(file_id, 4);
    file_id[4] = '\0';

    header.file_id = file_id;

    /** Unused/unknown int */
    ss.ignore(4);

    /** Map name */
    char map_name[128];
    ss.getline(map_name, 128, '\0');
    
    header.map_name = map_name;

    /** Map flags */
    uint32_t map_flags_raw_binary = -1;
    ss.read(reinterpret_cast<char *>(&map_flags_raw_binary), sizeof(map_flags_raw_binary)); // black magic

    header.flag.hide_minimap_in_preview_screens = (bool)map_flags_raw_binary;
    header.flag.modify_ally_priorities = (bool)map_flags_raw_binary;
    header.flag.melee_map = map_flags_raw_binary >> 2 & 1;
    header.flag.playable_map_size_was_large_and_has_never_been_reduced_to_medium = (bool)map_flags_raw_binary;
    header.flag.masked_areas_are_partially_visible = (bool)map_flags_raw_binary;
    header.flag.fixed_player_settings_for_custom_forces = (bool)map_flags_raw_binary;
    header.flag.use_custom_forces = (bool)map_flags_raw_binary;
    header.flag.use_custom_techtree = (bool)map_flags_raw_binary;
    header.flag.use_custom_abilities = (bool)map_flags_raw_binary;
    header.flag.use_custom_upgrades = (bool)map_flags_raw_binary;
    header.flag.map_properties_menu_opened_at_least_once_since_map_creation = (bool)map_flags_raw_binary;
    header.flag.show_water_waves_on_cliff_shores = (bool)map_flags_raw_binary;
    header.flag.show_water_waves_on_rolling_shores = (bool)map_flags_raw_binary;

    /** Max players */
    uint32_t max_players = 0;
    ss.read(reinterpret_cast<char*>(&max_players), sizeof(max_players));

    header.max_players = max_players;

    return header;
}
