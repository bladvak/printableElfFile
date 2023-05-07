#ifndef UTILS_HPP
#define UTILS_HPP
#include <sstream>
#include <string>
#include <iomanip>
#include <unordered_map>


inline std::string intToStrHex(long long val){
    std::ostringstream ss;
    ss<<"0x"<<std::hex<<val;
    return ss.str();
}

std::string asAddressHex(long long val);

typedef std::pair<std::string, std::string> pr;

#endif