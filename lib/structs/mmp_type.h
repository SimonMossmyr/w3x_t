#include "utils.h"

enum ICON_TYPE {gold_mine = 0, house = 1, player_start = 2};

struct mmp_type {
    int format_version;
    int n_icons;
    struct icon_type {
        enum ICON_TYPE type;
        int x;
        int y;
        rgba_color_type color;
    };
    vector<icon_type> icons;
    byte_type unknown_2;
};
