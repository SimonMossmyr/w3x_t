#include "w3x_t.h"
#include <algorithm>

#define TRIGGER_CATEGORIES 0
#define TRIGGER_TYPES 1
#define TRIGGER_TYPE_DEFAULTS 2
#define TRIGGER_PARAMETERS 3
#define TRIGGER_EVENTS 4
#define TRIGGER_CONDITIONS 5
#define TRIGGER_ACTIONS 6
#define TRIGGER_CALLS 7
#define DEFAULT_TRIGGER_CATEGORIES 8
#define DEFAULT_TRIGGERS 9

string find_next_token_and_erase(string* line, string delimiter) {
    size_t pos = line->find(delimiter);
    if (pos == string::npos) {
        string s = *line;
        line->erase(0, line->length());
        return s;
    }
    else {
        string s = line->substr(0, pos);
        line->erase(0, pos + 1);
        return s;
    }
}

bool string_ends_with(string line, string ending) {
    return line.substr(line.length() - ending.length(), line.length()).compare(ending) == 0;
}

trigger_data_type trigger_data_to_struct(string contents) {
    stringstream ss(contents);
    trigger_data_type trigger_data;

    string delimiter = ",";
    int current_category = -1;
    string line;
    while (!ss.eof()) {
        getline(ss, line);

        if (line.substr(0,1).compare("[") == 0) {
            if (line.compare("[TriggerCategories]\r") == 0) {
                current_category = TRIGGER_CATEGORIES;
            }
            else if (line.compare("[TriggerTypes]\r") == 0) {
                current_category = TRIGGER_TYPES;
            }
            else if (line.compare("[TriggerTypeDefaults]\r") == 0) {
                current_category = TRIGGER_TYPE_DEFAULTS;
            }
            else if (line.compare("[TriggerParams]\r") == 0) {
                current_category = TRIGGER_PARAMETERS;
            }
            else if (line.compare("[TriggerEvents]\r") == 0) {
                current_category = TRIGGER_EVENTS;
            }
            else if (line.compare("[TriggerConditions]\r") == 0) {
                current_category = TRIGGER_CONDITIONS;
            }
            else if (line.compare("[TriggerActions]\r") == 0) {
                current_category = TRIGGER_ACTIONS;
            }
            else if (line.compare("[TriggerCalls]\r") == 0) {
                current_category = TRIGGER_CALLS;
            }
            else if (line.compare("[DefaultTriggerCategories]\r") == 0) {
                current_category = DEFAULT_TRIGGER_CATEGORIES;
            }
            else if (line.compare("[DefaultTriggers]\r") == 0) {
                current_category = DEFAULT_TRIGGERS;
            }
        }
        else if (line.substr(0,2).compare("//") != 0 && line.compare("\r") != 0) {
            string key = find_next_token_and_erase(&line, "=");
            switch (current_category) {
                case TRIGGER_CATEGORIES:
                    {
                        trigger_category_type trigger_category;
                        trigger_category.display_text = find_next_token_and_erase(&line, delimiter);
                        trigger_category.icon_image_file = find_next_token_and_erase(&line, delimiter);
                        if (line.length() != 0) {
                            trigger_category.flag = (bool)stoi(find_next_token_and_erase(&line, delimiter));
                        }
                        trigger_data.trigger_categories[key] = trigger_category;
                    }
                    break;
                
                case TRIGGER_TYPES:
                    {
                        trigger_type_type trigger_type;
                        trigger_type.first_game_version = stoi(find_next_token_and_erase(&line, delimiter));
                        trigger_type.flag.can_be_global_variable = stoi(find_next_token_and_erase(&line, delimiter));
                        trigger_type.flag.can_be_used_with_comparison_operators = stoi(find_next_token_and_erase(&line, delimiter));
                        trigger_type.editor_display = find_next_token_and_erase(&line, delimiter);
                        if (line.length() != 0) {
                            trigger_type.base_type = find_next_token_and_erase(&line, delimiter);
                        }
                        if (line.length() != 0) {
                            trigger_type.import_type = find_next_token_and_erase(&line, delimiter);
                        }
                        if (line.length() != 0) {
                            trigger_type.treat_as_base_type = (bool)stoi(find_next_token_and_erase(&line, delimiter));
                        }
                        trigger_data.trigger_types[key] = trigger_type;
                    }
                    break;

                case TRIGGER_TYPE_DEFAULTS:
                    {
                        trigger_type_defaults_type trigger_type_defaults;
                        trigger_type_defaults.script_text = find_next_token_and_erase(&line, delimiter);
                        if (line.length() != 0) {
                            trigger_type_defaults.display_text = find_next_token_and_erase(&line, delimiter);
                        }
                        trigger_data.trigger_types_defaults[key] = trigger_type_defaults;
                    }
                    break;

                case TRIGGER_PARAMETERS:
                    {
                        trigger_parameter_type trigger_parameters;
                        trigger_parameters.first_game_version = stoi(find_next_token_and_erase(&line, delimiter));
                        trigger_parameters.variable_type = find_next_token_and_erase(&line, delimiter);
                        trigger_parameters.code_text = find_next_token_and_erase(&line, delimiter);
                        trigger_parameters.display_text = find_next_token_and_erase(&line, delimiter);
                        trigger_data.trigger_parameters[key] = trigger_parameters;
                    }
                    break;

                case TRIGGER_EVENTS:
                    {
                        trigger_action_or_event_type trigger_events;
                        trigger_events.first_game_version = stoi(find_next_token_and_erase(&line, delimiter));
                        while (line.length() != 0) {
                            string token = find_next_token_and_erase(&line, delimiter);
                            while (token[token.length() - 1] == '\r' || token[token.length() - 1] == '\n') {
                                token.erase(token.length() - 1);
                            }
                            trigger_events.argument_types.push_back(token);
                            

                        }
                        while (true) {
                            getline(ss, line);
                            if (line.substr(0,1).compare("_") == 0) {
                                string name = find_next_token_and_erase(&line, "=");
                                if (string_ends_with(name, "Defaults")) {
                                    while (line.length() != 0) {
                                        trigger_events.defaults.push_back(find_next_token_and_erase(&line, delimiter));
                                    }
                                }
                                else if (string_ends_with(name, "Limits")) {
                                    while (line.length() != 0) {
                                        trigger_events.limits.push_back(find_next_token_and_erase(&line, delimiter));
                                    }
                                }
                                else if (string_ends_with(name, "Category")) {
                                    trigger_events.category = find_next_token_and_erase(&line, delimiter);
                                }
                            }
                            else {
                                break;
                            }
                        }
                        trigger_data.trigger_events[key] = trigger_events;
                    }
                    break;

                case TRIGGER_CONDITIONS:
                    {
                        trigger_condition_type trigger_conditions;
                        trigger_conditions.first_game_version = stoi(find_next_token_and_erase(&line, delimiter));
                        while (line.length() != 0) {
                            string token = find_next_token_and_erase(&line, delimiter);
                            while (token[token.length() - 1] == '\r' || token[token.length() - 1] == '\n') {
                                token.erase(token.length() - 1);
                            }
                            trigger_conditions.argument_types.push_back(token);
                        }
                        while (true) {
                            getline(ss, line);
                            if (line.substr(0,1).compare("_") == 0) {
                                string name = find_next_token_and_erase(&line, "=");
                                if (string_ends_with(name, "AIDefaults")) {
                                    trigger_conditions.ai_defaults.compare_value_1 = find_next_token_and_erase(&line, delimiter);
                                    trigger_conditions.ai_defaults.operator_type = find_next_token_and_erase(&line, delimiter);
                                    trigger_conditions.ai_defaults.compare_value_2 = find_next_token_and_erase(&line, delimiter);
                                }
                                else if (string_ends_with(name, "Defaults")) {
                                    while (line.length() != 0) {
                                        trigger_conditions.defaults.push_back(find_next_token_and_erase(&line, delimiter));
                                    }
                                }
                                else if (string_ends_with(name, "Category")) {
                                    trigger_conditions.category = find_next_token_and_erase(&line, delimiter);
                                }
                                else if (string_ends_with(name, "UseWithAI")) {
                                    trigger_conditions.use_with_ai = (bool)stoi(find_next_token_and_erase(&line, delimiter));
                                }
                            }
                            else {
                                break;
                            }
                        }
                        trigger_data.trigger_conditions[key] = trigger_conditions;
                    }
                    break;

                case TRIGGER_ACTIONS:
                    {
                        trigger_action_or_event_type trigger_actions;
                        trigger_actions.first_game_version = stoi(find_next_token_and_erase(&line, delimiter));
                        while (line.length() != 0) {
                            string token = find_next_token_and_erase(&line, delimiter);
                            while (token[token.length() - 1] == '\r' || token[token.length() - 1] == '\n') {
                                token.erase(token.length() - 1);
                            }
                            trigger_actions.argument_types.push_back(token);
                        }
                        while (true) {
                            getline(ss, line);
                            if (line.substr(0,1).compare("_") == 0) {
                                string name = find_next_token_and_erase(&line, "=");
                                if (string_ends_with(name, "Defaults")) {
                                    while (line.length() != 0) {
                                        trigger_actions.defaults.push_back(find_next_token_and_erase(&line, delimiter));
                                    }
                                }
                                else if (string_ends_with(name, "Limits")) {
                                    while (line.length() != 0) {
                                        trigger_actions.limits.push_back(find_next_token_and_erase(&line, delimiter));
                                    }
                                }
                                else if (string_ends_with(name, "Category")) {
                                    trigger_actions.category = find_next_token_and_erase(&line, delimiter);
                                }
                            }
                            else {
                                break;
                            }
                        }
                        trigger_data.trigger_actions[key] = trigger_actions;
                    }
                    break;

                case TRIGGER_CALLS:
                    {
                        trigger_call_type trigger_call;
                        trigger_call.first_game_version = stoi(find_next_token_and_erase(&line, delimiter));
                        trigger_call.can_be_used_in_events = (bool)stoi(find_next_token_and_erase(&line, delimiter));
                        trigger_call.return_type = find_next_token_and_erase(&line, delimiter);
                        while (line.length() != 0) {
                            string token = find_next_token_and_erase(&line, delimiter);
                            while (token[token.length() - 1] == '\r' || token[token.length() - 1] == '\n') {
                                token.erase(token.length() - 1);
                            }
                            trigger_call.argument_types.push_back(token);
                        }
                        while (true) {
                            getline(ss, line);
                            if (line.substr(0,1).compare("_") == 0) {
                                string name = find_next_token_and_erase(&line, "=");
                                if (string_ends_with(name, "Defaults")) {
                                    while (line.length() != 0) {
                                        trigger_call.defaults.push_back(find_next_token_and_erase(&line, delimiter));
                                    }
                                }
                                else if (string_ends_with(name, "Limits")) {
                                    while (line.length() != 0) {
                                        trigger_call.limits.push_back(find_next_token_and_erase(&line, delimiter));
                                    }
                                }
                                else if (string_ends_with(name, "CATEGORY")) {
                                    trigger_call.category = find_next_token_and_erase(&line, delimiter);
                                }
                            }
                            else {
                                break;
                            }
                        }
                        trigger_data.trigger_calls[key] = trigger_call;
                    }
                    break;

                case DEFAULT_TRIGGER_CATEGORIES:
                    {
                        default_trigger_categories_type default_trigger_categories;
                        default_trigger_categories.n_categories = stoi(line);
                        
                        int number_of_categories_read_from_file = 0;
                        while(number_of_categories_read_from_file < default_trigger_categories.n_categories) {
                            getline(ss, line);
                            if (line.substr(0,2).compare("//") != 0 && line.compare("\r") != 0) {
                                find_next_token_and_erase(&line, "=");
                                default_trigger_categories.categories.push_back(find_next_token_and_erase(&line, delimiter));
                                number_of_categories_read_from_file++;
                            }
                        }
                        
                        trigger_data.default_trigger_categories = default_trigger_categories;
                    }
                    break;

                case DEFAULT_TRIGGERS:
                    {
                        if (key.compare("NumTriggers") == 0) {
                            trigger_data.default_triggers.n_triggers = stoi(find_next_token_and_erase(&line, delimiter));
                            trigger_data.default_triggers.triggers.resize(trigger_data.default_triggers.n_triggers);
                        }
                        else if (key.substr(0,7).compare("Trigger") == 0) {
                            int index = stoi(key.substr(7, 2)) - 1;
                            if (key.substr(9, key.length() - 9).compare("Name") == 0) {
                                trigger_data.default_triggers.triggers[index].name = line;
                            }
                            else if (key.substr(9, key.length() - 9).compare("Comment") == 0) {
                                trigger_data.default_triggers.triggers[index].comment = line;
                            }
                            else if (key.substr(9, key.length() - 9).compare("Category") == 0) {
                                trigger_data.default_triggers.triggers[index].comment = stoi(line);
                            }
                            else if (key.substr(9, 5).compare("Event") == 0) {
                                if (key.substr(9, key.length() - 9).compare("Events") == 0) {
                                    trigger_data.default_triggers.triggers[index].n_events = stoi(line);
                                    trigger_data.default_triggers.triggers[index].events.resize(trigger_data.default_triggers.triggers[index].n_events);
                                }
                                else {
                                    int event_index = stoi(key.substr(key.length() - 2, 2)) - 1;
                                    trigger_data.default_triggers.triggers[index].events[event_index] = line;
                                }
                            }
                            else if (key.substr(9, 9).compare("Condition") == 0) {
                                if (key.substr(9, key.length() - 9).compare("Conditions") == 0) {
                                    trigger_data.default_triggers.triggers[index].n_conditions = stoi(line);
                                    trigger_data.default_triggers.triggers[index].conditions.resize(trigger_data.default_triggers.triggers[index].n_conditions);
                                }
                                else {
                                    int condition_index = stoi(key.substr(key.length() - 2, 2)) - 1;
                                    trigger_data.default_triggers.triggers[index].conditions[condition_index] = line;
                                }
                            }
                            else if (key.substr(9, 6).compare("Action") == 0) {
                                if (key.substr(9, key.length() - 9).compare("Actions") == 0) {
                                    trigger_data.default_triggers.triggers[index].n_actions = stoi(line);
                                    trigger_data.default_triggers.triggers[index].actions.resize(trigger_data.default_triggers.triggers[index].n_actions);
                                }
                                else {
                                    int action_index = stoi(key.substr(key.length() - 2, 2)) - 1;
                                    trigger_data.default_triggers.triggers[index].actions[action_index] = line;
                                }
                            }
                        }
                    }
                    break;
            }
        }
    }

    return trigger_data;
}
