#include "w3x_t.h"

w3i_type w3i_to_struct(string contents) {
    stringstream ss(contents);
    w3i_type w3i;

    w3i.file_format_version = read_int(&ss);
    w3i.map_version = read_int(&ss);
    w3i.editor_version = read_int(&ss);

    w3i.name = read_string(&ss);
    w3i.author = read_string(&ss);
    w3i.description = read_string(&ss);
    w3i.recommended_players = read_string(&ss);

    for (int i = 0; i < 8; i++) {
        w3i.camera_bounds[i] = read_float(&ss);
    }

    for (int i = 0; i < 4; i++) {
        w3i.camera_bounds_complements[i] = read_int(&ss);
    }

    w3i.playable_area.width = read_int(&ss);
    w3i.playable_area.height = read_int(&ss);

    uint32_t flags = read_int(&ss);
    w3i.flags.hide_minimap_in_preview = (bool)(flags & 0x1);
    w3i.flags.modify_ally_priorities = (bool)(flags & 0x2);
    w3i.flags.melee_map = (bool)(flags & 0x4);
    w3i.flags.playable_map_size_was_large_and_has_never_been_reduced_to_medium = (bool)(flags & 0x8);
    w3i.flags.masked_area_are_partially_visible = (bool)(flags & 0x10);
    w3i.flags.fixed_player_Setting_for_custom_forces = (bool)(flags & 0x20);
    w3i.flags.use_custom.forces = (bool)(flags & 0x40);
    w3i.flags.use_custom.techtree = (bool)(flags & 0x80);
    w3i.flags.use_custom.abilities = (bool)(flags & 0x100);
    w3i.flags.use_custom.upgrades = (bool)(flags & 0x200);
    w3i.flags.map_properties_menu_opened_at_least_once_since_map_creation = (bool)(flags & 0x400);
    w3i.flags.show_water_waves.cliff_shores = (bool)(flags & 0x800);
    w3i.flags.show_water_waves.rolling_shores = (bool)(flags & 0x1000);
    w3i.flags.unknown_1 = (bool)(flags & 0x2000);
    w3i.flags.unknown_2 = (bool)(flags & 0x4000);
    w3i.flags.unknown_3 = (bool)(flags & 0x8000);

    w3i.main_ground_type = read_char(&ss);

    w3i.loading_screen_background_number = read_int(&ss);
    w3i.loading_screen.path = read_string(&ss);
    w3i.loading_screen.text = read_string(&ss);
    w3i.loading_screen.title = read_string(&ss);
    w3i.loading_screen.subtitle = read_string(&ss);

    w3i.used_game_data_set = read_int(&ss);
    
    w3i.prologue_screen.path = read_string(&ss);
    w3i.prologue_screen.text = read_string(&ss);
    w3i.prologue_screen.title = read_string(&ss);
    w3i.prologue_screen.subtitle = read_string(&ss);
    
    w3i.fog.style = read_int(&ss);
    w3i.fog.height.start = read_float(&ss);
    w3i.fog.height.end = read_float(&ss);
    w3i.fog.density = read_float(&ss);
    w3i.fog.color.red = read_byte(&ss);
    w3i.fog.color.green = read_byte(&ss);
    w3i.fog.color.blue = read_byte(&ss);
    w3i.fog.color.alpha = read_byte(&ss);

    w3i.global_weather_id = read_chars(&ss, 4);
    w3i.custom_sound_environment = read_string(&ss);
    w3i.tileset_id_of_custom_light_environment = read_char(&ss);
    w3i.custom_water_tinting.red = read_byte(&ss);
    w3i.custom_water_tinting.green = read_byte(&ss);
    w3i.custom_water_tinting.blue = read_byte(&ss);
    w3i.custom_water_tinting.alpha = read_byte(&ss);

    w3i.max_n_players = read_int(&ss);
    if (w3i.max_n_players > 0) {
        w3i.players.resize(w3i.max_n_players);
    }
    for (int i = 0; i < w3i.max_n_players; i++) {
        w3i.players[i].number = read_int(&ss);
        w3i.players[i].type = read_int(&ss);
        w3i.players[i].race = read_int(&ss);
        w3i.players[i].has_fixed_start_position = (bool)read_int(&ss);
        w3i.players[i].name = read_string(&ss);
        w3i.players[i].starting_location.x = read_float(&ss);
        w3i.players[i].starting_location.y = read_float(&ss);
        
        int low_ally_priorities = read_int(&ss);
        for (int j = 0; j < 32; j++) {
            w3i.players[i].low_ally_priorities_for_player[j] = (bool)((low_ally_priorities >> j) & 1);
        }
        
        int high_ally_priorities = read_int(&ss);
        for (int j = 0; j < 32; j++) {
            w3i.players[i].high_ally_priorities_for_player[j] = (bool)((high_ally_priorities >> j) & 1);
        }
    }

    w3i.max_n_forces = read_int(&ss);
    if (w3i.max_n_forces > 0) {
        w3i.forces.resize(w3i.max_n_forces);
    }
    for (int i = 0; i < w3i.max_n_forces; i++) {
        flags = read_int(&ss);
        w3i.forces[i].flags.allied = (bool)(flags & 0x1);
        w3i.forces[i].flags.allied_victory = (bool)(flags & 0x2);
        w3i.forces[i].flags.shared_vision = (bool)(flags & 0x4);
        w3i.forces[i].flags.shared_unit_control = (bool)(flags & 0x10);
        w3i.forces[i].flags.shared_advanced_unit_control = (bool)(flags & 0x20);

        int player_mask = read_int(&ss);
        for (int j = 0; j < 32; j++) {
            w3i.forces[i].player_is_in_this_force[j] = (bool)((player_mask >> j) & 1);
        }
        w3i.forces[i].name = read_string(&ss);
    }

    w3i.n_upgrade_availabilities = read_int(&ss);
    if (w3i.n_upgrade_availabilities > 0) {
        w3i.upgrade_availabilities.resize(w3i.n_upgrade_availabilities);
    }
    for (int i = 0; i < w3i.n_upgrade_availabilities; i++) {
        int player_mask = read_int(&ss);
        for (int j = 0; j < 32; j++) {
            w3i.upgrade_availabilities[i].applies_to_player[j] = (bool)((player_mask >> j) & 1);
        }
        w3i.upgrade_availabilities[i].id = read_chars(&ss, 4);
        w3i.upgrade_availabilities[i].level_minus_one_of_the_upgrade_for_which_the_availability_is_changed = read_int(&ss);
        
        int availability = read_int(&ss);
        switch (availability) {
            case 0:
                w3i.upgrade_availabilities[i].is_available = false;
                break;
            case 1:
                w3i.upgrade_availabilities[i].is_available = true;
                break;
            case 2:
                w3i.upgrade_availabilities[i].is_researched = true;
                break;
        }
    }

    w3i.n_tech_availabilities = read_int(&ss);
    if (w3i.n_tech_availabilities > 0) {
        w3i.tech_availabilities.resize(w3i.n_tech_availabilities);
    }
    for (int i = 0; i < w3i.n_tech_availabilities; i++) {
        int player_mask = read_int(&ss);
        for (int j = 0; j < 32; j++) {
            w3i.tech_availabilities[i].applies_to_player[j] = (bool)((player_mask >> j) & 1);
        }

        w3i.tech_availabilities[i].id = read_chars(&ss, 4);
    }

    w3i.n_random_unit_tables = read_int(&ss);
    if (w3i.n_random_unit_tables > 0) {
        w3i.random_unit_tables.resize(w3i.n_random_unit_tables);
    }
    for (int i = 0; i < w3i.n_random_unit_tables; i++) {
        w3i.random_unit_tables[i].n_random_groups = read_int(&ss);
        if (w3i.random_unit_tables[i].n_random_groups > 0) {
            w3i.random_unit_tables[i].random_groups.resize(w3i.random_unit_tables[i].n_random_groups);
        }
        for (int j = 0; j < w3i.random_unit_tables[i].n_random_groups; j++) {
            w3i.random_unit_tables[i].random_groups[j].number = read_int(&ss);
            w3i.random_unit_tables[i].random_groups[j].name = read_string(&ss);
            
            w3i.random_unit_tables[i].random_groups[j].n_positions = read_int(&ss);
            if (w3i.random_unit_tables[i].random_groups[j].n_positions > 0) {
                w3i.random_unit_tables[i].random_groups[j].positions.resize(w3i.random_unit_tables[i].random_groups[j].n_positions);
            }
            for (int k = 0; k < w3i.random_unit_tables[i].random_groups[j].n_positions; k++) {
                w3i.random_unit_tables[i].random_groups[j].positions[k] = read_int(&ss);
            }

            w3i.random_unit_tables[i].random_groups[j].n_widgets = read_int(&ss);
            if (w3i.random_unit_tables[i].random_groups[j].n_widgets > 0) {
                w3i.random_unit_tables[i].random_groups[j].random_widgets.resize(w3i.random_unit_tables[i].random_groups[j].n_widgets);
            }
            for (int k = 0; k < w3i.random_unit_tables[i].random_groups[j].n_widgets; k++) {
                w3i.random_unit_tables[i].random_groups[j].random_widgets[k].chance = read_int(&ss);
                w3i.random_unit_tables[i].random_groups[j].random_widgets[k].ids.resize(w3i.random_unit_tables[i].random_groups[j].n_positions);
                for (int l = 0; l < w3i.random_unit_tables[i].random_groups[j].n_positions; l++) {
                    w3i.random_unit_tables[i].random_groups[j].random_widgets[k].ids[l] = read_chars(&ss, 4);
                }
            }
        }
    }

    w3i.n_random_items_table_sets = read_int(&ss);
    if (w3i.n_random_items_table_sets > 0) {
        w3i.random_item_table_sets.resize(w3i.n_random_items_table_sets);
    }
    for (int i = 0; i < w3i.n_random_items_table_sets; i++) {
        w3i.random_item_table_sets[i].n_random_item_tables = read_int(&ss);
        if (w3i.random_item_table_sets[i].n_random_item_tables > 0) {
            w3i.random_item_table_sets[i].random_item_tables.resize(w3i.random_item_table_sets[i].n_random_item_tables);
        }
        for (int j = 0; j < w3i.random_item_table_sets[i].n_random_item_tables; j++) {
            w3i.random_item_table_sets[i].random_item_tables[j].number = read_int(&ss);
            w3i.random_item_table_sets[i].random_item_tables[j].name = read_string(&ss);
            
            w3i.random_item_table_sets[i].random_item_tables[j].n_item_sets= read_int(&ss);
            if (w3i.random_item_table_sets[i].random_item_tables[j].n_item_sets > 0) {
                w3i.random_item_table_sets[i].random_item_tables[j].item_sets.resize(w3i.random_item_table_sets[i].random_item_tables[j].n_item_sets);
            }
            for (int k = 0; k < w3i.random_item_table_sets[i].random_item_tables[j].n_item_sets; k++) {
                w3i.random_item_table_sets[i].random_item_tables[j].item_sets[k].n_items = read_int(&ss);
                if (w3i.random_item_table_sets[i].random_item_tables[j].item_sets[k].n_items > 0) {
                    w3i.random_item_table_sets[i].random_item_tables[j].item_sets[k].items.resize(w3i.random_item_table_sets[i].random_item_tables[j].item_sets[k].n_items);
                }
                for (int l = 0; l < w3i.random_item_table_sets[i].random_item_tables[j].item_sets[k].n_items; l++) {
                    w3i.random_item_table_sets[i].random_item_tables[j].item_sets[k].items[l].percentual_chance = read_int(&ss);
                    w3i.random_item_table_sets[i].random_item_tables[j].item_sets[k].items[l].id = read_chars(&ss, 4);
                }
            }
        }
    }

    w3i.unknown = read_byte(&ss);

    if (!ss.eof()) {
        throw DataStillExistsException("war3map.w3i");
    }

    return w3i;
}