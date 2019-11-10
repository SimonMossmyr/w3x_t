#include "utils.h"

struct units_doo_type {
    string file_id;
    uint32_t file_version;
    uint32_t file_sub_version;
    uint32_t n_units;
    struct unit_type {
        string type_id;
        uint32_t variation;
        position_type position;
        float rotation_angle;
        scale_type scale;
        bool visible;
        bool solid;
        uint32_t owning_player;
        unsigned short unknown_1;
        uint32_t hit_points;
        uint32_t mana_points;
        uint32_t dropped_item_sets_id;
        uint32_t n_item_sets_dropped;
        struct dropped_item_set_type {
            uint32_t size;
            struct item_type {
                string item_id;
                uint32_t chance_to_be_dropped;
            };
            vector<item_type> items;
        };
        vector<dropped_item_set_type> dropped_item_sets;
        uint32_t gold_amount;
        float target_acquisition;
        struct hero_stats_type {
            uint32_t level;
            uint32_t strength;
            uint32_t agility;
            uint32_t intelligence;
        } hero_stats;
        uint32_t n_items_in_inventory;
        struct item_in_inventory_type {
            uint32_t slot;
            string type_id;
        };
        vector<item_in_inventory_type> items_in_inventory;
        uint32_t n_modified_abilities;
        struct modified_ability_type {
            string ability_id;
            bool autocast_active;
            uint32_t level;
        };
        vector<modified_ability_type> modified_abilities;
        uint32_t random_flag;
        struct random_item_neutral_passive_type {
            byte_type level_high; // actually 24-bit number
            byte_type level_mid;
            byte_type level_low;
            byte_type item_class;
        } random_item_neutral_passive;
        struct random_unit_from_random_group_type {
            uint32_t unit_group;
            uint32_t position;
        } random_unit_from_random_group;
        struct random_unit_from_custom_table_type {
            uint32_t n_units;
            struct table_entry_type {
                string unit_id;
                uint32_t chance;
            };
            vector<table_entry_type> table;
        } random_unit_from_custom_table;
        uint32_t custom_color;
        uint32_t waygate;
        uint32_t id;
    };
    vector<unit_type> units;
    byte_type unknown_2;
};
