#include "utils.h"

struct parameter_type {
    int type;
    string value;
    bool has_sub_parameters;
    struct sub_parameter_type {
        int type;
        string name;
        bool begin_parameters;
        vector<parameter_type> parameters;
    };
    int unknown;
    bool is_array;
    int array_index;
};

struct eca_type {
    int type;
    int group_for_if_then_else;
    string name;
    bool is_enabled;
    vector<parameter_type> parameters;
    int n_child_ecas;
    vector<eca_type> child_ecas;
};

struct wtg_type {
    string file_id;
    int format_version;
    int n_trigger_categories;
    struct trigger_category_type {
        int id;
        string name;
        bool is_comment;
    };
    vector<trigger_category_type> trigger_categories;
    int unknown;
    int n_variables;
    struct variable_type {
        string name;
        string type;
        int unknown;
        bool is_array;
        int array_size;
        bool is_initialized;
        string initial_value;
    };
    vector<variable_type> variables;
    int n_triggers;
    struct trigger_type {
        string name;
        string description;
        bool is_enabled;
        bool is_custom;
        bool is_initially_off;
        bool run_on_initialization;
        int trigger_category_id;
        int n_eca;
        vector<eca_type> ecas;
    };
    vector<trigger_type> triggers;
};
