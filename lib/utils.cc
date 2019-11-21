#include "w3x_t.h"
#include <iomanip>

std::string read_string(std::stringstream* ss) {
    std::string s;
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

std::string read_chars(std::stringstream* ss, int amount) {
    char buffer[amount];
    ss->read(buffer, amount);
    return std::string(buffer, amount);
}

int read_int(std::stringstream* ss) {
    int i;
    ss->read(reinterpret_cast<char *>(&i), sizeof(i));
    return i;
}

void write_int(std::stringstream& ss, int i) {
    int swapped = ((i>>24)&0xff) | ((i<<8)&0xff0000) | ((i>>8)&0xff00) | ((i<<24)&0xff000000);
    ss << std::setfill ('0') << std::setw(sizeof(int)*2) << std::hex << swapped;
}

bool read_bool(std::stringstream* ss) {
    return (bool)read_int(ss);
}

float read_float(std::stringstream* ss) {
    float i;
    ss->read(reinterpret_cast<char *>(&i), sizeof(i));
    return i;
}

short read_short(std::stringstream* ss) {
    short i;
    ss->read(reinterpret_cast<char *>(&i), sizeof(i));
    return i;
}

char read_char(std::stringstream* ss) {
    char i;
    ss->get(i);
    return i;
}

byte_type read_byte(std::stringstream* ss) {
    return (byte_type)read_char(ss);
}
