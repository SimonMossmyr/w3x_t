#include "utils.h"

struct w3r_type {
    int format_version;
    int n_regions;
    struct region_type {
        float left;
        float right;
        float bottom;
        float top;
        string name;
        int id;
        string weather_effect_id;
        string ambient_sound;
        rgba_color_type color;
        byte_type unknown;
    };
    vector<region_type> regions;
    byte_type unknown;
};
