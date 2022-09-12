#include <sstream>

#include "../include/util.h"

std::vector<std::string> splitStr(const std::string& str, const char delim) {
    std::vector<std::string> result;
    std::istringstream ss;
    ss.str(str);
    std::string item;

    while (std::getline(ss, item, delim)) {
        result.push_back(move(item));
    }

    return result;
}
