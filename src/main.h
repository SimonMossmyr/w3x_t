#include "../lib/w3x_t.h"
#include <StormLib.h>
#include <CascLib.h>

struct archive_file_does_not_exist : public std::exception {
    private:
        std::string message;
    public:
        archive_file_does_not_exist(std::string file_name) {
            message = file_name + " does not exist.";
        }
        const char* what() const throw () {
            return message.c_str();
        }
};

void    warning                             (std::string message);
void    error                               (std::string message);
std::string  get_contents_from_mpq_file          (HANDLE hMpq, std::string file_name);
int     main                                (int argc, char* argv[]);
std::string  extract_triggerdata_txt_from_casc   (char* warcraft_iii_path);
