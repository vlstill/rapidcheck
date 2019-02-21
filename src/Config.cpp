#include "rapidcheck/Config.h"

namespace rc {

Config operator|( const Config &a, const Config &b ) {
    Config c;
    c.max_size = b.max_size >= 0 ? b.max_size : a.max_size;
    c.max_success = b.max_success >= 0 ? b.max_success : a.max_success;
    return c;
}

}
