#include "utils.h"

struct w3e_type {
    string file_id;
    uint32_t format_version;
    byte_type main_tileset;
    bool custom_tileset;
    uint32_t n_ground_tilesets;
    vector<string> ground_tilesets;
    uint32_t n_cliff_tilesets;
    vector<string> cliff_tilesets;
    uint32_t map_width_plus_one;
    uint32_t map_height_plus_one;
    uint32_t center_offset_x;
    uint32_t center_offset_y;
    struct tilepouint32_t_type {
        short ground_height;
        short water_height;
        struct flag_type {
            bool boundary_1;
            bool ramp;
            bool blight;
            bool water;
            bool boundary_2;
        } flag;
        uint32_t ground_texture_type;
        uint32_t ground_texture_variation;;
        uint32_t cliff_texture_type;
        uint32_t cliff_texture_variation;
        uint32_t layer_height;
    };
    vector<tilepouint32_t_type> tilepoints;
    byte_type unknown;
};
