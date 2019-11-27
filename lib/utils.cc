#include "w3x_t.h"

std::string str_to_hex(std::string s) {
    std::stringstream ss;
    std::stringstream ss2(s);
    while(!ss2.eof()) {
        unsigned char c = read_char(&ss2);
        if ((int)c < 16) {
            ss << "0";
        }
        ss << std::hex << (int)c;
    }
    return ss.str();
}

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

//void write_string(std::stringstream& ss, std::string s) {

//}

std::string read_chars(std::stringstream* ss, int amount) {
    char buffer[amount];
    ss->read(buffer, amount);
    return std::string(buffer, amount);
}

void write_chars(std::stringstream& ss, std::string s, int amount) {
    ss << s.substr(0, amount);
}

int read_int(std::stringstream* ss) {
    int i;
    ss->read(reinterpret_cast<char *>(&i), sizeof(i));
    return i;
}

void write_int(std::stringstream& ss, int i) {
    ss.write(reinterpret_cast<char *>(&i), sizeof(i));
}

bool read_bool(std::stringstream* ss) {
    return (bool)read_int(ss);
}

void write_bool(std::stringstream& ss, bool b) {
    int i = (int)b;
    write_int(ss, i);
}

float read_float(std::stringstream* ss) {
    float i;
    ss->read(reinterpret_cast<char *>(&i), sizeof(i));
    return i;
}

void write_float(std::stringstream& ss, float* f) {
    char c[4];
    memcpy(c, f, sizeof(float));
    ss << c[0] << c[1] << c[2] << c[3];
}

short read_short(std::stringstream* ss) {
    short i;
    ss->read(reinterpret_cast<char *>(&i), sizeof(i));
    return i;
}

void write_short(std::stringstream& ss, short s) {
    ss.write(reinterpret_cast<char *>(&s), sizeof(s));
}

char read_char(std::stringstream* ss) {
    char i;
    ss->get(i);
    return i;
}

void write_char(std::stringstream& ss, char c) {
    ss << c;
}

byte_type read_byte(std::stringstream* ss) {
    return (byte_type)read_char(ss);
}

void write_byte(std::stringstream& ss, byte_type b) {
    ss << b;
}
