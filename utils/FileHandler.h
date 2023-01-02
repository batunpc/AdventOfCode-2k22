#pragma once
#include <iostream>

namespace sdds {

std::vector<std::string> read(const std::string &filename,
                              char delimiter = '\n');

} // namespace sdds