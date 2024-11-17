#pragma once

#include <ostream>
#include <string>

#include "version.h"

namespace hello {
std::string version();
std::ostream &greetings(std::ostream &out);
} // namespace hello
