struct trigger_string_type {
    int number;
    std::string content;
};

struct wts_type {
    byte_type unknown_1;
    byte_type unknown_2;
    byte_type unknown_3;
    std::vector<trigger_string_type> trigger_strings;
};
