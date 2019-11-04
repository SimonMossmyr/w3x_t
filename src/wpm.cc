#include "w3x_t.h"

wpm_type wpm_to_struct(string contents) {

    stringstream ss(contents);
    wpm_type wpm;
    
    char file_id[5];
    ss.read(file_id, 4);
    file_id[4] = '\0';
    wpm.file_id = string(file_id);

    wpm.format_version = read_int(&ss);
    wpm.path_map_width = read_int(&ss);
    wpm.path_map_height = read_int(&ss);

    int number_of_pixels = wpm.path_map_width*wpm.path_map_height;
    wpm.flag.resize(number_of_pixels);
    for (int i = 0; i < number_of_pixels; i++) {
        short tile_flags = read_short(&ss);

        wpm.flag[i].walk = (bool)(tile_flags & 0x02);
        wpm.flag[i].fly = (bool)(tile_flags & 0x04);
        wpm.flag[i].build = (bool)(tile_flags & 0x08);
        wpm.flag[i].blight = (bool)(tile_flags & 0x20);
        wpm.flag[i].water = (bool)(tile_flags & 0x40);
        wpm.flag[i].unknown = (bool)(tile_flags & 0x80);
    }

    if (!ss.eof()) {
        cout << "stuff left" << endl;
    }

    return wpm;
}
