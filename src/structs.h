#include <string>
#include <vector>

using namespace std;

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
    char main_tileset;
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
        short water_level;
        struct flag_type {
            bool boundary_1;
            bool ramp;
            bool blight;
            bool water;
            bool boundary_2;
        } flag;
        int ground_texture_type;
        int texture_detail;
        int cliff_texture_type;
        int layer_height;
    };
    vector<tilepoint_type> tilepoints;
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

struct doo_type {
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
        char current_hit_points_percent;
        int item_table_id;
        int number_of_item_sets_dropped;
        int id;
    };
    vector<doodad_type> doodads;

    int special_doodads_format_version;
    int number_of_special_doodads;
    struct special_doodad_type {
        string type_id;
        int position_z;
        int position_x;
        int position_y;
    };
    vector<special_doodad_type> special_doodads;

    string tree_file_id;
    int tree_format_version;
    int tree_format_sub_version;
    int number_of_trees;
    struct tree_type {
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
        char current_hit_points_percent;
        int item_table_id;
        int number_of_item_sets_dropped;
        int id;
    };
    vector<doodad_type> trees;
};
