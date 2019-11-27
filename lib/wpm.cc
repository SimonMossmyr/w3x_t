#include "w3x_t.h"

wpm_type wpm_to_struct(std::string contents) {

    std::stringstream ss(contents);
    wpm_type wpm;
    
    wpm.file_id = warcraft_id(&ss);
    wpm.format_version = read_int(&ss);
    wpm.path_map_width = read_int(&ss);
    wpm.path_map_height = read_int(&ss);

    int number_of_pixels = wpm.path_map_width*wpm.path_map_height;
    wpm.path_pixels.resize(number_of_pixels);
    for (int i = 0; i < number_of_pixels; i++) {
        short tile_flags = read_short(&ss);

        wpm.path_pixels[i].walk = (bool)(tile_flags & 0x02);
        wpm.path_pixels[i].fly = (bool)(tile_flags & 0x04);
        wpm.path_pixels[i].build = (bool)(tile_flags & 0x08);
        wpm.path_pixels[i].blight = (bool)(tile_flags & 0x20);
        wpm.path_pixels[i].water = (bool)(tile_flags & 0x40);
        wpm.path_pixels[i].unknown = (bool)(tile_flags & 0x80);
    }

    if (!ss.eof()) {
        throw data_still_exists("war3map.wpm");
    }

    return wpm;
}
