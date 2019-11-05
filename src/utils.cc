#include "w3x_t.h"

string read_chars(stringstream* ss, int amount) {
    char buffer[amount + 1];
    ss->read(buffer, amount);
    buffer[amount] = '\0';
    return string(buffer);
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

byte_type read_byte(stringstream* ss) {
    byte_type i;
    ss->get(i);
    return i;
}

void warning(string message) {
    cout << "\033[1;33mWarning\033[0m: " << message << " (Code " << GetLastError() << ")" << endl;
}

int error(string message) {
    cout << "\033[1;31mError\033[0m: " << message << " (Code " << GetLastError() << ")" << endl;
    exit(1);
    return 1; 
}

int error(string message, int error_code) {
    SetLastError(error_code);
    return error(message);
}
