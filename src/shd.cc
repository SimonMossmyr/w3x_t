#include "w3x_t.h"

shd_type shd_to_struct(string contents, int map_width, int map_height) {

    stringstream ss(contents);
    shd_type shd;

    int number_of_pixels = 16*map_width*map_height;
    shd.shadow.resize(number_of_pixels);
    for (int i = 0; i < number_of_pixels; i++) {
        char c;
        ss.get(c);
        if (c != (char)0 && c != (char)0xFF) {
            cout << "error: " << c << endl;
        }
        shd.shadow[i] = (bool)c;
    }

    return shd;
}