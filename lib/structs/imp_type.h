struct imp_type {
    int format_version;
    int n_imps;
    struct imp_file_type {
        bool prefix_path_with_map3mapImported;
        std::string path;
    };
    std::vector<imp_file_type> imported_files;

    byte_type unknown;
};
