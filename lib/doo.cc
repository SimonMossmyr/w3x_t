#include "w3x_t.h"

doo_type doo_to_struct(std::string contents) {
    std::stringstream ss(contents);
    doo_type doo;

    doo.doodads.file_id = read_chars(&ss, 4);

    doo.doodads.format_version = read_int(&ss);
    doo.doodads.format_sub_version = read_int(&ss);
    doo.doodads.n_doodads = read_int(&ss);

    doo.doodads.doodads.resize(doo.doodads.n_doodads);
    for (int i = 0; i < doo.doodads.n_doodads; i++) {
        char type_id[5];
        ss.read(type_id, 4);
        type_id[4] = '\0';
        doo.doodads.doodads[i].type_id = std::string(type_id);

        doo.doodads.doodads[i].variation = read_int(&ss);
        doo.doodads.doodads[i].position.x = read_float(&ss);
        doo.doodads.doodads[i].position.y = read_float(&ss);
        doo.doodads.doodads[i].position.z = read_float(&ss);
        doo.doodads.doodads[i].rotation_angle = read_float(&ss);
        doo.doodads.doodads[i].scale.x = read_float(&ss);
        doo.doodads.doodads[i].scale.y = read_float(&ss);
        doo.doodads.doodads[i].scale.z = read_float(&ss);
        
        byte_type flags = read_byte(&ss);
        doo.doodads.doodads[i].visible = (bool)(flags & 1);
        doo.doodads.doodads[i].visible = (bool)(flags & 2);

        doo.doodads.doodads[i].current_hit_points_percent = read_byte(&ss);
        doo.doodads.doodads[i].item_table_id = read_int(&ss);
        doo.doodads.doodads[i].n_item_sets_dropped = read_int(&ss);
        doo.doodads.doodads[i].id = read_int(&ss);
    }

    doo.special_doodads_format_version = read_int(&ss);
    doo.n_special_doodads = read_int(&ss);

    doo.special_doodads.resize(doo.n_special_doodads);
    for (int i = 0; i < doo.n_special_doodads; i++) {
        doo.special_doodads[i].type_id = read_chars(&ss, 4);

        doo.special_doodads[i].position.z = read_int(&ss);
        doo.special_doodads[i].position.x = read_int(&ss);
        doo.special_doodads[i].position.y = read_int(&ss);
    }

    /**
     * For whatever god damn reason I can't encapsulate the w3do_type extraction into its own function,
     * so here's 27 lines of code repetition. If you can encapsulate these two code blocks into a
     * function that takes the std::stringstream as an argument, please do, but after four hours of
     * this I give up.
     */
    doo.trees.file_id = read_chars(&ss, 4);
    doo.trees.format_version = read_int(&ss);
    doo.trees.format_sub_version = read_int(&ss);
    doo.trees.n_doodads = read_int(&ss);

    doo.trees.doodads.resize(doo.trees.n_doodads);
    for (int i = 0; i < doo.trees.n_doodads; i++) {
        char type_id[5];
        ss.read(type_id, 4);
        type_id[4] = '\0';
        doo.trees.doodads[i].type_id = std::string(type_id);

        doo.trees.doodads[i].variation = read_int(&ss);
        doo.trees.doodads[i].position.x = read_float(&ss);
        doo.trees.doodads[i].position.y = read_float(&ss);
        doo.trees.doodads[i].position.z = read_float(&ss);
        doo.trees.doodads[i].rotation_angle = read_float(&ss);
        doo.trees.doodads[i].scale.x = read_float(&ss);
        doo.trees.doodads[i].scale.y = read_float(&ss);
        doo.trees.doodads[i].scale.z = read_float(&ss);
        
        byte_type flags = read_byte(&ss);
        doo.trees.doodads[i].visible = (bool)(flags & 1);
        doo.trees.doodads[i].solid = (bool)(flags & 2);

        doo.trees.doodads[i].current_hit_points_percent = read_byte(&ss);
        doo.trees.doodads[i].item_table_id = read_int(&ss);
        doo.trees.doodads[i].n_item_sets_dropped = read_int(&ss);
        doo.trees.doodads[i].id = read_int(&ss);
    }

    if (!ss.eof()) {
        throw DataStillExistsException("war3map.doo");
    }

    return doo;
}
