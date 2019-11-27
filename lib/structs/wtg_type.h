struct parameter_type {
    int type;
    std::string value;
    bool has_sub_parameters;
    struct sub_parameter_type {
        int type;
        std::string name;
        bool begin_parameters;
        std::vector<parameter_type> parameters;
        int end_function;
    } sub_parameter;
    bool is_array;
    parameter_type* array_index_parameter;
};

struct eca_type {
    int type;
    int group_for_if_then_else;
    std::string name;
    bool is_enabled;
    std::vector<parameter_type> parameters;
    int n_child_ecas;
    std::vector<eca_type> child_ecas;
};

struct wtg_type {
    warcraft_id file_id;
    int format_version;
    int n_trigger_categories;
    struct trigger_category_type {
        int id;
        std::string name;
        bool is_comment;
    };
    std::vector<trigger_category_type> trigger_categories;
    int unknown;
    int n_variables;
    struct variable_type {
        std::string name;
        std::string type;
        int unknown;
        bool is_array;
        int array_size;
        bool is_initialized;
        std::string initial_value;
    };
    std::vector<variable_type> variables;
    int n_triggers;
    struct trigger_type {
        std::string name;
        std::string description;
        bool is_comment;
        bool is_enabled;
        bool is_custom;
        bool is_initially_off;
        bool run_on_initialization;
        int trigger_category_id;
        int n_eca;
        std::vector<eca_type> ecas;
    };
    std::vector<trigger_type> triggers;
    byte_type unknown_2;
};
