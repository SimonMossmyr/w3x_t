#include "w3x_t.h"

w3e_type w3e_to_struct(string contents) {

    stringstream ss(contents);
    w3e_type w3e;

    /** File ID */
    char file_id[4 + 1];
    ss.read(file_id, 4);
    file_id[4] = '\0';
    w3e.file_id = file_id;
    
    w3e.format_version = read_int(&ss);
    w3e.main_tileset = read_char(&ss);
    w3e.custom_tileset = (bool)read_int(&ss);
    
    /** Ground tilesets */
    w3e.number_of_ground_tilesets = read_int(&ss);
    w3e.ground_tilesets.resize(w3e.number_of_ground_tilesets);
    for (int i = 0; i < w3e.number_of_ground_tilesets; i++) {
        char ground_tilesets[5];
        ss.read(ground_tilesets, 4);
        ground_tilesets[4] = '\0';
        w3e.ground_tilesets[i] = string(ground_tilesets);
    }

    /** Cliff tilesets */
    w3e.number_of_cliff_tilesets = read_int(&ss);
    w3e.cliff_tilesets.resize(w3e.number_of_cliff_tilesets);
    for (int i = 0; i < w3e.number_of_cliff_tilesets; i++) {
        char cliff_tilesets[5];
        ss.read(cliff_tilesets, 4);
        cliff_tilesets[4] = '\0';
        w3e.cliff_tilesets[i] = string(cliff_tilesets);
    }

    w3e.map_width_plus_one = read_int(&ss);
    w3e.map_height_plus_one = read_int(&ss);
    w3e.center_offset_x = read_float(&ss);
    w3e.center_offset_y = read_float(&ss);

    /** Tilepoint data */
    int number_of_tilepoints = (w3e.map_width_plus_one - 1)*(w3e.map_height_plus_one - 1);
    w3e.tilepoints.resize(number_of_tilepoints);
    for (int i = 0; i < number_of_tilepoints; i++) {
        w3e.tilepoints[i].ground_height = read_short(&ss);

        short water_level_and_boundary_flag = read_short(&ss);
        w3e.tilepoints[i].water_level = water_level_and_boundary_flag & 0x7FFF; // lowest 15 bits
        w3e.tilepoints[i].flag.boundary_1 = (bool)(water_level_and_boundary_flag & 0x8000); // highest bit;
        
        char flags = read_char(&ss);
        w3e.tilepoints[i].flag.ramp = (bool)(flags & 0x1);
        w3e.tilepoints[i].flag.blight = (bool)(flags & 0x2);
        w3e.tilepoints[i].flag.water = (bool)(flags & 0x4);
        w3e.tilepoints[i].flag.boundary_2 = (bool)(flags & 0x8);
        
        char ground_texture_type = (int)read_char(&ss);
        char texture_detail = (int)read_char(&ss);
        char cliff_texture_type = (int)read_char(&ss);
        char layer_height = (int)read_char(&ss);
    }

    return w3e;
}
