struct w3c_type {
    int file_version;
    int n_cameras;
    struct camera_type {
        float target_x;
        float target_y;
        float z_offset;
        float rotation_angle; // TODO: type cast
        float angle_of_attack;
        float distance;
        float roll;
        float field_of_view;
        float far_clipping;
        float unknown;
        std::string name;
    };
    std::vector<camera_type> cameras;
    byte_type unknown;
};
