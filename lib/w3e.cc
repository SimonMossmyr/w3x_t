#include "w3x_t.h"

w3e_type w3e_to_struct(string contents) {

    stringstream ss(contents);
    w3e_type w3e;

    w3e.file_id = read_chars(&ss, 4);    
    w3e.format_version = read_int(&ss);
    w3e.main_tileset = read_byte(&ss);
    w3e.custom_tileset = (bool)read_int(&ss);
    
    /** Ground tilesets */
    w3e.n_ground_tilesets = read_int(&ss);
    w3e.ground_tilesets.resize(w3e.n_ground_tilesets);
    for (int i = 0; i < w3e.n_ground_tilesets; i++) {
        w3e.ground_tilesets[i] = read_chars(&ss, 4);
    }

    /** Cliff tilesets */
    w3e.n_cliff_tilesets = read_int(&ss);
    w3e.cliff_tilesets.resize(w3e.n_cliff_tilesets);
    for (int i = 0; i < w3e.n_cliff_tilesets; i++) {
        w3e.cliff_tilesets[i] = read_chars(&ss, 4);
    }

    w3e.map_width_plus_one = read_int(&ss);
    w3e.map_height_plus_one = read_int(&ss);
    w3e.center_offset_x = read_float(&ss);
    w3e.center_offset_y = read_float(&ss);

    /** Tilepoint data */
    w3e.tilepoints.resize(w3e.map_width_plus_one*w3e.map_height_plus_one);
    for (int i = 0; i < w3e.map_width_plus_one*w3e.map_height_plus_one; i++) {
        w3e.tilepoints[i].ground_height = read_short(&ss);

        short water_height_and_boundary_flag = read_short(&ss);
        w3e.tilepoints[i].water_height = water_height_and_boundary_flag & 0x7FFF; // lowest 15 bits
        w3e.tilepoints[i].flag.boundary_1 = (bool)(water_height_and_boundary_flag & 0x8000); // highest bit;
        
        byte_type flags_and_ground_texture = read_byte(&ss);
        w3e.tilepoints[i].flag.ramp = (bool)(flags_and_ground_texture & 0x10);
        w3e.tilepoints[i].flag.blight = (bool)(flags_and_ground_texture & 0x20);
        w3e.tilepoints[i].flag.water = (bool)(flags_and_ground_texture & 0x40);
        w3e.tilepoints[i].flag.boundary_2 = (bool)(flags_and_ground_texture & 0x80);
        w3e.tilepoints[i].ground_texture_type = (int)(flags_and_ground_texture & 0xF);

        byte_type ground_and_cliff_variation = read_byte(&ss);
        w3e.tilepoints[i].ground_texture_variation = (int)(ground_and_cliff_variation & 0xF8);
        w3e.tilepoints[i].cliff_texture_variation = (int)(ground_and_cliff_variation & 0x7);

        byte_type cliff_texture_and_layer_height = read_byte(&ss);
        w3e.tilepoints[i].cliff_texture_type = (int)(cliff_texture_and_layer_height & 0xF0);
        w3e.tilepoints[i].layer_height = (int)(cliff_texture_and_layer_height & 0x0F);
    }

    w3e.unknown = read_byte(&ss);

    if (!ss.eof()) {    
        throw DataStillExistsException("war3map.w3e");
    }

    return w3e;
}
