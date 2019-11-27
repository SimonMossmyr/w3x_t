#include "w3x_t.h"

units_doo_type units_doo_to_struct(std::string contents) {
    std::stringstream ss(contents);
    units_doo_type udoo;

    udoo.file_id = warcraft_id(&ss);
    udoo.file_version = read_int(&ss);
    udoo.file_sub_version = read_int(&ss);
    udoo.n_units = read_int(&ss);

    udoo.units.resize(udoo.n_units);
    for (int i = 0; i < udoo.n_units; i++) {
        udoo.units[i].type_id = warcraft_id(&ss);
        udoo.units[i].variation = read_int(&ss);
        udoo.units[i].position.x = read_float(&ss);
        udoo.units[i].position.y = read_float(&ss);
        udoo.units[i].position.z = read_float(&ss);
        udoo.units[i].rotation_angle = read_float(&ss);
        udoo.units[i].scale.x = read_float(&ss);
        udoo.units[i].scale.y = read_float(&ss);
        udoo.units[i].scale.z = read_float(&ss);

        udoo.units[i].unknown_1 = read_byte(&ss);

        udoo.units[i].owning_player = read_int(&ss);
        udoo.units[i].unknown_2 = read_short(&ss);
        udoo.units[i].hit_points = read_int(&ss);
        udoo.units[i].mana_points = read_int(&ss);

        udoo.units[i].dropped_item_sets_id = read_int(&ss);
        udoo.units[i].n_item_sets_dropped = read_int(&ss);

        if (udoo.units[i].n_item_sets_dropped > 0) {
            udoo.units[i].dropped_item_sets.resize(udoo.units[i].n_item_sets_dropped);
        }
        for (int j = 0; j < udoo.units[i].n_item_sets_dropped; j++) {
            udoo.units[i].dropped_item_sets[j].size = read_int(&ss);
            if (udoo.units[i].dropped_item_sets[j].size > 0) {
                udoo.units[i].dropped_item_sets[j].items.resize(udoo.units[i].dropped_item_sets[j].size);
            }
            for (int k = 0; k < udoo.units[i].dropped_item_sets[j].size; k++) {
                udoo.units[i].dropped_item_sets[j].items[k].item_id = warcraft_id(&ss);
                udoo.units[i].dropped_item_sets[j].items[k].chance_to_be_dropped = read_int(&ss);
            }
        }

        udoo.units[i].gold_amount = read_int(&ss);
        udoo.units[i].target_acquisition = read_float(&ss);

        udoo.units[i].hero_stats.level = read_int(&ss);
        udoo.units[i].hero_stats.strength = read_int(&ss);
        udoo.units[i].hero_stats.agility = read_int(&ss);
        udoo.units[i].hero_stats.intelligence = read_int(&ss);

        udoo.units[i].n_items_in_inventory = read_int(&ss);
        udoo.units[i].items_in_inventory.resize(udoo.units[i].n_items_in_inventory);
        for (int j = 0; i < udoo.units[i].n_items_in_inventory; j++) {
            udoo.units[i].items_in_inventory[j].slot = read_int(&ss);
            udoo.units[i].items_in_inventory[j].type_id = warcraft_id(&ss);
        }

        udoo.units[i].n_modified_abilities = read_int(&ss);
        udoo.units[i].modified_abilities.resize(udoo.units[i].n_modified_abilities);
        for (int j = 0; j < udoo.units[i].n_modified_abilities; j++) {
            udoo.units[i].modified_abilities[j].ability_id = warcraft_id(&ss);
            udoo.units[i].modified_abilities[j].autocast_active = (bool)read_int(&ss);
            udoo.units[i].modified_abilities[j].level = read_int(&ss);
        }

        udoo.units[i].random_flag = read_int(&ss);
        switch (udoo.units[i].random_flag) {
            case 0:
                udoo.units[i].random_item_neutral_passive.level_high = read_byte(&ss);
                udoo.units[i].random_item_neutral_passive.level_mid = read_byte(&ss);
                udoo.units[i].random_item_neutral_passive.level_low = read_byte(&ss);
                udoo.units[i].random_item_neutral_passive.item_class = read_byte(&ss);
                break;
            case 1:
                udoo.units[i].random_unit_from_random_group.unit_group = read_int(&ss);
                udoo.units[i].random_unit_from_random_group.position = read_int(&ss);
                break;
            case 2:
                udoo.units[i].random_unit_from_custom_table.n_units = read_int(&ss);
                udoo.units[i].random_unit_from_custom_table.table.resize(udoo.units[i].random_unit_from_custom_table.n_units);
                for (int j = 0; j < udoo.units[i].random_unit_from_custom_table.n_units; j++) {
                    udoo.units[i].random_unit_from_custom_table.table[j].unit_id = warcraft_id(&ss);
                    udoo.units[i].random_unit_from_custom_table.table[j].chance = read_int(&ss);
                }
                break;
        }

        udoo.units[i].custom_color = read_int(&ss);
        udoo.units[i].waygate = read_int(&ss);
        udoo.units[i].id = read_int(&ss);
    }

    udoo.unknown = read_byte(&ss);

    if (!ss.eof()) {
        throw data_still_exists("war3mapUnits.doo");
    }

    return udoo;
}
