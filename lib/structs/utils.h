#ifndef STRUCTS_H /** Include guard */
    #define STRUCTS_H

#include <string>
#include <vector>
#include <map>

struct data_still_exists : public std::exception {
    private:
        std::string message;
    public:
        data_still_exists(std::string file_name) {
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

class warcraft_id {
    private:
        std::string value;
    public:
        struct not_a_warcraft_id : public std::exception {
            private:
                std::string message;
            public:
                not_a_warcraft_id(std::string id) {
                    message = std::string("Expected string ") + id + std::string(" to be four characters long.");
                }

                const char* what() const throw () {
                    return message.c_str();
                }
        };

        warcraft_id(std::string value) {
            if (value.length() != 4) {
                throw not_a_warcraft_id(value);
            }
            this->value = value;
        };

        warcraft_id() {
            warcraft_id(std::string("\0\0\0\0", 4));
        }

        warcraft_id(std::stringstream* ss) {
            value = read_chars(ss, 4);
        }

        std::string to_string() {
            return value;
        }

        void write_to_ss(std::stringstream& ss) {
            write_chars(ss, value, 4);
        }
};

#endif
