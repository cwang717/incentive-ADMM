#include <sstream>
#include <fstream>

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

size_t sysrandom(void* dst, size_t dstlen)
{
    char* buffer = reinterpret_cast<char*>(dst);
    std::ifstream stream("/dev/urandom", std::ios_base::binary | std::ios_base::in);
    stream.read(buffer, dstlen);

    return dstlen;
}