#include "w3x_t.h"

w3s_type w3s_to_struct(string contents) {
    stringstream ss(contents);
    w3s_type w3s;

    w3s.format_version = read_int(&ss);
    
    w3s.n_sounds = read_int(&ss);
    w3s.sounds.resize(w3s.n_sounds);
    for (int i = 0; i < w3s.n_sounds; i++) {
        w3s.sounds[i].id = read_string(&ss);
        w3s.sounds[i].file = read_string(&ss);
        w3s.sounds[i].eax_effect = read_string(&ss);

        int flags = read_int(&ss);
        w3s.sounds[i].flags.looping = flags & 0x01;
        w3s.sounds[i].flags.is_3d = flags & 0x02;
        w3s.sounds[i].flags.stop_when_out_of_range = flags & 0x04;
        w3s.sounds[i].flags.music = flags & 0x08;
        w3s.sounds[i].flags.unknown = flags & 0x10;

        w3s.sounds[i].fade_in_rate = read_int(&ss);
        w3s.sounds[i].fade_out_rate = read_int(&ss);
        w3s.sounds[i].volume = read_int(&ss);
        w3s.sounds[i].pitch = read_float(&ss);
        w3s.sounds[i].unknown_1 = read_float(&ss);
        w3s.sounds[i].unknown_2 = read_int(&ss);
        w3s.sounds[i].channel = read_int(&ss);
        w3s.sounds[i].min_distance = read_float(&ss);
        w3s.sounds[i].max_distance = read_float(&ss);
        w3s.sounds[i].distance_cutoff = read_float(&ss);
        w3s.sounds[i].unknown_3 = read_float(&ss);
        w3s.sounds[i].unknown_4 = read_float(&ss);
        w3s.sounds[i].unknown_5 = read_int(&ss);
        w3s.sounds[i].unknown_6 = read_float(&ss);
        w3s.sounds[i].unknown_7 = read_float(&ss);
        w3s.sounds[i].unknown_8 = read_float(&ss);
    }

    w3s.unknown = read_byte(&ss);

    if (!ss.eof()) {
        throw DataStillExistsException("war3map.w3s");
    }

    return w3s;
}
