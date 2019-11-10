#include "utils.h"

struct wpm_type {
    string file_id;
    uint32_t format_version;
    uint32_t path_map_width;
    uint32_t path_map_height;
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
