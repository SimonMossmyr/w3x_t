// TODO: Processing this takes a LONG time for files with a moderate
// amount of triggers. Probably the fault of std::string comparison. This
// interpreter should be rewritten using something other than a
// std::std::stringstream.

#include "w3x_t.h"

#define ECA_EVENT 0
#define ECA_CONDITION 1
#define ECA_ACTION 2

struct eca_not_defined : public std::exception {
    private:
        std::string message;
    public:
        eca_not_defined(std::string eca_name) {
            message = "ECA function \"" + eca_name + "\" in war3map.wtg could not be found in TriggerData.txt.";
        }
        const char* what() const throw () {
            return message.c_str();
        }
};

bool string_counts_as_parameter(std::string value) {    
    return
        value.compare("0") != 0 &&
        value.compare("1") != 0 &&
        value.compare("nothing") != 0 &&
        value.compare("") != 0;
}

int find_n_parameters(std::string name, trigger_data_type trigger_data) {
    int n_parameters = 0;
    if (trigger_data.trigger_events.find(name) != trigger_data.trigger_events.end()) {
        for (int i = 0; i < trigger_data.trigger_events[name].argument_types.size(); i++) {
            std::string argument_type = trigger_data.trigger_events[name].argument_types[i];
            if (string_counts_as_parameter(argument_type)) {
                n_parameters++;
            }
        }
    }
    else if (trigger_data.trigger_conditions.find(name) != trigger_data.trigger_conditions.end()) {
        for (int i = 0; i < trigger_data.trigger_conditions[name].argument_types.size(); i++) {
            std::string argument_type = trigger_data.trigger_conditions[name].argument_types[i];
            if (string_counts_as_parameter(argument_type)) {
                n_parameters++;
            }
        }
    }
    else if (trigger_data.trigger_actions.find(name) != trigger_data.trigger_actions.end()) {
        for (int i = 0; i < trigger_data.trigger_actions[name].argument_types.size(); i++) {
            std::string argument_type = trigger_data.trigger_actions[name].argument_types[i];
            if (string_counts_as_parameter(argument_type)) {
                n_parameters++;
            }
        }
    }
    else if (trigger_data.trigger_calls.find(name) != trigger_data.trigger_calls.end()) {
        for (int i = 0; i < trigger_data.trigger_calls[name].argument_types.size(); i++) {
            std::string argument_type = trigger_data.trigger_calls[name].argument_types[i];
            if (string_counts_as_parameter(argument_type)) {
                n_parameters++;
            }
        }
    }
    else {
        throw eca_not_defined(name);
    }

    return n_parameters;
}

parameter_type read_parameter(
    std::stringstream* ss,
    trigger_data_type trigger_data
) {
    parameter_type parameter;

    parameter.type = read_int(ss);
    parameter.value = read_string(ss);
    parameter.has_sub_parameters = read_bool(ss);
    if (parameter.has_sub_parameters) {
        parameter.sub_parameter.type = read_int(ss);
        parameter.sub_parameter.name = read_string(ss);
        parameter.sub_parameter.begin_parameters = read_bool(ss);

        int n_parameters = find_n_parameters(parameter.sub_parameter.name, trigger_data);
        parameter.sub_parameter.parameters.resize(n_parameters);
        for (int i = 0; i < n_parameters; i++) {
            parameter.sub_parameter.parameters[i] = read_parameter(
                ss,
                trigger_data
            );
        }
        parameter.sub_parameter.end_function = read_int(ss);
    }
    parameter.is_array = read_bool(ss);
    if (parameter.is_array) {
        parameter_type array_data = read_parameter(
            ss,
            trigger_data
        );
        parameter.array_index_parameter = &array_data;
    }

    return parameter;
}

std::vector<eca_type> read_ecas(std::stringstream* ss, int amount, bool is_child, trigger_data_type trigger_data) {
    std::vector<eca_type> ecas;
    ecas.resize(amount);

    for (int i = 0; i < amount; i++) {
        ecas[i].type = read_int(ss);
        if (is_child) {
            ecas[i].group_for_if_then_else = read_int(ss);
        }
        ecas[i].name = read_string(ss);
        ecas[i].is_enabled = read_bool(ss);

        int n_parameters = find_n_parameters(ecas[i].name, trigger_data);
        ecas[i].parameters.resize(n_parameters);
        for (int j = 0; j < n_parameters; j++) {
            ecas[i].parameters[j] = read_parameter(ss, trigger_data);
        }

        ecas[i].n_child_ecas = read_int(ss);
        ecas[i].child_ecas = read_ecas(ss, ecas[i].n_child_ecas, true, trigger_data);
    }

    return ecas;
}

wtg_type wtg_to_struct(std::string content, trigger_data_type trigger_data) {
    std::stringstream ss(content);
    wtg_type wtg;

    wtg.file_id = warcraft_id(&ss);
    wtg.format_version = read_int(&ss);
    
    wtg.n_trigger_categories = read_int(&ss);
    wtg.trigger_categories.resize(wtg.n_trigger_categories);
    for (int i = 0; i < wtg.n_trigger_categories; i++) {
        wtg.trigger_categories[i].id = read_int(&ss);
        wtg.trigger_categories[i].name = read_string(&ss);
        wtg.trigger_categories[i].is_comment = read_bool(&ss);
    }

    wtg.unknown = read_int(&ss);

    wtg.n_variables = read_int(&ss);
    wtg.variables.resize(wtg.n_variables);
    for (int i = 0; i < wtg.n_variables; i++) {
        wtg.variables[i].name = read_string(&ss);
        wtg.variables[i].type = read_string(&ss);
        wtg.variables[i].unknown = read_int(&ss);
        wtg.variables[i].is_array = read_bool(&ss);
        wtg.variables[i].array_size = read_int(&ss);
        wtg.variables[i].is_initialized = read_bool(&ss);
        wtg.variables[i].initial_value = read_string(&ss);
    }

    wtg.n_triggers = read_int(&ss);
    wtg.triggers.resize(wtg.n_triggers);
    for (int i = 0; i < wtg.n_triggers; i++) {
        wtg.triggers[i].name = read_string(&ss);
        wtg.triggers[i].description = read_string(&ss);
        wtg.triggers[i].is_comment = read_int(&ss);
        wtg.triggers[i].is_enabled = read_bool(&ss);
        wtg.triggers[i].is_custom = read_bool(&ss);
        wtg.triggers[i].is_initially_off = read_bool(&ss);
        wtg.triggers[i].run_on_initialization = read_bool(&ss);
        wtg.triggers[i].trigger_category_id = read_int(&ss);
        wtg.triggers[i].n_eca = read_int(&ss);
        wtg.triggers[i].ecas = read_ecas(&ss, wtg.triggers[i].n_eca, false, trigger_data);
    }

    wtg.unknown_2 = read_byte(&ss);

    if (!ss.eof()) {
        throw data_still_exists("war3map.wtg");
    }

    return wtg;
}
