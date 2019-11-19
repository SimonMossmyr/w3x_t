#include "utils.h"

struct mmp_type {
    int format_version;
    int n_icons;
    struct icon_type {
        int type;
        int x;
        int y;
        rgba_color_type color;
    };
    vector<icon_type> icons;
    byte_type unknown_2;
};
