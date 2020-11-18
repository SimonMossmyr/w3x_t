#include "w3x_t.h"

shd_type shd_to_struct(std::string contents, int map_width, int map_height) {

    std::stringstream ss(contents);
    shd_type shd;

    int number_of_pixels = 16*map_width*map_height;
    shd.shadow.resize(number_of_pixels);
    for (int i = 0; i < number_of_pixels; i++) {
        shd.shadow[i] = (bool)read_byte(&ss);
    }

    shd.unknown_or_unused = read_byte(&ss);

    if (!ss.eof()) {
        throw data_still_exists("war3map.shd");
    }

    return shd;
}

std::string struct_to_shd(shd_type shd) {
    std::stringstream ss;

    for (int i = 0; i < shd.shadow.size(); i++) {
        if (shd.shadow[i])
        {
            write_byte(ss, 0xf);
        }
        else
        {
            write_byte(ss, 0);
        }
    }

    return ss.str();
}
