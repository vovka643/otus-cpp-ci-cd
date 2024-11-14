#pragma once

#include <ostream>
#include <string>

#include "version.h"

namespace hello {
std::ostream &greetings(std::ostream &out);

std::string version();
}
