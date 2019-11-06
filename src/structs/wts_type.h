#include "utils.h"

struct trigger_string_type {
    int number;
    string content;
};

struct wts_type {
    byte_type unknown_1;
    byte_type unknown_2;
    byte_type unknown_3;
    vector<trigger_string_type> trigger_strings;
};
