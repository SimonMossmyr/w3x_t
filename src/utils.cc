#include "main.h"

void warning(string message) {
    cout << "\033[1;33mWarning\033[0m: " << message << endl;
}

void error(string message) {
    cout << "\033[1;31mError\033[0m: " << message << endl;
    exit(1);
}
