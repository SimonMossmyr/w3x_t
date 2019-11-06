#include "w3x_t.h"

shd_type shd_to_struct(string contents, int map_width, int map_height) {

    stringstream ss(contents);
    shd_type shd;

    int number_of_pixels = 16*map_width*map_height;
    shd.shadow.resize(number_of_pixels);
    for (int i = 0; i < number_of_pixels; i++) {
        shd.shadow[i] = (bool)read_byte(&ss);
    }

    shd.unknown_or_unused = read_byte(&ss);

    if (!ss.eof()) {
        throw DataStillExistsException("war3map.shd");
    }

    return shd;
}
