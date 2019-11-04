#include "w3x_t.h"

w3e_type w3e_to_struct(string contents) {

    stringstream ss(contents);
    w3e_type w3e;

    int i = 0;

    /** File ID */
    char file_id[4 + 1];
    ss.read(file_id, 4);
    file_id[4] = '\0';

    w3e.file_id = file_id;

    /** W3E format version */
    uint32_t format_version = -1;
    ss.read(reinterpret_cast<char *>(&format_version), sizeof(format_version));

    w3e.format_version = format_version;

    /** Main tileset */
    char main_tileset;
    ss.get(main_tileset);

    w3e.main_tileset = main_tileset;

    /** Custom tileset flag */
    uint32_t custom_tileset = -1;
    ss.read(reinterpret_cast<char *>(&custom_tileset), sizeof(custom_tileset));

    w3e.custom_tileset = (bool)custom_tileset;

    /** Number of ground tilesets */
    uint32_t number_of_ground_tilesets_used = -1;
    ss.read(reinterpret_cast<char *>(&number_of_ground_tilesets_used), sizeof(number_of_ground_tilesets_used));

    w3e.number_of_ground_tilesets = number_of_ground_tilesets_used;
    
    /** Ground tilesets */
    w3e.ground_tilesets.resize(number_of_ground_tilesets_used);
    for (int i = 0; i < number_of_ground_tilesets_used; i++) {
        char ground_tilesets[5];
        ss.read(ground_tilesets, 4);
        ground_tilesets[4] = '\0';
        w3e.ground_tilesets[i] = string(ground_tilesets);
    }

    /** Number of cliff tilesets */
    uint32_t number_of_cliff_tilesets_used = -1;
    ss.read(reinterpret_cast<char *>(&number_of_cliff_tilesets_used), sizeof(number_of_cliff_tilesets_used));

    w3e.number_of_cliff_tilesets = number_of_ground_tilesets_used;

    /** Cliff tilesets */
    w3e.cliff_tilesets.resize(number_of_cliff_tilesets_used);
    for (int i = 0; i < number_of_cliff_tilesets_used; i++) {
        char cliff_tilesets[5];
        ss.read(cliff_tilesets, 4);
        cliff_tilesets[4] = '\0';
        w3e.cliff_tilesets[i] = string(cliff_tilesets);
    }

    /** Map width */
    uint32_t map_width_plus_one = -1;
    ss.read(reinterpret_cast<char *>(&map_width_plus_one), sizeof(map_width_plus_one));

    w3e.map_width_plus_one = map_width_plus_one;

    /** Map height */
    uint32_t map_height_plus_one = -1;
    ss.read(reinterpret_cast<char *>(&map_height_plus_one), sizeof(map_height_plus_one));

    w3e.map_height_plus_one = map_height_plus_one;

    /** Center offset X */
    float center_offset_x;
    ss.read(reinterpret_cast<char *>(&center_offset_x), sizeof(center_offset_x));

    w3e.center_offset_x = center_offset_x;

    /** Center offset Y */
    float center_offset_y;
    ss.read(reinterpret_cast<char *>(&center_offset_y), sizeof(center_offset_y));

    w3e.center_offset_y = center_offset_y;

    /** Tilepoint data */
    int number_of_tilepoints = (map_width_plus_one - 1)*(map_height_plus_one - 1);
    w3e.tilepoint.resize(number_of_tilepoints);
    for (int i = 0; i < number_of_tilepoints; i++) {
        w3e.tilepoint[i].ground_height = read_short(&ss);

        short water_level_and_boundary_flag = read_short(&ss);
        w3e.tilepoint[i].water_level = water_level_and_boundary_flag & 0x7FFF; // get lowest 15 bits
        w3e.tilepoint[i].flag.boundary_1 = (bool)(water_level_and_boundary_flag & 0x8000); // get highest bit;
        
        char flags = read_char(&ss);
        w3e.tilepoint[i].flag.ramp = (bool)(flags & 0x1);
        w3e.tilepoint[i].flag.blight = (bool)(flags & 0x2);
        w3e.tilepoint[i].flag.water = (bool)(flags & 0x4);
        w3e.tilepoint[i].flag.boundary_2 = (bool)(flags & 0x8);
        
        char ground_texture_type = (int)read_char(&ss);
        char texture_detail = (int)read_char(&ss);
        char cliff_texture_type = (int)read_char(&ss);
        char layer_height = (int)read_char(&ss);
    }

    return w3e;
}
