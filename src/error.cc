#include "W3JSON.h"

void warning(string message) {
    cout << "\033[1;33mWarning\033[0m: " << message << " (Code " << GetLastError() << ")" << endl;
}

int error(string message) {
    cout << "\033[1;31mError\033[0m: " << message << " (Code " << GetLastError() << ")" << endl;
    return 1; 
}

int error(string message, int error_code) {
    SetLastError(error_code);
    return error(message);
}
