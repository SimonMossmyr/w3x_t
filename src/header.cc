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
    uint32_t map_flags_raw_binary = read_int(&ss);

    header.flags.hide_minimap_in_preview_screens = (bool)((map_flags_raw_binary >> 0) & 1);
    header.flags.modify_ally_priorities = (bool)((map_flags_raw_binary >> 1) & 1);
    header.flags.melee_map = (bool)((map_flags_raw_binary >> 2) & 1);
    header.flags.playable_map_size_was_large_and_has_never_been_reduced_to_medium = (bool)((map_flags_raw_binary >> 3) & 1);
    header.flags.masked_areas_are_partially_visible = (bool)((map_flags_raw_binary >> 4) & 1);
    header.flags.fixed_player_settings_for_custom_forces = (bool)((map_flags_raw_binary >> 5) & 1);
    header.flags.use_custom_forces = (bool)((map_flags_raw_binary >> 6) & 1);
    header.flags.use_custom_techtree = (bool)((map_flags_raw_binary >> 7) & 1);
    header.flags.use_custom_abilities = (bool)((map_flags_raw_binary >> 8) & 1);
    header.flags.use_custom_upgrades = (bool)((map_flags_raw_binary >> 9) & 1);
    header.flags.map_properties_menu_opened_at_least_once_since_map_creation = (bool)((map_flags_raw_binary >> 10) & 1);
    header.flags.show_water_waves_on_cliff_shores = (bool)((map_flags_raw_binary >> 11) & 1);
    header.flags.show_water_waves_on_rolling_shores = (bool)((map_flags_raw_binary >> 12) & 1);

    /** Max players */
    uint32_t max_players = 0;
    ss.read(reinterpret_cast<char*>(&max_players), sizeof(max_players));

    header.max_players = max_players;

    return header;
}
