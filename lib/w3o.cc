#include "w3x_t.h"

modification_table_type read_modification_table(std::stringstream* ss, bool is_doodad_ability_or_upgrade) {
    modification_table_type mod;

    mod.n_objects = read_int(ss);
    mod.objects.resize(mod.n_objects);
    for (int i = 0; i < mod.n_objects; i++) {
        mod.objects[i].original_id = read_chars(ss, 4);
        mod.objects[i].new_id = read_chars(ss, 4);
        mod.objects[i].n_modifications = read_int(ss);
        mod.objects[i].modifications.resize(mod.objects[i].n_modifications);
        for (int j = 0; j < mod.objects[i].n_modifications; j++) {
            mod.objects[i].modifications[j].id = read_chars(ss, 4);
            mod.objects[i].modifications[j].type = read_int(ss);
            if (is_doodad_ability_or_upgrade) {
                mod.objects[i].modifications[j].level = read_int(ss);
                mod.objects[i].modifications[j].column = read_int(ss);
            }
            switch (mod.objects[i].modifications[j].type) {
                case W3O_TYPE_INTEGER:
                    mod.objects[i].modifications[j].value.integer = read_int(ss);
                    break;
                case W3O_TYPE_REAL:
                case W3O_TYPE_UREAL:
                    mod.objects[i].modifications[j].value.real = read_float(ss);
                    break;
                case W3O_TYPE_STRING:
                    mod.objects[i].modifications[j].value.str = read_string(ss);
                    break;
            }
            mod.objects[i].modifications[j].object_id = read_chars(ss, 4);
        }
    }

    return mod;
}

w3o_type w3o_to_struct(std::string contents, bool is_doodad_ability_or_upgrade, std::string file_name) {
    std::stringstream ss(contents);
    w3o_type w3o;

    w3o.file_version = read_int(&ss);
    w3o.original_table = read_modification_table(&ss, is_doodad_ability_or_upgrade);
    w3o.custom_table = read_modification_table(&ss, is_doodad_ability_or_upgrade);

    w3o.unknown = read_byte(&ss);

    if (!ss.eof()) {
        throw DataStillExistsException(file_name);
    }

    return w3o;
}
