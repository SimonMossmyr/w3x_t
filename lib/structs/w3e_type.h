class tileset {
    private:
        char value;
        std::map<char, std::string> tilesets = {
            {'A', "Ashenvale"},
            {'B', "Barrens"},
            {'C', "Felwood"},
            {'D', "Dungeon"},
            {'F', "LordaeronFall"},
            {'G', "Underground"},
            {'L', "LordaeronSummer"},
            {'N', "Northrend"},
            {'Q', "VillageFall"},
            {'V', "Village"},
            {'W', "LordaeronWinter"},
            {'X', "Dalaran"},
            {'Y', "Cityscape"},
            {'Z', "SunkenRuins"},
            {'I', "Icecrown"},
            {'J', "DalaranRuins"},
            {'O', "Outland"},
            {'K', "BlackCitadel"}
        };
    public:
        struct not_a_tileset : public std::exception {
            private:
                std::string message;
            public:
                not_a_tileset(char c) {
                    message = std::string("Character ") + c + std::string(" is not a valid tileset.");
                }

                const char* what() const throw () {
                    return message.c_str();
                }
        };

        tileset(char value) {
            for (std::map<char, std::string>::iterator it = tilesets.begin(); it != tilesets.end(); it++) {
                if (it->first == value) {
                    this->value = value;
                    return;
                }
            }
            throw not_a_tileset(value);
        };

        tileset() { tileset('A'); };

        char to_char() {
            return value;
        }

        std::string to_string() {
            return tilesets[value];
        }
};

struct w3e_type {
    warcraft_id file_id;
    int format_version;
    tileset main_tileset;
    bool custom_tileset;
    int n_ground_tilesets;
    std::vector<warcraft_id> ground_tilesets;
    int n_cliff_tilesets;
    std::vector<warcraft_id> cliff_tilesets;
    int map_width_plus_one;
    int map_height_plus_one;
    float center_offset_x;
    float center_offset_y;
    struct tilepoint_type {
        short ground_height;
        short water_height;
        struct flag_type {
            bool boundary_1;
            bool ramp;
            bool blight;
            bool water;
            bool boundary_2;
        } flag;
        int ground_texture_type;
        int ground_texture_variation;;
        int cliff_texture_type;
        int cliff_texture_variation;
        int layer_height;
    };
    std::vector<tilepoint_type> tilepoints;
    byte_type unknown;
};
