struct w3r_type {
    int format_version;
    int n_regions;
    struct region_type {
        float left;
        float right;
        float bottom;
        float top;
        std::string name;
        int id;
        warcraft_id weather_effect_id;
        std::string ambient_sound;
        rgba_color_type color;
    };
    std::vector<region_type> regions;
    byte_type unknown;
};
