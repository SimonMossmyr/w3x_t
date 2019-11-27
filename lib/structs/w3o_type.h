struct modification_table_type {
    int n_objects;
    struct object_type {
        warcraft_id original_id;
        warcraft_id new_id;
        int n_modifications;
        struct modification_type {
            warcraft_id id;
            int type;
            int level;
            int column;
            struct value_type {
                int integer;
                float real;
                std::string str;
            } value;
            warcraft_id object_id;
        };
        std::vector<modification_type> modifications;
    };
    std::vector<object_type> objects;
};

struct w3o_type {
    int file_version;
    modification_table_type original_table;
    modification_table_type custom_table;
    byte_type unknown;
};
