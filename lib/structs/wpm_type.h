#include "utils.h"

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
