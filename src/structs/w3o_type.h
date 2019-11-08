#include "utils.h"

struct w3o_type {
    uint32_t file_version;
    struct modification_table_type {
        uint32_t n_objects;
        struct object_type {
            string original_id;
            string new_id;
            uint32_t n_modifications;
            struct modification_type {
                string id;
                uint32_t type;
                uint32_t level;
                uint32_t column;
                struct value_type {
                    uint32_t integer;
                    float real;
                    string str;
                } value;
                string object_id;
            };
            vector<modification_type> modifications;
        };
        vector<object_type> objects;
    } original_table, custom_table;
};
