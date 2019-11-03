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

    header.flag.hide_minimap_in_preview_screens = map_flags_raw_binary & 1;
    header.flag.modify_ally_priorities = map_flags_raw_binary >> 1 & 1;
    header.flag.melee_map = map_flags_raw_binary >> 2 & 1;
    header.flag.playable_map_size_was_large_and_has_never_been_reduced_to_medium = map_flags_raw_binary >> 3 & 1;
    header.flag.masked_areas_are_partially_visible = map_flags_raw_binary >> 4 & 1;
    header.flag.fixed_player_settings_for_custom_forces = map_flags_raw_binary >> 5 & 1;
    header.flag.use_custom_forces = map_flags_raw_binary >> 6 & 1;
    header.flag.use_custom_techtree = map_flags_raw_binary >> 7 & 1;
    header.flag.use_custom_abilities = map_flags_raw_binary >> 8 & 1;
    header.flag.use_custom_upgrades = map_flags_raw_binary >> 9 & 1;
    header.flag.map_properties_menu_opened_at_least_once_since_map_creation = map_flags_raw_binary >> 10 & 1;
    header.flag.show_water_waves_on_cliff_shores = map_flags_raw_binary >> 11 & 1;
    header.flag.show_water_waves_on_rolling_shores = map_flags_raw_binary >> 12 & 1;

    /** Max players */
    uint32_t max_players = 0;
    ss.read(reinterpret_cast<char*>(&max_players), sizeof(max_players));

    header.max_players = max_players;

    return header;
}
