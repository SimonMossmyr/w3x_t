#ifndef STRUCTS_H /** Include guard */
    #define STRUCTS_H

#include <string>
#include <vector>
#include <map>

typedef unsigned char byte_type;

struct DataStillExistsException : public std::exception {
    private:
        std::string message;
    public:
        DataStillExistsException(std::string file_name) {
            message = file_name + " still contains data after being processed. Either file is corrupt or interpreter is incorrect.";
        }
        const char* what() const throw () {
            return message.c_str();
        }
};

struct position_type {
    float x;
    float y;
    float z;
};

struct scale_type {
    float x;
    float y;
    float z;
};

struct rgba_color_type {
    byte_type red;
    byte_type green;
    byte_type blue;
    byte_type alpha;
};

#endif
