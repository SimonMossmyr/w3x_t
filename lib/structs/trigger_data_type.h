#include "utils.h"

struct trigger_category_type {
    string display_text;
    string icon_image_file;
    bool flag;
};

struct trigger_type_type {
    int first_game_version;
    struct flag_type {
        bool can_be_global_variable;
        bool can_be_used_with_comparison_operators;
    } flag;
    string editor_display;
    string base_type;
    string import_type;
    bool treat_as_base_type;
};

struct trigger_type_defaults_type {
    string script_text;
    string display_text;
};

struct trigger_parameter_type {
    int first_game_version;
    string variable_type;
    string code_text;
    string display_text;
};

struct trigger_action_or_event_type {
    int first_game_version;
    vector<string> argument_types;
    vector<string> defaults;
    vector<string> limits;
    string category;
};

struct trigger_condition_type {
    int first_game_version;
    vector<string> argument_types;
    vector<string> defaults;
    string category;
    bool use_with_ai;
    struct ai_defaults_type {
        string compare_value_1;
        string operator_type;
        string compare_value_2;
    } ai_defaults;
};

struct trigger_call_type {
    int first_game_version;
    bool can_be_used_in_events;
    string return_type;
    vector<string> argument_types;
    vector<string> limits;
    vector<string> defaults;
    string category;
};

struct default_trigger_categories_type {
    int n_categories;
    vector<string> categories;
};

struct default_triggers_type {
    int n_triggers;
    struct trigger_type {
        string name;
        string comment;
        int category_number;
        int n_events;
        vector<string> events;
        int n_conditions;
        vector<string> conditions;
        int n_actions;
        vector<string> actions;
    };
    vector<trigger_type> triggers;
};

struct trigger_data_type {
    map<string, trigger_category_type> trigger_categories;
    map<string, trigger_type_type> trigger_types;
    map<string, trigger_type_defaults_type> trigger_types_defaults;
    map<string, trigger_parameter_type> trigger_parameters;
    map<string, trigger_action_or_event_type> trigger_events;
    map<string, trigger_condition_type> trigger_conditions;
    map<string, trigger_action_or_event_type> trigger_actions;
    map<string, trigger_call_type> trigger_calls;
    default_trigger_categories_type default_trigger_categories;
    default_triggers_type default_triggers;
};
