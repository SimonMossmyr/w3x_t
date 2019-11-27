#include "w3x_t.h"

imp_type imp_to_struct(std::string contents) {

    std::stringstream ss(contents);
    imp_type imp;

    imp.format_version = read_int(&ss);
    imp.n_imps = read_int(&ss);
    imp.imported_files.resize(imp.n_imps);
    for (int i = 0; i < imp.n_imps; i++) {
        byte_type flag = read_byte(&ss);
        if (flag == 5 || flag == 8) {
            imp.imported_files[i].prefix_path_with_map3mapImported = true;
        }
        imp.imported_files[i].path = read_string(&ss);
    }

    imp.unknown = read_byte(&ss);

    if (!ss.eof()) {    
        throw data_still_exists("war3map.imp");
    }

    return imp;
}
