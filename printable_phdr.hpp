#ifndef PRINTABLE_PHDR_HPP
#define PRINTABLE_PHDR_HPP
#include <elf.h>
#include "utils.hpp"

namespace Phdr {
extern std::unordered_map<int, std::string> typeDict;

struct type{
    std::string operator()(Elf32_Phdr* );
    std::string operator()(Elf64_Phdr* );
};

struct flags{
    std::string operator()(Elf32_Phdr* );
    std::string operator()(Elf64_Phdr* );
};

struct offset{
    std::string operator()(Elf32_Phdr* );
    std::string operator()(Elf64_Phdr* );
};

struct vaddr{
    std::string operator()(Elf32_Phdr* );
    std::string operator()(Elf64_Phdr* );
};

struct paddr{
    std::string operator()(Elf32_Phdr* );
    std::string operator()(Elf64_Phdr* );
};

struct filesz{
    long operator()(Elf32_Phdr* );
    long operator()(Elf64_Phdr* );
};

struct memsz{
    long operator()(Elf32_Phdr* );
    long operator()(Elf64_Phdr* );
};

struct align{
    long operator()(Elf32_Phdr* );
    long operator()(Elf64_Phdr* );
};

}

#endif