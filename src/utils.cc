#include "main.h"

void warning(std::string message) {
    std::cout << "\033[1;33mWarning\033[0m: " << message << std::endl;
}

void error(std::string message) {
    std::cout << "\033[1;31mError\033[0m: " << message << std::endl;
    exit(1);
}
