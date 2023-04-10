#ifndef PRINTABLESHDR32_H
#define PRINTABLESHDR32_H

#include "printableshdr.h"
#include <unordered_map>

class PrintableShdr32 : public PrintableShdr{
public:
PrintableShdr32(void* ptr);

virtual int name_index();
virtual pr type();
virtual pr flags();

virtual std::string addr();
virtual std::string offset();
virtual std::string size();

virtual int link();
virtual int info();

private:
Elf32_Shdr* shdr_ptr;
static std::unordered_map<int, std::string> s_type;

std::string intToStrHex(long long val);
//virtual addralign() =0;
//virtual entsize() = 0;

};

#endif