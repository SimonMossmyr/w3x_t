#include "utils.h"

struct units_doo_type {
    std::string file_id;
    int file_version;
    int file_sub_version;
    int n_units;
    struct unit_type {
        std::string type_id;
        int variation;
        position_type position;
        float rotation_angle;
        scale_type scale;
        byte_type unknown_1;
        int owning_player;
        short unknown_2;
        int hit_points;
        int mana_points;
        int dropped_item_sets_id;
        int n_item_sets_dropped;
        struct dropped_item_set_type {
            int size;
            struct item_type {
                std::string item_id;
                int chance_to_be_dropped;
            };
            std::vector<item_type> items;
        };
        std::vector<dropped_item_set_type> dropped_item_sets;
        int gold_amount;
        float target_acquisition;
        struct hero_stats_type {
            int level;
            int strength;
            int agility;
            int intelligence;
        } hero_stats;
        int n_items_in_inventory;
        struct item_in_inventory_type {
            int slot;
            std::string type_id;
        };
        std::vector<item_in_inventory_type> items_in_inventory;
        int n_modified_abilities;
        struct modified_ability_type {
            std::string ability_id;
            bool autocast_active;
            int level;
        };
        std::vector<modified_ability_type> modified_abilities;
        int random_flag;
        struct random_item_neutral_passive_type {
            byte_type level_high; // actually 24-bit number
            byte_type level_mid;
            byte_type level_low;
            byte_type item_class;
        } random_item_neutral_passive;
        struct random_unit_from_random_group_type {
            int unit_group;
            int position;
        } random_unit_from_random_group;
        struct random_unit_from_custom_table_type {
            int n_units;
            struct table_entry_type {
                std::string unit_id;
                int chance;
            };
            std::vector<table_entry_type> table;
        } random_unit_from_custom_table;
        int custom_color;
        int waygate;
        int id;
    };
    std::vector<unit_type> units;
    byte_type unknown;
};
