#include "w3x_t.h"

wts_type wts_to_struct(string contents) {
    stringstream ss(contents);
    wts_type wts;

    wts.unknown_1 = read_byte(&ss);
    wts.unknown_2 = read_byte(&ss);
    wts.unknown_3 = read_byte(&ss);

    string line;
    while (!ss.eof()) {
        getline(ss, line);
        if (line.substr(0, 7).compare("STRING ") == 0) {
            int number = stoi(line.substr(7, line.length() - 8));
            getline(ss, line);

            string s;
            while (1) {
                getline(ss, line);
                if (line.substr(0,1).compare("}") == 0) {
                    break;
                }
                s += line;
            }

            trigger_string_type trgstr;
            trgstr.number = number;
            trgstr.content = s;
            wts.trigger_strings.push_back(trgstr);
        }
    }

    return wts;
}
