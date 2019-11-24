#include "utils.h"

struct w3e_type {
    std::string file_id;
    int format_version;
    byte_type main_tileset;
    bool custom_tileset;
    int n_ground_tilesets;
    std::vector<std::string> ground_tilesets;
    int n_cliff_tilesets;
    std::vector<std::string> cliff_tilesets;
    int map_width_plus_one;
    int map_height_plus_one;
    float center_offset_x;
    float center_offset_y;
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
    std::vector<tilepoint_type> tilepoints;
    byte_type unknown;
};
