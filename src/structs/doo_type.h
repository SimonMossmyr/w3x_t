#include "utils.h"

struct w3do_type {
    string file_id;
    uint32_t format_version;
    uint32_t format_sub_version;
    uint32_t n_doodads;
    struct doodad_type {
        string type_id;
        uint32_t variation;
        position_type position;
        float rotation_angle;
        scale_type scale;
        bool visible;
        bool solid;
        byte_type current_hit_points_percent;
        uint32_t item_table_id;
        uint32_t n_item_sets_dropped;
        uint32_t id;
    };
    vector<doodad_type> doodads;
};

struct doo_type {
    w3do_type doodads;

    uint32_t special_doodads_format_version;
    uint32_t n_special_doodads;
    struct special_doodad_type {
        string type_id;
        position_type position;
    };
    vector<special_doodad_type> special_doodads;

    w3do_type trees;
};
