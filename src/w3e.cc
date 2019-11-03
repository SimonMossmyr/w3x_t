#include "W3JSON.h"

string w3e_to_json(string w3e_contents) {

  rapidjson::Document d;
  d.SetObject();

  stringstream ss(w3e_contents);

  /** File ID */
  char file_id[4 + 1];
  ss.read(file_id, 4);
  file_id[4] = '\0';

  rapidjson::Value v_file_id;
  v_file_id.SetString(rapidjson::StringRef(file_id));
  d.AddMember("file_id", v_file_id, d.GetAllocator());

  /** W3E format version */
  uint32_t w3e_format_version = -1;
  ss.read(reinterpret_cast<char *>(&w3e_format_version), sizeof(w3e_format_version));

  rapidjson::Value v_w3e_format_version;
  v_w3e_format_version.SetInt(w3e_format_version);
  d.AddMember("w3e_format_version", v_w3e_format_version, d.GetAllocator());

  /** Main tileset */
  char main_tileset;
  ss.get(main_tileset);

  /** Custom tileset flag */
  uint32_t custom_tileset = -1;
  ss.read(reinterpret_cast<char *>(&custom_tileset), sizeof(custom_tileset));

  rapidjson::Value v_custom_tileset;
  v_custom_tileset.SetBool(custom_tileset);
  d.AddMember("custom_tileset", v_custom_tileset, d.GetAllocator());

  /** Number of ground tilesets */
  uint32_t number_of_ground_tilesets_used = -1;
  ss.read(reinterpret_cast<char *>(&number_of_ground_tilesets_used), sizeof(number_of_ground_tilesets_used));

  rapidjson::Value v_number_of_ground_tilesets_used;
  v_number_of_ground_tilesets_used.SetInt(number_of_ground_tilesets_used);
  d.AddMember("number_of_ground_tilesets_used", v_number_of_ground_tilesets_used, d.GetAllocator());

  /** Ground tilesets */
  char ground_tilesets[number_of_ground_tilesets_used][5];
  rapidjson::Value v_ground_tilesets(rapidjson::kArrayType);
  for (int i = 0; i < number_of_ground_tilesets_used; i++) {
    ss.read(ground_tilesets[i], 4);
    ground_tilesets[i][4] = '\0';
    v_ground_tilesets.PushBack(rapidjson::Value().SetString(rapidjson::StringRef(ground_tilesets[i])), d.GetAllocator());
  }
  d.AddMember("ground_tilesets", v_ground_tilesets, d.GetAllocator());

  /** Number of cliff tilesets */
  uint32_t number_of_cliff_tilesets_used = -1;
  ss.read(reinterpret_cast<char *>(&number_of_cliff_tilesets_used), sizeof(number_of_cliff_tilesets_used));

  rapidjson::Value v_number_of_cliff_tilesets_used;
  v_number_of_cliff_tilesets_used.SetInt(number_of_cliff_tilesets_used);
  d.AddMember("number_of_cliff_tilesets_used", v_number_of_cliff_tilesets_used, d.GetAllocator());

  /** Cliff tilesets */
  char cliff_tilesets[number_of_cliff_tilesets_used][5];
  rapidjson::Value v_cliff_tilesets(rapidjson::kArrayType);
  for (int i = 0; i < number_of_cliff_tilesets_used; i++) {
    ss.read(cliff_tilesets[i], 4);
    cliff_tilesets[i][4] = '\0';
    v_cliff_tilesets.PushBack(rapidjson::Value().SetString(rapidjson::StringRef(cliff_tilesets[i])), d.GetAllocator());
  }
  d.AddMember("cliff_tilesets", v_cliff_tilesets, d.GetAllocator());

  /** Map width */
  uint32_t map_width_plus_one = -1;
  ss.read(reinterpret_cast<char *>(&map_width_plus_one), sizeof(map_width_plus_one));

  rapidjson::Value v_map_width_plus_one;
  v_map_width_plus_one.SetInt(map_width_plus_one);
  d.AddMember("map_width_plus_one", v_map_width_plus_one, d.GetAllocator());

  /** Map height */
  uint32_t map_height_plus_one = -1;
  ss.read(reinterpret_cast<char *>(&map_height_plus_one), sizeof(map_height_plus_one));

  rapidjson::Value v_map_height_plus_one;
  v_map_height_plus_one.SetInt(map_height_plus_one);
  d.AddMember("map_height_plus_one", v_map_height_plus_one, d.GetAllocator());

  /** Center offset X */
  float center_offset_x;
  ss.read(reinterpret_cast<char *>(&center_offset_x), sizeof(center_offset_x));

  rapidjson::Value v_center_offset_x;
  v_center_offset_x.SetInt(center_offset_x);
  d.AddMember("center_offset_x", v_center_offset_x, d.GetAllocator());

  /** Center offset Y */
  float center_offset_y;
  ss.read(reinterpret_cast<char *>(&center_offset_y), sizeof(center_offset_y));

  rapidjson::Value v_center_offset_y;
  v_center_offset_y.SetInt(center_offset_y);
  d.AddMember("center_offset_y", v_center_offset_y, d.GetAllocator());

  /** Tilepoint data */
  int number_of_tilepoints = (map_width_plus_one - 1)*(map_height_plus_one - 1);

  short ground_height[number_of_tilepoints];
  short water_level[number_of_tilepoints];
  short boundary_flag_1[number_of_tilepoints];
  short ramp_flag[number_of_tilepoints];
  short blight_flag[number_of_tilepoints];
  short water_flag[number_of_tilepoints];
  short boundary_flag_2[number_of_tilepoints];
  char ground_texture_type[number_of_tilepoints];
  char texture_detail[number_of_tilepoints];
  char cliff_texture_type[number_of_tilepoints];
  char layer_height[number_of_tilepoints];
  
  rapidjson::Value v_tilepoint_data(rapidjson::kArrayType);
  for (int i = 0; i < number_of_tilepoints; i++) {
    rapidjson::Value v_tilepoint(rapidjson::kObjectType);

    ss.read(reinterpret_cast<char *>(&ground_height[i]), sizeof(ground_height[i]));
    v_tilepoint.AddMember("ground_height", rapidjson::Value().SetInt(ground_height[i]), d.GetAllocator());

    short water_level_and_boundary_flag;
    ss.read(reinterpret_cast<char *>(&water_level_and_boundary_flag), sizeof(water_level_and_boundary_flag));
    water_level[i] = water_level_and_boundary_flag & 0x3FFF;
    v_tilepoint.AddMember("water_level", rapidjson::Value().SetInt(water_level[i]), d.GetAllocator());
    boundary_flag_1[i] = water_level_and_boundary_flag & 0xC000;
    v_tilepoint.AddMember("boundary_flag_1", rapidjson::Value().SetBool(boundary_flag_1[i]), d.GetAllocator());

    char flags;
    ss.read(reinterpret_cast<char *>(&flags), sizeof(flags));
    ramp_flag[i] = flags & 0x0010;
    v_tilepoint.AddMember("ramp_flag", rapidjson::Value().SetBool(ramp_flag[i]), d.GetAllocator());
    blight_flag[i] = flags & 0x0020;
    v_tilepoint.AddMember("blight_flag", rapidjson::Value().SetBool(blight_flag[i]), d.GetAllocator());
    water_flag[i] = flags & 0x0040;
    v_tilepoint.AddMember("water_flag", rapidjson::Value().SetBool(water_flag[i]), d.GetAllocator());
    boundary_flag_2[i] = flags & 0x0080;
    v_tilepoint.AddMember("boundary_flag_2", rapidjson::Value().SetBool(boundary_flag_2[i]), d.GetAllocator());

    ss.read(reinterpret_cast<char *>(&ground_texture_type[i]), sizeof(ground_texture_type[i]));
    v_tilepoint.AddMember("ground_texture_type", rapidjson::Value().SetInt(ground_texture_type[i]), d.GetAllocator());
    ss.read(reinterpret_cast<char *>(&texture_detail[i]), sizeof(texture_detail[i]));
    v_tilepoint.AddMember("texture_detail", rapidjson::Value().SetInt(texture_detail[i]), d.GetAllocator());
    ss.read(reinterpret_cast<char *>(&cliff_texture_type[i]), sizeof(cliff_texture_type[i]));
    v_tilepoint.AddMember("cliff_texture_type", rapidjson::Value().SetInt(cliff_texture_type[i]), d.GetAllocator());
    ss.read(reinterpret_cast<char *>(&layer_height[i]), sizeof(layer_height[i]));
    v_tilepoint.AddMember("layer_height", rapidjson::Value().SetInt(layer_height[i]), d.GetAllocator());

    v_tilepoint_data.PushBack(v_tilepoint, d.GetAllocator());
  }
  d.AddMember("tilepoint_data", v_tilepoint_data, d.GetAllocator());


  rapidjson::StringBuffer buffer;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
  writer.SetIndent(' ', 2);
  d.Accept(writer);

  return buffer.GetString();
}
