#include "main.h"

std::string get_contents_from_mpq_file(HANDLE hMpq, std::string file_name) {
    HANDLE file_handle;
    if (!SFileOpenFileEx(hMpq, file_name.c_str(), SFILE_OPEN_FROM_MPQ, &file_handle)) {
        throw ArchiveFileDoesNotExistException(file_name);
    }

    DWORD size_of_file_high = -1;
    DWORD size_of_file = SFileGetFileSize(file_handle, &size_of_file_high);
    if (size_of_file == SFILE_INVALID_SIZE || size_of_file_high != 0) {
        error("Size of one of the files could not be determined.");
        exit(1);
    }

    char file_contents[size_of_file];
    DWORD number_of_chars_actually_read = 0;
    if (!SFileReadFile(file_handle, &file_contents, size_of_file, &number_of_chars_actually_read, NULL)) {
        error("Could not read contents of file.");
        exit(1);
    }
    //file_contents[size_of_file] = '\0';
    return std::string(file_contents, number_of_chars_actually_read);
}

std::string extract_triggerdata_txt_from_casc(char* warcraft_iii_path) {
    HANDLE hStorage = NULL;        // Open storage handle
    HANDLE hFile  = NULL;          // Storage file handle
    HANDLE handle = NULL;          // Disk file handle

    if(!CascOpenStorage(warcraft_iii_path, 0, &hStorage))
        return "";

    if(!CascOpenFile(hStorage, "war3.w3mod:ui\\triggerdata.txt", 0, 0, &hFile))
        return "";

    char buffer[0x000FFFFF];
    DWORD chars_read;
    if (!CascReadFile(hFile, buffer, 0x000FFFFF, &chars_read))
        return "";

    return std::string(buffer, chars_read);
}

int main(int argc, char* argv[])
{

    if (argc < 3) {
        std::cout << argv[0] << " version " << W3JSON_VERSION_MAJOR << "." << W3JSON_VERSION_MINOR << "." << W3JSON_VERSION_PATCH << std::endl;
        std::cout << "usage: " << argv[0] << " <w3x-file>" << " <warcraft-iii-dir" << std::endl;
        std::cout << "       " << argv[0] << " <w3x-file>" << " <gamedata.txt" << std::endl;
        return 1;
    }

    char* archive_file_name = argv[1];

    std::string trigger_data_txt = extract_triggerdata_txt_from_casc(argv[2]);
    if (trigger_data_txt.compare("") == 0) {
        trigger_data_txt = std::string(argv[2]);
    }

    /** Open w3x as MPQ archive */
    HANDLE hMpq = NULL;
    if(!SFileOpenArchive(archive_file_name, 0, MPQ_OPEN_READ_ONLY, &hMpq)) {
        error("Archive could not be opened.");
    }

    /** Open archive listfile */
    HANDLE listfile_handle = NULL;
    if(!SFileOpenFileEx(hMpq, "(listfile)", SFILE_OPEN_FROM_MPQ, &listfile_handle)) {
        error("Listfile could not be opened.");
    }

    /** Find size of listfile */
    DWORD size_of_listfile_high = -1;
    DWORD size_of_listfile = 0;
    size_of_listfile = SFileGetFileSize(listfile_handle, &size_of_listfile_high);
    if (size_of_listfile == SFILE_INVALID_SIZE || size_of_listfile_high != 0) {
        error("Size of listfile could not be determined.");
    }

    /** Read contents of listfile */
    char listfile_contents[size_of_listfile + 1];
    DWORD number_of_chars_actually_read = 0;
    if(!SFileReadFile(listfile_handle, &listfile_contents, size_of_listfile, &number_of_chars_actually_read, NULL)) {
        error("Could not read contents of listfile.");
    }
    listfile_contents[size_of_listfile] = '\0';

    int map_width;
    int map_height;

    w3e_type w3e;
    shd_type shd;
    wpm_type wpm;
    doo_type doo;
    units_doo_type udoo;
    w3i_type w3i;
    wts_type wts;
    mmp_type mmp;
    w3o_type w3u;
    w3o_type w3t;
    w3o_type w3b;
    w3o_type w3d;
    w3o_type w3a;
    w3o_type w3h;
    w3o_type w3q;
    trigger_data_type trigger_data;
    wtg_type wtg;
    w3c_type w3c;
    w3r_type w3r;
    w3s_type w3s;
    wct_type wct;
    imp_type imp;

    try {
        w3e = w3e_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3e"));
        map_width = w3e.map_width_plus_one - 1;
        map_height = w3e.map_height_plus_one - 1;
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    try {
        shd = shd_to_struct(get_contents_from_mpq_file(hMpq, "war3map.shd"), map_width, map_height);
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    try {
        wpm = wpm_to_struct(get_contents_from_mpq_file(hMpq, "war3map.wpm"));
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    try {
        doo = doo_to_struct(get_contents_from_mpq_file(hMpq, "war3map.doo"));
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    try {
        udoo = units_doo_to_struct(get_contents_from_mpq_file(hMpq, "war3mapUnits.doo"));
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    try {
        w3i = w3i_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3i"));
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    try {
        wts = wts_to_struct(get_contents_from_mpq_file(hMpq, "war3map.wts"));
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    try {
        mmp = mmp_to_struct(get_contents_from_mpq_file(hMpq, "war3map.mmp"));
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    try {
        w3u = w3o_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3u"), false, "war3map.w3u");
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    try {
        w3t = w3o_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3t"), false, "war3map.w3t");
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    try {
        w3b = w3o_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3b"), false, "war3map.w3b");
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    try {
        w3d = w3o_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3d"), true, "war3map.w3d");
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    try {
        w3a = w3o_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3a"), true, "war3map.w3a");
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    try {
        w3h = w3o_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3h"), false, "war3map.w3h");
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    try {
        w3q = w3o_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3q"), true, "war3map.w3q");
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    try {
        trigger_data = trigger_data_to_struct(trigger_data_txt);
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    /*
    try {
        wtg = wtg_to_struct(get_contents_from_mpq_file(hMpq, "war3map.wtg"), trigger_data);
    }
    catch (std::exception& s) {
        warning(s.what());
    }
    */

    try {
        w3c = w3c_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3c"));
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    try {
        w3r = w3r_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3r"));
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    try {
        w3s = w3s_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3s"));
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    try {
        wct = wct_to_struct(get_contents_from_mpq_file(hMpq, "war3map.wct"));
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    try {
        imp = imp_to_struct(get_contents_from_mpq_file(hMpq, "war3map.imp"));
    }
    catch (std::exception& s) {
        warning(s.what());
    }

    return 0;
}
