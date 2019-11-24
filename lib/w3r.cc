#include "w3x_t.h"

w3r_type w3r_to_struct(std::string contents) {
    std::stringstream ss(contents);
    w3r_type w3r;

    w3r.format_version = read_int(&ss);
    w3r.n_regions = read_int(&ss);

    w3r.regions.resize(w3r.n_regions);
    for (int i = 0; i < w3r.n_regions; i++) {
        w3r.regions[i].left = read_float(&ss);
        w3r.regions[i].right = read_float(&ss);
        w3r.regions[i].bottom = read_float(&ss);
        w3r.regions[i].top = read_float(&ss);
        w3r.regions[i].name = read_string(&ss);
        w3r.regions[i].id = read_int(&ss);
        w3r.regions[i].weather_effect_id = read_chars(&ss, 4);
        w3r.regions[i].ambient_sound = read_string(&ss);
        w3r.regions[i].color.blue = read_byte(&ss);
        w3r.regions[i].color.green = read_byte(&ss);
        w3r.regions[i].color.red = read_byte(&ss);
        w3r.regions[i].color.alpha = read_byte(&ss);
    }

    w3r.unknown = read_byte(&ss);

    if (!ss.eof()) {
        throw DataStillExistsException("war3map.w3r");
    }

    return w3r;
}
