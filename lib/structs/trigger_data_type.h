struct trigger_category_type {
    std::string display_text;
    std::string icon_image_file;
    bool flag;
};

struct trigger_type_type {
    int first_game_version;
    struct flag_type {
        bool can_be_global_variable;
        bool can_be_used_with_comparison_operators;
    } flag;
    std::string editor_display;
    std::string base_type;
    std::string import_type;
    bool treat_as_base_type;
};

struct trigger_type_defaults_type {
    std::string script_text;
    std::string display_text;
};

struct trigger_parameter_type {
    int first_game_version;
    std::string variable_type;
    std::string code_text;
    std::string display_text;
};

struct trigger_action_or_event_type {
    int first_game_version;
    std::vector<std::string> argument_types;
    std::vector<std::string> defaults;
    std::vector<std::string> limits;
    std::string category;
};

struct trigger_condition_type {
    int first_game_version;
    std::vector<std::string> argument_types;
    std::vector<std::string> defaults;
    std::string category;
    bool use_with_ai;
    struct ai_defaults_type {
        std::string compare_value_1;
        std::string operator_type;
        std::string compare_value_2;
    } ai_defaults;
};

struct trigger_call_type {
    int first_game_version;
    bool can_be_used_in_events;
    std::string return_type;
    std::vector<std::string> argument_types;
    std::vector<std::string> limits;
    std::vector<std::string> defaults;
    std::string category;
};

struct default_trigger_categories_type {
    int n_categories;
    std::vector<std::string> categories;
};

struct default_triggers_type {
    int n_triggers;
    struct trigger_type {
        std::string name;
        std::string comment;
        int category_number;
        int n_events;
        std::vector<std::string> events;
        int n_conditions;
        std::vector<std::string> conditions;
        int n_actions;
        std::vector<std::string> actions;
    };
    std::vector<trigger_type> triggers;
};

struct trigger_data_type {
    std::map<std::string, trigger_category_type> trigger_categories;
    std::map<std::string, trigger_type_type> trigger_types;
    std::map<std::string, trigger_type_defaults_type> trigger_types_defaults;
    std::map<std::string, trigger_parameter_type> trigger_parameters;
    std::map<std::string, trigger_action_or_event_type> trigger_events;
    std::map<std::string, trigger_condition_type> trigger_conditions;
    std::map<std::string, trigger_action_or_event_type> trigger_actions;
    std::map<std::string, trigger_call_type> trigger_calls;
    default_trigger_categories_type default_trigger_categories;
    default_triggers_type default_triggers;
};
