#include "w3x_t.h"

doo_type doo_to_struct(string contents) {
    stringstream ss(contents);
    doo_type doo;

    char file_id[5];
    ss.read(file_id, 4);
    file_id[4] = '\0';
    doo.doodads.file_id = string(file_id);

    doo.doodads.format_version = read_int(&ss);
    doo.doodads.format_sub_version = read_int(&ss);
    doo.doodads.number_of_doodads = read_int(&ss);

    doo.doodads.doodads.resize(doo.doodads.number_of_doodads);
    for (int i = 0; i < doo.doodads.number_of_doodads; i++) {
        char type_id[5];
        ss.read(type_id, 4);
        type_id[4] = '\0';
        doo.doodads.doodads[i].type_id = string(type_id);

        doo.doodads.doodads[i].variation = read_int(&ss);
        doo.doodads.doodads[i].position_x = read_float(&ss);
        doo.doodads.doodads[i].position_y = read_float(&ss);
        doo.doodads.doodads[i].position_z = read_float(&ss);
        doo.doodads.doodads[i].rotation_angle = read_float(&ss);
        doo.doodads.doodads[i].scale_x = read_float(&ss);
        doo.doodads.doodads[i].scale_y = read_float(&ss);
        doo.doodads.doodads[i].scale_z = read_float(&ss);
        
        int flags = (int)read_char(&ss);
        doo.doodads.doodads[i].visible = (bool)(flags & 1);
        doo.doodads.doodads[i].visible = (bool)(flags & 2);

        doo.doodads.doodads[i].current_hit_points_percent = read_char(&ss);
        doo.doodads.doodads[i].item_table_id = read_int(&ss);
        doo.doodads.doodads[i].number_of_item_sets_dropped = read_int(&ss);
        doo.doodads.doodads[i].id = read_int(&ss);
    }

    doo.special_doodads_format_version = read_int(&ss);
    doo.number_of_special_doodads = read_int(&ss);

    doo.special_doodads.resize(doo.number_of_special_doodads);
    for (int i = 0; i < doo.number_of_special_doodads; i++) {
        char type_id[5];
        ss.read(type_id, 4);
        type_id[4] = '\0';
        doo.special_doodads[i].type_id = string(type_id);
        cout << doo.special_doodads[i].type_id << " ";

        doo.special_doodads[i].position_z = read_int(&ss);
        doo.special_doodads[i].position_x = read_int(&ss);
        doo.special_doodads[i].position_y = read_int(&ss);
    }

    /**
     * For whatever god damn reason I can't encapsulate the w3do_type extraction into its own function,
     * so here's 27 lines of code repetition. If you can encapsulate these two code blocks into a
     * function that takes the stringstream as an argument, please do, but after four hours of
     * this I give up.
     */
    ss.read(file_id, 4);
    doo.trees.file_id = string(file_id);
    doo.trees.format_version = read_int(&ss);
    doo.trees.format_sub_version = read_int(&ss);
    doo.trees.number_of_doodads = read_int(&ss);

    doo.trees.doodads.resize(doo.trees.number_of_doodads);
    for (int i = 0; i < doo.trees.number_of_doodads; i++) {
        char type_id[5];
        ss.read(type_id, 4);
        type_id[4] = '\0';
        doo.trees.doodads[i].type_id = string(type_id);

        doo.trees.doodads[i].variation = read_int(&ss);
        doo.trees.doodads[i].position_x = read_float(&ss);
        doo.trees.doodads[i].position_y = read_float(&ss);
        doo.trees.doodads[i].position_z = read_float(&ss);
        doo.trees.doodads[i].rotation_angle = read_float(&ss);
        doo.trees.doodads[i].scale_x = read_float(&ss);
        doo.trees.doodads[i].scale_y = read_float(&ss);
        doo.trees.doodads[i].scale_z = read_float(&ss);
        
        int flags = (int)read_char(&ss);
        doo.trees.doodads[i].visible = (bool)(flags & 1);
        doo.trees.doodads[i].visible = (bool)(flags & 2);

        doo.trees.doodads[i].current_hit_points_percent = read_char(&ss);
        doo.trees.doodads[i].item_table_id = read_int(&ss);
        doo.trees.doodads[i].number_of_item_sets_dropped = read_int(&ss);
        doo.trees.doodads[i].id = read_int(&ss);
    }

    if (!ss.eof()) {
        error("war3map.doo still contains data after being read. Either file is corrupt or interpreter is incorrect.");
    }

    return doo;
}
