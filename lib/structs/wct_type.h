#include "utils.h"

struct custom_text_trigger_type {
    int length;
    string contents;
};

struct wct_type {
    int format_version;
    string comment;
    custom_text_trigger_type ctt;
    int n_ctt;
    vector<custom_text_trigger_type> custom_text_triggers;
    byte_type unknown;
};
