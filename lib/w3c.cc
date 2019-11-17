#include "w3x_t.h"

w3c_type w3c_to_struct(string contents) {
    stringstream ss(contents);
    w3c_type w3c;

    w3c.file_version = read_int(&ss);
    w3c.n_cameras = read_int(&ss);

    w3c.cameras.resize(w3c.n_cameras);
    for (int i = 0; i < w3c.n_cameras; i++) {
        w3c.cameras[i].target_x = read_float(&ss);
        w3c.cameras[i].target_y = read_float(&ss);
        w3c.cameras[i].z_offset = read_float(&ss);
        w3c.cameras[i].rotation_angle = read_float(&ss);
        w3c.cameras[i].angle_of_attack = read_float(&ss);
        w3c.cameras[i].distance = read_float(&ss);
        w3c.cameras[i].roll = read_float(&ss);
        w3c.cameras[i].field_of_view = read_float(&ss);
        w3c.cameras[i].far_clipping = read_float(&ss);
        w3c.cameras[i].unknown = read_float(&ss);
        w3c.cameras[i].name = read_string(&ss);
    }

    w3c.unknown = read_byte(&ss);

    if (!ss.eof()) {    
        throw DataStillExistsException("war3map.w3c");
    }

    return w3c;
}
