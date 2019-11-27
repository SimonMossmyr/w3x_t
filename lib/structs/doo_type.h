struct w3do_type {
    warcraft_id file_id;
    int format_version;
    int format_sub_version;
    int n_doodads;
    struct doodad_type {
        std::string type_id;
        int variation;
        position_type position;
        float rotation_angle;
        scale_type scale;
        bool visible;
        bool solid;
        byte_type current_hit_points_percent;
        int item_table_id;
        int n_item_sets_dropped;
        int id;
    };
    std::vector<doodad_type> doodads;
};

struct doo_type {
    w3do_type doodads;

    int special_doodads_format_version;
    int n_special_doodads;
    struct special_doodad_type {
        warcraft_id type_id;
        position_type position;
    };
    std::vector<special_doodad_type> special_doodads;

    w3do_type trees;
};
