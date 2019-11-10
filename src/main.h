#include "../lib/w3x_t.h"
#include <StormLib.h>

using namespace std;

struct ArchiveFileDoesNotExistException : public exception {
    private:
        string message;
    public:
        ArchiveFileDoesNotExistException(string file_name) {
            message = file_name + " does not exist.";
        }
        const char* what() const throw () {
            return message.c_str();
        }
};

void warning(string message);
void error(string message);
int     read_and_interpret_w3x_header   (char* archive_file_name);
string  get_contents_from_mpq_file      (HANDLE hMpq, string file_name);
int     main                            (int argc, char* argv[]);
