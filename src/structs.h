#include <string>
#include <vector>

using namespace std;

typedef char byte_type;

struct DataStillExistsException : public exception {
    private:
        string message;
    public:
        DataStillExistsException(string file_name) {
            message = file_name + " still contains data after being processed. Either file is corrupt or interpreter is incorrect.";
        }
        const char* what() const throw () {
            return message.c_str();
        }
};

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
    int max_players;
};

struct w3e_type {
    string file_id;
    int format_version;
    byte_type main_tileset;
    bool custom_tileset;
    int n_ground_tilesets;
    vector<string> ground_tilesets;
    int n_cliff_tilesets;
    vector<string> cliff_tilesets;
    int map_width_plus_one;
    int map_height_plus_one;
    int center_offset_x;
    int center_offset_y;
    struct tilepoint_type {
        short ground_height;
        short water_height;
        struct flag_type {
            bool boundary_1;
            bool ramp;
            bool blight;
            bool water;
            bool boundary_2;
        } flag;
        int ground_texture_type;
        int ground_texture_variation;;
        int cliff_texture_type;
        int cliff_texture_variation;
        int layer_height;
    };
    vector<tilepoint_type> tilepoints;
    byte_type unknown;
};

struct shd_type {
    vector<bool> shadow;
    byte_type unknown_or_unused;
};

struct wpm_type {
    string file_id;
    int format_version;
    int path_map_width;
    int path_map_height;
    struct path_pixel_type {
        bool walk;
        bool fly;
        bool build;
        bool blight;
        bool water;
        bool unknown;
    };
    vector<path_pixel_type> path_pixels;
};

struct position_type {
    float x;
    float y;
    float z;
};

struct scale_type {
    float x;
    float y;
    float z;
};

struct w3do_type {
    string file_id;
    int format_version;
    int format_sub_version;
    int n_doodads;
    struct doodad_type {
        string type_id;
        int variation;
        position_type position;
        float rotation_angle;
        scale_type scale;
        bool visible;
        bool solid;
        byte_type current_hit_points_percent;
        int item_table_id;
        int n_item_sets_dropped;
        int id;
    };
    vector<doodad_type> doodads;
};

struct doo_type {
    w3do_type doodads;

    int special_doodads_format_version;
    int n_special_doodads;
    struct special_doodad_type {
        string type_id;
        position_type position;
    };
    vector<special_doodad_type> special_doodads;

    w3do_type trees;
};

struct units_doo_type {
    string file_id;
    int file_version;
    int file_sub_version;
    int n_units;
    struct unit_type {
        string type_id;
        int variation;
        position_type position;
        float rotation_angle;
        scale_type scale;
        bool visible;
        bool solid;
        int owning_player;
        byte_type unknown_1;
        byte_type unknown_2;
        int hit_points;
        int mana_points;
        int dropped_item_sets_id;
        int n_item_sets_dropped;
        struct dropped_item_set_type {
            int size;
            struct item_type {
                string item_id;
                int chance_to_be_dropped;
            };
            vector<item_type> items;
        };
        vector<dropped_item_set_type> dropped_item_sets;
        int gold_amount;
        float target_acquisition;
        struct hero_stats_type {
            int level;
            int strength;
            int agility;
            int intelligence;
        } hero_stats;
        int n_items_in_inventory;
        struct item_in_inventory_type {
            int slot;
            string type_id;
        };
        vector<item_in_inventory_type> items_in_inventory;
        int n_modified_abilities;
        struct modified_ability_type {
            string ability_id;
            bool autocast_active;
            int level;
        };
        vector<modified_ability_type> modified_abilities;
        int random_flag;
        struct random_item_neutral_passive_type {
            byte_type level_high; // actually 24-bit number
            byte_type level_mid;
            byte_type level_low;
            byte_type item_class;
        } random_item_neutral_passive;
        struct random_unit_from_random_group_type {
            int unit_group;
            int position;
        } random_unit_from_random_group;
        struct random_unit_from_custom_table_type {
            int n_units;
            struct table_entry_type {
                string unit_id;
                int chance;
            };
            vector<table_entry_type> table;
        } random_unit_from_custom_table;
        int custom_color;
        int waygate;
        int id;
    };
    vector<unit_type> units;
    byte_type unknown;
};

struct rgba_color_type {
    byte_type red;
    byte_type green;
    byte_type blue;
    byte_type alpha;
};

struct w3i_type {
    int file_format_version;
    int map_version;
    int editor_version;
    string map_name;
    string author;
    string map_description;
    string players_recommended;
    float camera_bounds[8];
    int camera_bounds_complements[4];
    int playable_width;
    int playable_height;
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
    string path_of_custom_loading_screen_model;
    struct screen_type {
        string text;
        string title;
        string screen_subtitle;
    } loading_screen, prologue_screen;
    int used_game_data_set;
    int terrain_fog_style;
    struct fog_type {
        float height_start;
        float height_end;
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
        float x;
        float y;
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
        string tech_id;
    };
    vector<tech_availability_type> tech_availabilities;
    int n_random_unit_tables;
    struct random_unit_table_type {
        int n_random_groups;
        struct random_group_type {
            int group_number;
            string group_name;
            int n_positions;
            vector<int> positions;
            int n_widgets;
            struct random_widget_type {
                int chance;
                vector<char> id;
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
    vector<random_item_table_set_type> random_item_table_set;
};
