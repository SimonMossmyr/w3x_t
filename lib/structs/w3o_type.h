#include "utils.h"

struct modification_table_type {
    int n_objects;
    struct object_type {
        string original_id;
        string new_id;
        int n_modifications;
        struct modification_type {
            string id;
            int type;
            int level;
            int column;
            struct value_type {
                int integer;
                float real;
                string str;
            } value;
            string object_id;
        };
        vector<modification_type> modifications;
    };
    vector<object_type> objects;
};

struct w3o_type {
    int file_version;
    modification_table_type original_table;
    modification_table_type custom_table;
    byte_type unknown;
};
