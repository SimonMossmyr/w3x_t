#include "w3x_t.h"

w3e_type w3e_to_struct(std::string contents) {

    std::stringstream ss(contents);
    w3e_type w3e;

    w3e.file_id = warcraft_id(&ss);
    w3e.format_version = read_int(&ss);
    w3e.main_tileset = tileset(read_char(&ss));
    w3e.custom_tileset = (bool)read_int(&ss);
    
    /** Ground tilesets */
    w3e.n_ground_tilesets = read_int(&ss);
    w3e.ground_tilesets.resize(w3e.n_ground_tilesets);
    for (int i = 0; i < w3e.n_ground_tilesets; i++) {
        w3e.ground_tilesets[i] = warcraft_id(&ss);
    }

    /** Cliff tilesets */
    w3e.n_cliff_tilesets = read_int(&ss);
    w3e.cliff_tilesets.resize(w3e.n_cliff_tilesets);
    for (int i = 0; i < w3e.n_cliff_tilesets; i++) {
        w3e.cliff_tilesets[i] = warcraft_id(&ss);
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
        w3e.tilepoints[i].ground_texture_variation = (int)((ground_and_cliff_variation & 0xF8) >> 3);
        w3e.tilepoints[i].cliff_texture_variation = (int)(ground_and_cliff_variation & 0x7);

        byte_type cliff_texture_and_layer_height = read_byte(&ss);
        w3e.tilepoints[i].cliff_texture_type = (int)((cliff_texture_and_layer_height & 0xF0) >> 4);
        w3e.tilepoints[i].layer_height = (int)(cliff_texture_and_layer_height & 0xF);
    }

    w3e.unknown = read_byte(&ss);

    if (!ss.eof()) {    
        throw data_still_exists("war3map.w3e");
    }

    return w3e;
}

std::string struct_to_w3e(w3e_type w3e) {
    std::stringstream ss;

    w3e.file_id.write_to_ss(ss);
    write_int(ss, w3e.format_version);
    write_char(ss, w3e.main_tileset.to_char());
    write_bool(ss, w3e.custom_tileset);
    write_int(ss, w3e.n_ground_tilesets);
    for (int i = 0; i < w3e.n_ground_tilesets; i++) {
        w3e.ground_tilesets[i].write_to_ss(ss);
    }
    write_int(ss, w3e.n_cliff_tilesets);
    for (int i = 0; i < w3e.n_cliff_tilesets; i++) {
        w3e.cliff_tilesets[i].write_to_ss(ss);
    }
    write_int(ss, w3e.map_width_plus_one);
    write_int(ss, w3e.map_height_plus_one);
    write_float(ss, &w3e.center_offset_x);
    write_float(ss, &w3e.center_offset_y);

    for (int i = 0; i < w3e.map_width_plus_one*w3e.map_height_plus_one; i++) {
        write_short(ss, w3e.tilepoints[i].ground_height);

        short water_height_and_boundary_flag = w3e.tilepoints[i].water_height;
        if (w3e.tilepoints[i].flag.boundary_1) {
            water_height_and_boundary_flag |= 0x80000000;
        }
        write_short(ss, water_height_and_boundary_flag);

        byte_type flags_and_ground_texture = 0;
        if (w3e.tilepoints[i].flag.ramp) {
            flags_and_ground_texture |= 0x10;
        }
        if (w3e.tilepoints[i].flag.blight) {
            flags_and_ground_texture |= 0x20;
        }
        if (w3e.tilepoints[i].flag.water) {
            flags_and_ground_texture |= 0x40;
        }
        if (w3e.tilepoints[i].flag.boundary_2) {
            flags_and_ground_texture |= 0x80;
        }
        flags_and_ground_texture |= (w3e.tilepoints[i].ground_texture_type & 0xF);
        write_byte(ss, flags_and_ground_texture);

        byte_type ground_and_cliff_variation = 0;
        ground_and_cliff_variation |= w3e.tilepoints[i].ground_texture_variation << 3;
        ground_and_cliff_variation |= w3e.tilepoints[i].cliff_texture_variation;
        write_byte(ss, ground_and_cliff_variation);

        byte_type cliff_texture_and_layer_height = 0;
        cliff_texture_and_layer_height |= ((w3e.tilepoints[i].cliff_texture_type << 4));
        cliff_texture_and_layer_height |= w3e.tilepoints[i].layer_height;
        write_byte(ss, cliff_texture_and_layer_height);
    }

    return ss.str();
}
