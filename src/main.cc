#include "w3x_t.h"

#define DEFAULT_CHAR_BUFFER_SIZE 512

/** Map settings flag indices */

using namespace std;

struct ArchiveFileDoesNotExistException : public exception {
    private:
        string message;
    public:
        ArchiveFileDoesNotExistException(string file_name) {
            message = file_name + " does not exist.";
        }
        const char* what() const throw () {
            return message.c_str();
        }
};

int read_and_interpret_w3x_header(char* archive_file_name) {
    ifstream ifs;
    ifs.open(archive_file_name);
    if (!ifs.good()) {
        return 0;
    }

    char header_content[513];
    ifs.read(header_content, 512);
    header_content[512] = '\0';

    header_type header = header_to_struct(string(header_content, 512));

    return 1;
}

string get_contents_from_mpq_file(HANDLE hMpq, string file_name) {
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
    return string(file_contents, number_of_chars_actually_read);
}

int main(int argc, char* argv[])
{

    if (argc < 2) {
        cout << argv[0] << " Version " << W3JSON_VERSION_MAJOR << "." << W3JSON_VERSION_MINOR << "." << W3JSON_VERSION_PATCH << endl;
        cout << "Usage: " << argv[0] << " <w3x-file>" << endl;
        return 1;
    }

    char* archive_file_name = argv[1];

    /** Read W3X Header */
    if(!read_and_interpret_w3x_header(archive_file_name)) {
        error("Could not read archive header.");
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

    uint32_t map_width;
    uint32_t map_height;

    w3e_type w3e;
    shd_type shd;
    wpm_type wpm;
    doo_type doo;
    units_doo_type udoo;
    w3i_type w3i;
    wts_type wts;
    w3o_type w3u;
    w3o_type w3t;
    w3o_type w3b;
    w3o_type w3d;
    w3o_type w3a;
    w3o_type w3h;
    w3o_type w3q;

    try {
        w3e = w3e_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3e"));
        map_width = w3e.map_width_plus_one - 1;
        map_height = w3e.map_height_plus_one - 1;
    }
    catch (exception& s) {
        warning(s.what());
    }

    try {
        shd = shd_to_struct(get_contents_from_mpq_file(hMpq, "war3map.shd"), map_width, map_height);
    }
    catch (exception& s) {
        warning(s.what());
    }

    try {
        wpm = wpm_to_struct(get_contents_from_mpq_file(hMpq, "war3map.wpm"));
    }
    catch (exception& s) {
        warning(s.what());
    }

    try {
        doo = doo_to_struct(get_contents_from_mpq_file(hMpq, "war3map.doo"));
    }
    catch (exception& s) {
        warning(s.what());
    }

    try {
        udoo = units_doo_to_struct(get_contents_from_mpq_file(hMpq, "war3mapUnits.doo"));
    }
    catch (exception& s) {
        warning(s.what());
    }

    try {
        w3i = w3i_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3i"));
    }
    catch (exception& s) {
        warning(s.what());
    }

    try {
        wts = wts_to_struct(get_contents_from_mpq_file(hMpq, "war3map.wts"));
    }
    catch (exception& s) {
        warning(s.what());
    }

    try {
        w3u = w3o_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3u"), false, "war3map.w3u");
    }
    catch (exception& s) {
        warning(s.what());
    }

    try {
        w3t = w3o_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3t"), false, "war3map.w3t");
    }
    catch (exception& s) {
        warning(s.what());
    }

    try {
        w3b = w3o_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3b"), false, "war3map.w3b");
    }
    catch (exception& s) {
        warning(s.what());
    }

    try {
        w3d = w3o_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3d"), true, "war3map.w3d");
    }
    catch (exception& s) {
        warning(s.what());
    }

    try {
        w3a = w3o_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3a"), true, "war3map.w3a");
    }
    catch (exception& s) {
        warning(s.what());
    }

    try {
        w3h = w3o_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3h"), false, "war3map.w3h");
    }
    catch (exception& s) {
        warning(s.what());
    }

    try {
        w3q = w3o_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3q"), true, "war3map.w3q");
    }
    catch (exception& s) {
        warning(s.what());
    }

    return 0;
}
