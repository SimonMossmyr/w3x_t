#include "W3JSON.h"

string header_to_json(string file_id, string map_name, int map_flags[], uint32_t max_players) {

    rapidjson::Document d;
    d.SetObject();
 
    rapidjson::Value file_id_value;
    file_id_value.SetString(rapidjson::StringRef(file_id.c_str()));
    d.AddMember("file_id", file_id_value, d.GetAllocator());

    rapidjson::Value map_name_value;
    map_name_value.SetString(rapidjson::StringRef(map_name.c_str()));
    d.AddMember("map_name", map_name_value, d.GetAllocator());

    for (int i = 0; i < 13; i++) {
        string key;
        switch (i) {
            case HEADER_FLAG_HIDE_MINIMAP_IN_PREVIEW_SCREENS:
                key = "hide_minimap_in_preview_screens";
                break;
            case HEADER_FLAG_MODIFY_ALLY_PRIORITIES:
                key = "modify_ally_priorities";
                break;
            case HEADER_FLAG_MELEE_MAP:
                key = "melee_map";
                break;
            case HEADER_FLAG_PLAYABLE_MAP_SIZE_WAS_LARGE_AND_HAS_NEVER_BEEN_REDUCED_TO_MEDIUM:
                key = "playable_map_size_was_large_and_has_never_been_reduced_to_medium";
                break;
            case HEADER_FLAG_MASKED_AREAS_ARE_PARTIALLY_VISIBLE:
                key = "masked_areas_are_partially_visible";
                break;
            case HEADER_FLAG_FIXED_PLAYER_SETTING_FOR_CUSTOM_FORCES:
                key = "fixed_player_setting_for_custom_forces";
                break;
            case HEADER_FLAG_USE_CUSTOM_FORCES:
                key = "use_custom_forces";
                break;
            case HEADER_FLAG_USE_CUSTOM_TECHTREE:
                key = "use_custom_techtree";
                break;
            case HEADER_FLAG_USE_CUSTOM_ABILITIES:
                key = "use_custom_abilities";
                break;
            case HEADER_FLAG_USE_CUSTOM_UPGRADES:
                key = "use_custom_upgrades";
                break;
            case HEADER_FLAG_MAP_PROPERTIES_MENU_OPENED_AT_LEAST_ONCE_SINCE_MAP_CREATION :
                key = "map_properties_menu_opened_at_least_once_since_map_creation";
                break;
            case HEADER_FLAG_SHOW_WATER_WAVES_ON_CLIFF_SHORES :
                key = "show_water_waves_on_cliff_shores";
                break;
            case HEADER_FLAG_SHOW_WATER_WAVES_ON_ROLLING_SHORES :
                key = "show_water_waves_on_rolling_shores";
                break;
            default:
                key = "fuck";
                break;
        }

        char key_buffer[256];
        int length = sprintf(key_buffer, "%s", key.c_str());

        rapidjson::Value actual_key;
        actual_key.SetString(key_buffer, length, d.GetAllocator());

        rapidjson::Value value;
        value.SetBool(map_flags[i]);

        d.AddMember(actual_key, value, d.GetAllocator());
    }

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    writer.SetIndent(' ', 2);
    d.Accept(writer);

    return buffer.GetString();
}