#include "w3x_t.h"

#define DEFAULT_CHAR_BUFFER_SIZE 512

/** Map settings flag indices */

using namespace std;

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
        error("File does not exist.");
        exit(1);
    }

    DWORD size_of_file_high = -1;
    DWORD size_of_file = SFileGetFileSize(file_handle, &size_of_file_high);
    if (size_of_file == SFILE_INVALID_SIZE || size_of_file_high != 0) {
        error("Size of one of the files could not be determined.");
        exit(1);
    }

    char file_contents[size_of_file + 1];
    DWORD number_of_chars_actually_read = 0;
    if (!SFileReadFile(file_handle, &file_contents, size_of_file, &number_of_chars_actually_read, NULL)) {
        error("Could not read contents of file.");
        exit(1);
    }
    file_contents[size_of_file] = '\0';
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
        error("Could not read archive header.", 1);
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
    char listfile_contents[size_of_listfile + 1]; // extra byte for null termination
    DWORD number_of_chars_actually_read = 0;
    if(!SFileReadFile(listfile_handle, &listfile_contents, size_of_listfile, &number_of_chars_actually_read, NULL)) {
        error("Could not read contents of listfile.");
    }
    listfile_contents[size_of_listfile] = '\0';

    /** Count number of files in listfile */
    int number_of_files = 0;
    for (int i = 0; i < size_of_listfile + 1; i++) {
        if (listfile_contents[i] == '\r' && listfile_contents[i+1] == '\n') {
            number_of_files += 1;
        }
    }

    try {
        w3e_type w3e = w3e_to_struct(get_contents_from_mpq_file(hMpq, "war3map.w3e"));
        shd_type shd = shd_to_struct(get_contents_from_mpq_file(hMpq, "war3map.shd"), w3e.map_width_plus_one - 1, w3e.map_height_plus_one - 1);
        wpm_type wpm = wpm_to_struct(get_contents_from_mpq_file(hMpq, "war3map.wpm"));
        doo_type doo = doo_to_struct(get_contents_from_mpq_file(hMpq, "war3map.doo"));
    }
    catch (exception& s) {
        error(s.what());
    }

    return 0;
}
