#include "utils.h"

struct w3i_type {
    uint32_t file_format_version;
    uint32_t map_version;
    uint32_t editor_version;
    string name;
    string author;
    string description;
    string recommended_players;
    float camera_bounds[8];
    uint32_t camera_bounds_complements[4];
    struct playable_area_type {
        uint32_t width;
        uint32_t height;
    } playable_area;
    struct flags_type {
        bool hide_minimap_in_preview;
        bool modify_ally_priorities;
        bool melee_map;
        bool playable_map_size_was_large_and_has_never_been_reduced_to_medium;
        bool masked_area_are_partially_visible;
        bool fixed_player_Setting_for_custom_forces;
        struct use_custom_type {
            bool forces;
            bool techtree;
            bool abilities;
            bool upgrades;
        } use_custom;
        bool map_properties_menu_opened_at_least_once_since_map_creation;
        struct show_water_waves_type {
            bool cliff_shores;
            bool rolling_shores;
        } show_water_waves;
        bool unknown_1;
        bool unknown_2;
        bool unknown_3;
    } flags;
    char main_ground_type;
    uint32_t loading_screen_background_number;
    struct screen_type {
        string path;
        string text;
        string title;
        string subtitle;
    } loading_screen, prologue_screen;
    uint32_t used_game_data_set;
    struct fog_type {
        uint32_t style;
        struct height_type {
            float start;
            float end;
        } height;
        float density;
        rgba_color_type color;
    } fog;
    string global_weather_id;
    string custom_sound_environment;
    char tileset_id_of_custom_light_environment;
    rgba_color_type custom_water_tinting;
    uint32_t max_n_players;
    struct player_type {
        uint32_t number;
        uint32_t type;
        uint32_t race;
        bool has_fixed_start_position;
        string name;
        struct starting_location_type {
            float x;
            float y;
        } starting_location;
        bool low_ally_priorities_for_player[32];
        bool high_ally_priorities_for_player[32];
    };
    vector<player_type> players;
    uint32_t max_n_forces;
    struct force_type {
        struct flags_type {
            bool allied;
            bool allied_victory;
            bool shared_vision;
            bool shared_unit_control;
            bool shared_advanced_unit_control;
        } flags;
        bool player_is_in_this_force[32];
        string name;
    };
    vector<force_type> forces;
    uint32_t n_upgrade_availabilities;
    struct upgrade_availability_type {
        bool applies_to_player[32];
        string id;
        uint32_t level_minus_one_of_the_upgrade_for_which_the_availability_is_changed;
        bool is_available;
        bool is_researched;
    };
    vector<upgrade_availability_type> upgrade_availabilities;
    uint32_t n_tech_availabilities;
    struct tech_availability_type {
        bool applies_to_player[32];
        string id;
    };
    vector<tech_availability_type> tech_availabilities;
    uint32_t n_random_unit_tables;
    struct random_unit_table_type {
        uint32_t n_random_groups;
        struct random_group_type {
            uint32_t number;
            string name;
            uint32_t n_positions;
            vector<uint32_t> positions;
            uint32_t n_widgets;
            struct random_widget_type {
                uint32_t chance;
                vector<string> ids;
            };
            vector<random_widget_type> random_widgets;
        };
        vector<random_group_type> random_groups;
    };
    vector<random_unit_table_type> random_unit_tables;
    uint32_t n_random_items_table_sets;
    struct random_item_table_set_type {
        uint32_t n_random_item_tables;
        struct random_item_table_type {
            uint32_t number;
            string name;
            uint32_t n_item_sets;
            struct item_set_type {
                uint32_t n_items;
                struct item_type {
                    uint32_t percentual_chance;
                    string id;
                };
                vector<item_type> items;
            };
            vector<item_set_type> item_sets;
        };
        vector<random_item_table_type> random_item_tables;
    };
    vector<random_item_table_set_type> random_item_table_sets;
    byte_type unknown;
};
