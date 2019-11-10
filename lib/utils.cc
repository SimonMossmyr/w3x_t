#include "w3x_t.h"

string read_string(stringstream* ss) {
    string s;
    char c;
    while (1) {
        ss->get(c);
        if (c == '\0') {
            break;
        }
        s += c;
    }
    return s;
}

string read_chars(stringstream* ss, int amount) {
    char buffer[amount];
    ss->read(buffer, amount);
    return string(buffer, amount);
}

int read_int(stringstream* ss) {
    int i;
    ss->read(reinterpret_cast<char *>(&i), sizeof(i));
    return i;
}

float read_float(stringstream* ss) {
    float i;
    ss->read(reinterpret_cast<char *>(&i), sizeof(i));
    return i;
}

short read_short(stringstream* ss) {
    short i;
    ss->read(reinterpret_cast<char *>(&i), sizeof(i));
    return i;
}

char read_char(stringstream* ss) {
    char i;
    ss->get(i);
    return i;
}

byte_type read_byte(stringstream* ss) {
    return (byte_type)read_char(ss);
}
