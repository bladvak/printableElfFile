#include "utils.hpp"

std::string asAddressHex(long long val){
    std::ostringstream ss;
    ss<<std::setw(16)<<std::setfill('0')<<std::hex<<val;
    return "0x" + ss.str();
}