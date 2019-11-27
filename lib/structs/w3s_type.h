struct w3s_type {
    int format_version;
    int n_sounds;
    struct sound_type {
        std::string id;
        std::string file;
        std::string eax_effect;
        struct flags_type {
            bool looping;
            bool is_3d;
            bool stop_when_out_of_range;
            bool music;
            bool unknown;
        } flags;
        int fade_in_rate;
        int fade_out_rate;
        int volume;
        float pitch;
        float unknown_1;
        int unknown_2;
        int channel;
        float min_distance;
        float max_distance;
        float distance_cutoff;
        float unknown_3;
        float unknown_4;
        int unknown_5;
        float unknown_6;
        float unknown_7;
        float unknown_8;
    };
    std::vector<sound_type> sounds;
    byte_type unknown;
};
