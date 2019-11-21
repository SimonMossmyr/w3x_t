#include "utils.h"

struct w3r_type {
    int format_version;
    int n_regions;
    struct region_type {
        float left;
        float right;
        float bottom;
        float top;
        std::string name;
        int id;
        std::string weather_effect_id;
        std::string ambient_sound;
        rgba_color_type color;
        byte_type unknown;
    };
    std::vector<region_type> regions;
    byte_type unknown;
};
