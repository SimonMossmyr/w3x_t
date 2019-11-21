#include "utils.h"

struct modification_table_type {
    int n_objects;
    struct object_type {
        std::string original_id;
        std::string new_id;
        int n_modifications;
        struct modification_type {
            std::string id;
            int type;
            int level;
            int column;
            struct value_type {
                int integer;
                float real;
                std::string str;
            } value;
            std::string object_id;
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
