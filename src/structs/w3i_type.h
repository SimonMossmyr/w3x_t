#include "utils.h"

struct w3i_type {
    int file_format_version;
    int map_version;
    int editor_version;
    string name;
    string author;
    string description;
    string recommended_players;
    float camera_bounds[8];
    int camera_bounds_complements[4];
    struct playable_area_type {
        int width;
        int height;
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
    int loading_screen_background_number;
    struct screen_type {
        string path;
        string text;
        string title;
        string subtitle;
    } loading_screen, prologue_screen;
    int used_game_data_set;
    struct fog_type {
        int style;
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
    int max_n_players;
    struct player_type {
        int number;
        int type;
        int race;
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
    int max_n_forces;
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
    int n_upgrade_availabilities;
    struct upgrade_availability_type {
        bool applies_to_player[32];
        string id;
        int level_minus_one_of_the_upgrade_for_which_the_availability_is_changed;
        bool is_available;
        bool is_researched;
    };
    vector<upgrade_availability_type> upgrade_availabilities;
    int n_tech_availabilities;
    struct tech_availability_type {
        bool applies_to_player[32];
        string id;
    };
    vector<tech_availability_type> tech_availabilities;
    int n_random_unit_tables;
    struct random_unit_table_type {
        int n_random_groups;
        struct random_group_type {
            int number;
            string name;
            int n_positions;
            vector<int> positions;
            int n_widgets;
            struct random_widget_type {
                int chance;
                vector<string> ids;
            };
            vector<random_widget_type> random_widgets;
        };
        vector<random_group_type> random_groups;
    };
    vector<random_unit_table_type> random_unit_tables;
    int n_random_items_table_sets;
    struct random_item_table_set_type {
        int n_random_item_tables;
        struct random_item_table_type {
            int number;
            string name;
            int n_item_sets;
            struct item_set_type {
                int n_items;
                struct item_type {
                    int percentual_chance;
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
