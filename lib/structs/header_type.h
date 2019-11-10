#include "utils.h"

struct header_type {
    string file_id;
    string map_name;
    struct flag_type {
        bool hide_minimap_in_preview_screens;
        bool modify_ally_priorities;
        bool melee_map;
        bool playable_map_size_was_large_and_has_never_been_reduced_to_medium;
        bool masked_areas_are_partially_visible;
        bool fixed_player_settings_for_custom_forces;
        bool use_custom_forces;
        bool use_custom_techtree;
        bool use_custom_abilities;
        bool use_custom_upgrades;
        bool map_properties_menu_opened_at_least_once_since_map_creation;
        bool show_water_waves_on_cliff_shores;
        bool show_water_waves_on_rolling_shores;
    } flags;
    uint32_t max_players;
};