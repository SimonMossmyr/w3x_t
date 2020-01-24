class player_number {
    private:
        int number;
        std::map<int, std::string> player_name = {
            {0, "Player 0"},
            {1, "Player 1"},
            {2, "Player 2"},
            {3, "Player 3"},
            {4, "Player 4"},
            {5, "Player 5"},
            {6, "Player 6"},
            {7, "Player 7"},
            {8, "Player 8"},
            {9, "Player 9"},
            {10, "Player 10"},
            {11, "Player 11"},
            {12, "Player 12"},
            {13, "Player 13"},
            {14, "Player 14"},
            {15, "Player 15"},
            {16, "Player 16"},
            {17, "Player 17"},
            {18, "Player 18"},
            {19, "Player 19"},
            {20, "Player 20"},
            {21, "Player 21"},
            {22, "Player 22"},
            {23, "Player 23"},
            {24, "Neutral Hostile"},
            {25, "Neutral Passive"},
            {26, "Neutral Victim"},
            {27, "Neutral Extra"}
        };
    public:
        struct not_a_player : public std::exception {
            private:
                std::string message;
            public:
                not_a_player(int i) {
                    message = std::to_string(i) + std::string(" is not a valid player number.");
                }

                const char* what() const throw () {
                    return message.c_str();
                }
        };

        player_number() {};

        player_number(int i) {
            if (i >= 0 && i <= 27) {
                number = i;
            }
            else {
                throw not_a_player(i);
            }
        };

        player_number(std::stringstream* ss) {
            player_number(read_int(ss));
        }
};

struct units_doo_type {
    warcraft_id file_id;
    int file_version;
    int file_sub_version;
    int n_units;
    struct unit_type {
        warcraft_id type_id;
        int variation;
        position_type position;
        float rotation_angle;
        scale_type scale;
        byte_type unknown_1;
        player_number owning_player;
        short unknown_2;
        int hit_points;
        int mana_points;
        int dropped_item_sets_id;
        int n_item_sets_dropped;
        struct dropped_item_set_type {
            int size;
            struct item_type {
                warcraft_id item_id;
                int chance_to_be_dropped; // TODO: type cast
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
            int slot; // TODO: type cast
            warcraft_id type_id;
        };
        std::vector<item_in_inventory_type> items_in_inventory;
        int n_modified_abilities;
        struct modified_ability_type {
            warcraft_id ability_id;
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
                warcraft_id unit_id;
                int chance;
            };
            std::vector<table_entry_type> table;
        } random_unit_from_custom_table;
        int custom_color; // TODO: type cast
        int waygate;
        int id;
    };
    std::vector<unit_type> units;
    byte_type unknown;
};
