#pragma once 

#include <string>
#include <vector>

std::vector<std::string> splitStr(const std::string& str, const char delim);

size_t sysrandom(void* dst, size_t dstlen);