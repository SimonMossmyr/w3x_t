#include "w3x_t.h"

doo_type doo_to_struct(string contents) {
    stringstream ss(contents);
    doo_type doo;

    char file_id[5];
    ss.read(file_id, 4);
    file_id[4] = '\0';
    doo.file_id = string(file_id);

    doo.format_version = read_int(&ss);
    doo.format_sub_version = read_int(&ss);
    doo.number_of_doodads = read_int(&ss);

    doo.doodads.resize(doo.number_of_doodads);
    for (int i = 0; i < doo.number_of_doodads; i++) {
        char type_id[5];
        ss.read(type_id, 4);
        type_id[4] = '\0';
        doo.doodads[i].type_id = string(type_id);

        doo.doodads[i].variation = read_int(&ss);
        doo.doodads[i].position_x = read_float(&ss);
        doo.doodads[i].position_y = read_float(&ss);
        doo.doodads[i].position_z = read_float(&ss);
        doo.doodads[i].rotation_angle = read_float(&ss);
        doo.doodads[i].scale_x = read_float(&ss);
        doo.doodads[i].scale_y = read_float(&ss);
        doo.doodads[i].scale_z = read_float(&ss);
        
        int flags = (int)read_char(&ss);
        doo.doodads[i].visible = (bool)(flags & 1);
        doo.doodads[i].visible = (bool)(flags & 2);

        doo.doodads[i].current_hit_points_percent = read_char(&ss);
        doo.doodads[i].item_table_id = read_int(&ss);
        doo.doodads[i].number_of_item_sets_dropped = read_int(&ss);
        doo.doodads[i].id = read_int(&ss);
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

    ss.read(file_id, 4);
    doo.tree_file_id = string(file_id);

    doo.tree_format_version = read_int(&ss);
    doo.tree_format_sub_version = read_int(&ss);
    doo.number_of_trees = read_int(&ss);

    doo.trees.resize(doo.number_of_trees);
    for (int i = 0; i < doo.number_of_trees; i++) {
        char type_id[5];
        ss.read(type_id, 4);
        type_id[4] = '\0';
        doo.trees[i].type_id = string(type_id);

        doo.trees[i].variation = read_int(&ss);
        doo.trees[i].position_x = read_float(&ss);
        doo.trees[i].position_y = read_float(&ss);
        doo.trees[i].position_z = read_float(&ss);
        doo.trees[i].rotation_angle = read_float(&ss);
        doo.trees[i].scale_x = read_float(&ss);
        doo.trees[i].scale_y = read_float(&ss);
        doo.trees[i].scale_z = read_float(&ss);
        
        int flags = (int)read_char(&ss);
        doo.trees[i].visible = (bool)(flags & 1);
        doo.trees[i].visible = (bool)(flags & 2);

        doo.trees[i].current_hit_points_percent = read_char(&ss);
        doo.trees[i].item_table_id = read_int(&ss);
        doo.trees[i].number_of_item_sets_dropped = read_int(&ss);
        doo.trees[i].id = read_int(&ss);
    }

    return doo;
}
