#include "w3x_t.h"

custom_text_trigger_type read_ctt(std::stringstream* ss) {
    custom_text_trigger_type ctt;
    ctt.length = read_int(ss);
    if (ctt.length > 0) {
        ctt.contents = read_string(ss);
    }
    return ctt;
}

wct_type wct_to_struct(std::string contents) {

    std::stringstream ss(contents);
    wct_type wct;

    wct.format_version = read_int(&ss);
    wct.comment = read_string(&ss);
    wct.ctt = read_ctt(&ss);
    
    wct.n_ctt = read_int(&ss);
    wct.custom_text_triggers.resize(wct.n_ctt);
    for (int i = 0; i < wct.n_ctt; i++) {
        wct.ctt = read_ctt(&ss);
    }

    wct.unknown = read_byte(&ss);

    if (!ss.eof()) {    
        throw DataStillExistsException("war3map.wct");
    }

    return wct;
}
