#include <string>
#include <vector>

using namespace std;

typedef char byte_type;

struct DataStillExistsException : public exception {
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
    int number_of_ground_tilesets;
    vector<string> ground_tilesets;
    int number_of_cliff_tilesets;
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

struct w3do_type {
    string file_id;
    int format_version;
    int format_sub_version;
    int number_of_doodads;
    struct doodad_type {
        string type_id;
        int variation;
        float position_x;
        float position_y;
        float position_z;
        float rotation_angle;
        float scale_x;
        float scale_y;
        float scale_z;
        bool visible;
        bool solid;
        byte_type current_hit_points_percent;
        int item_table_id;
        int number_of_item_sets_dropped;
        int id;
    };
    vector<doodad_type> doodads;
};

struct doo_type {
    w3do_type doodads;

    int special_doodads_format_version;
    int number_of_special_doodads;
    struct special_doodad_type {
        string type_id;
        int position_z;
        int position_x;
        int position_y;
    };
    vector<special_doodad_type> special_doodads;

    w3do_type trees;
};

struct units_doo_type {
    string file_id;
    int file_version;
    int file_sub_version;
    int number_of_units;
    struct unit_type {
        string type_id;
        int variation;
        float position_x;
        float position_y;
        float position_z;
        float rotation_angle;
        float scale_x;
        float scale_y;
        float scale_z;
        bool visible;
        bool solid;
        int owning_player;
        byte_type unknown_1;
        byte_type unknown_2;
        int hit_points;
        int mana_points;
        int number_of_item_sets_dropped;
        int gold_amount;
        float target_acquisition;
        int hero_level;
        int hero_strength;
        int hero_agility;
        int hero_intelligence;
        int number_of_items_in_inventory;
        int number_of_modified_abilities;
    };
    vector<unit_type> units;
};
