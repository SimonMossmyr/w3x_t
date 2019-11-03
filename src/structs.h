#include <string>
#include <vector>

using namespace std;

struct header_type {
    string file_id;
    string map_name;
    struct flag_type {
        int hide_minimap_in_preview_screens;
        int modify_ally_priorities;
        int melee_map;
        int playable_map_size_was_large_and_has_never_been_reduced_to_medium;
        int masked_areas_are_partially_visible;
        int fixed_player_settings_for_custom_forces;
        int use_custom_forces;
        int use_custom_techtree;
        int use_custom_abilities;
        int use_custom_upgrades;
        int map_properties_menu_opened_at_least_once_since_map_creation;
        int show_water_waves_on_cliff_shores;
        int show_water_waves_on_rolling_shores;
    } flag;
    int max_players;
};

struct w3e_type {
    string file_id;
    int format_version;
    char main_tileset;
    int custom_tileset;
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
            int boundary_1;
            int ramp;
            int blight;
            int water;
            int boundary_2;
        } flag;
        int ground_texture_type;
        int texture_detail;
        int cliff_texture_type;
        int layer_height;
    };
    vector<tilepoint_type> tilepoint;
};
