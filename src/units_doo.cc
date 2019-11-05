#include "w3x_t.h"

units_doo_type units_doo_to_struct(string contents) {
    stringstream ss(contents);
    units_doo_type udoo;

    udoo.file_id = read_chars(&ss, 4);
    udoo.file_version = read_int(&ss);
    udoo.file_sub_version = read_int(&ss);
    udoo.number_of_units = read_int(&ss);

    udoo.units.resize(udoo.number_of_units);
    for (int i = 0; i < udoo.number_of_units; i++) {
        udoo.units[i].type_id = read_chars(&ss, 4);
        udoo.units[i].variation = read_int(&ss);
        udoo.units[i].position.x = read_float(&ss);
        udoo.units[i].position.y = read_float(&ss);
        udoo.units[i].position.z = read_float(&ss);
        udoo.units[i].rotation_angle = read_float(&ss);
        udoo.units[i].scale.x = read_float(&ss);
        udoo.units[i].scale.y = read_float(&ss);
        udoo.units[i].scale.z = read_float(&ss);

        byte_type flags = read_byte(&ss);
        udoo.units[i].visible = (bool)(flags & 1);
        udoo.units[i].solid = (bool)(flags & 2);

        udoo.units[i].owning_player = read_int(&ss);
        udoo.units[i].unknown_1 = read_byte(&ss);
        udoo.units[i].unknown_2 = read_byte(&ss);
        udoo.units[i].hit_points = read_int(&ss);
        udoo.units[i].mana_points = read_int(&ss);

        udoo.units[i].dropped_item_sets_id = read_int(&ss);
        udoo.units[i].number_of_item_sets_dropped = read_int(&ss);

        if (udoo.units[i].number_of_item_sets_dropped > 0) {
            udoo.units[i].dropped_item_sets.resize(udoo.units[i].number_of_item_sets_dropped);
        }
        for (int j = 0; j < udoo.units[i].number_of_item_sets_dropped; j++) {
            udoo.units[i].dropped_item_sets[j].size = read_int(&ss);
            if (udoo.units[i].dropped_item_sets[j].size > 0) {
                udoo.units[i].dropped_item_sets[j].items.resize(udoo.units[i].dropped_item_sets[j].size);
            }
            for (int k = 0; k < udoo.units[i].dropped_item_sets[j].size; k++) {
                udoo.units[i].dropped_item_sets[j].items[k].item_id = read_chars(&ss, 4);
                udoo.units[i].dropped_item_sets[j].items[k].chance_to_be_dropped = read_int(&ss);
            }
        }

        udoo.units[i].gold_amount = read_int(&ss);
        udoo.units[i].target_acquisition = read_float(&ss);

        udoo.units[i].hero_stats.level = read_int(&ss);
        udoo.units[i].hero_stats.strength = read_int(&ss);
        udoo.units[i].hero_stats.agility = read_int(&ss);
        udoo.units[i].hero_stats.intelligence = read_int(&ss);

        udoo.units[i].number_of_items_in_inventory = read_int(&ss);
        udoo.units[i].items_in_inventory.resize(udoo.units[i].number_of_items_in_inventory);
        for (int j = 0; i < udoo.units[i].number_of_items_in_inventory; j++) {
            udoo.units[i].items_in_inventory[j].slot = read_int(&ss);
            udoo.units[i].items_in_inventory[j].type_id = read_chars(&ss, 4);
        }

        udoo.units[i].number_of_modified_abilities = read_int(&ss);
        udoo.units[i].modified_abilities.resize(udoo.units[i].number_of_modified_abilities);
        for (int j = 0; j < udoo.units[i].number_of_modified_abilities; j++) {
            udoo.units[i].modified_abilities[j].ability_id = read_chars(&ss, 4);
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
                udoo.units[i].random_unit_from_custom_table.number_of_units = read_int(&ss);
                udoo.units[i].random_unit_from_custom_table.table.resize(udoo.units[i].random_unit_from_custom_table.number_of_units);
                for (int j = 0; j < udoo.units[i].random_unit_from_custom_table.number_of_units; j++) {
                    udoo.units[i].random_unit_from_custom_table.table[j].unit_id = read_chars(&ss, 4);
                    udoo.units[i].random_unit_from_custom_table.table[j].chance = read_int(&ss);
                }
                break;
        }

        udoo.units[i].color = read_int(&ss);
        udoo.units[i].waygate = read_int(&ss);
        udoo.units[i].id = read_int(&ss);
    }

    udoo.unknown = read_byte(&ss);

    if (!ss.eof()) {
        throw DataStillExistsException("war3mapUnits.doo");
    }

    return udoo;
}
