#include "../lib/w3x_t.h"
#include <StormLib.h>
#include <CascLib.h>

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

void    warning                             (string message);
void    error                               (string message);
string  get_contents_from_mpq_file          (HANDLE hMpq, string file_name);
int     main                                (int argc, char* argv[]);
string  extract_triggerdata_txt_from_casc   (char* warcraft_iii_path);
