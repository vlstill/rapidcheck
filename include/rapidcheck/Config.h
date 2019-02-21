#pragma once

namespace rc {

struct Config {
  long max_size = -1;
  long max_success = -1;
};

Config operator|( const Config &, const Config & );

}
