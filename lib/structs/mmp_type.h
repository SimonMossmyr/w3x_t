class icon {
    private:
        int type;
        std::map<int, std::string> types = {
            {0, "Gold mine"},
            {1, "House"},
            {2, "Player start"}
        };
    public:
        struct not_an_icon : public std::exception {
            private:
                std::string message;
            public:
                not_an_icon(int i) {
                    message = std::string("Integer ") + std::to_string(i) + std::string(" is not a valid minimap icon.");
                }

                const char* what() const throw () {
                    return message.c_str();
                }
        };

        icon() {};

        icon(int i) {
            for (std::map<int, std::string>::iterator it = types.begin(); it != types.end(); it++) {
                if (i == it->first) {
                    type = i;
                    return;
                }
            }

            throw not_an_icon(i);
        };

        icon(std::stringstream* ss) {
            icon(read_int(ss));
        };

        int value() { return type; };

        std::string to_string() { return types[type]; };
};

struct mmp_type {
    int format_version;
    int n_icons;
    struct icon_type {
        icon type;
        int x;
        int y;
        rgba_color_type color;
    };
    std::vector<icon_type> icons;
    byte_type unknown_2;
};
