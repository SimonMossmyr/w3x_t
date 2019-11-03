#include "W3JSON.h"

#define DEFAULT_CHAR_BUFFER_SIZE 512

/** Map settings flag indices */

using namespace std;

int read_and_interpret_w3x_header(char* archive_file_name, char* out_dir) {
    ifstream ifs;
    ifs.open(archive_file_name);
    if (!ifs.good()) {
        return 0;
    }

    /** File ID  */
    char file_id[4 + 1];
    ifs.read(file_id, 4);
    file_id[4] = '\0';

    ifs.ignore(4);

    /** Map name */
    char map_name[128];
    ifs.getline(map_name, 128, '\0');

    /** Map flags */
    uint32_t map_flags_raw_binary = 0;
    ifs.read(reinterpret_cast<char *>(&map_flags_raw_binary), sizeof(map_flags_raw_binary)); // black magic
    int map_flags[13];
    for (int i = 32-13; i < 32; i++) {
        map_flags[i-(32-13)] = (map_flags_raw_binary >> i-(32-13)) & 1;
    }

    /** Max players */
    uint32_t max_players = 0;
    ifs.read(reinterpret_cast<char*>(&max_players), sizeof(max_players));
    ifs.close();

    string json = header_to_json(string(file_id), string(map_name), map_flags, max_players);
    ofstream ofs;
    ofs.open(string(out_dir) + "header.json");
    ofs << json << endl;
    ofs.close();

    return 1;
}

int main(int argc, char* argv[])
{

    if (argc < 3) {
        cout << argv[0] << " Version " << W3Plus_VERSION_MAJOR << "." << W3Plus_VERSION_MINOR << endl;
        cout << "Usage: " << argv[0] << " <w3x-file> <output-directory>" << endl;
        return 1;
    }

    char* archive_file_name = argv[1];
    char* output_directory = argv[2];

    /** Read W3X Header */
    if(!read_and_interpret_w3x_header(archive_file_name, output_directory)) {
        return error("Could not read archive header.", 1);
    }

    /** Open w3x as MPQ archive */
    HANDLE hMpq = NULL;
    if(!SFileOpenArchive(archive_file_name, 0, MPQ_OPEN_READ_ONLY, &hMpq)) {
        return error("Archive could not be opened.");
    }

    /** Open archive listfile */
    HANDLE listfile_handle = NULL;
    if(!SFileOpenFileEx(hMpq, "(listfile)", SFILE_OPEN_FROM_MPQ, &listfile_handle)) {
        return error("Listfile could not be opened.");
    }

    /** Find size of listfile */
    DWORD size_of_listfile_high = -1;
    DWORD size_of_listfile = 0;
    size_of_listfile = SFileGetFileSize(listfile_handle, &size_of_listfile_high);
    if (size_of_listfile == SFILE_INVALID_SIZE || size_of_listfile_high != 0) {
        return error("Size of listfile could not be determined.");
    }

    /** Read contents of listfile */
    char listfile_contents[size_of_listfile + 1]; // extra byte for null termination
    DWORD number_of_chars_actually_read = 0;
    if(!SFileReadFile(listfile_handle, &listfile_contents, size_of_listfile, &number_of_chars_actually_read, NULL)) {
        return error("Could not read contents of listfile.");
    }
    listfile_contents[size_of_listfile] = '\0';

    /** Count number of files in listfile */
    int number_of_files = 0;
    for (int i = 0; i < size_of_listfile + 1; i++) {
        if (listfile_contents[i] == '\r' && listfile_contents[i+1] == '\n') {
            number_of_files += 1;
        }
    }

    /** Iterate through the listfile */
    string files[number_of_files];
    stringstream listfile_ss(listfile_contents);
    string filename_with_carriage_return;
    for (int i = 0; i < number_of_files; i++) {
        getline(listfile_ss, filename_with_carriage_return, '\n');
        stringstream filename_ss(filename_with_carriage_return);
        string file_name;
        getline(filename_ss, file_name, '\r');

        HANDLE file_handle = NULL;
        if (!SFileOpenFileEx(hMpq, file_name.c_str(), SFILE_OPEN_FROM_MPQ, &file_handle)) {
            return error("One of the files listed in the listfile could not be opened.");
        }

        DWORD size_of_file_high = -1;
        DWORD size_of_file = SFileGetFileSize(file_handle, &size_of_file_high);
        if (size_of_file == SFILE_INVALID_SIZE || size_of_file_high != 0) {
            return error("Size of one of the files could not be determined.");
        }

        char file_contents[size_of_file + 1];
        number_of_chars_actually_read = 0;
        if (!SFileReadFile(file_handle, &file_contents, size_of_file, &number_of_chars_actually_read, NULL)) {
            return error("Could not read contents of file.");
        }
        file_contents[size_of_file] = '\0';
        string contents = string(file_contents, number_of_chars_actually_read);

        string file_json;
        string out_file_name;
        if (file_name.compare("war3map.w3e") == 0) {
            file_json = w3e_to_json(contents);
            out_file_name = "w3e.json";
        }
        ofstream ofs;
        ofs.open(string(output_directory) + out_file_name);
        ofs << file_json;
        ofs.close();
    }



    return 0;
}
