#include "w3x_t.h"

mmp_type mmp_to_struct(std::string contents) {
    std::stringstream ss(contents);
    mmp_type mmp;

    mmp.format_version = read_int(&ss);
    mmp.n_icons = read_int(&ss);
    mmp.icons.resize(mmp.n_icons);
    for (int i = 0; i < mmp.n_icons; i++) {
        mmp.icons[i].type = read_int(&ss);
        mmp.icons[i].x = read_int(&ss);
        mmp.icons[i].y = read_int(&ss);
        mmp.icons[i].color.red = read_byte(&ss);
        mmp.icons[i].color.green = read_byte(&ss);
        mmp.icons[i].color.blue = read_byte(&ss);
        mmp.icons[i].color.alpha = read_byte(&ss);
    }

    mmp.unknown_2 = read_byte(&ss);

    if (!ss.eof()) {
        throw data_still_exists("war3map.mmp");
    }

    return mmp;
}
