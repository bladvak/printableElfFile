#pragma once

#include <sstream>
#include <iostream>
#include <elf.h>
#include <unordered_map>
#include <string>
#include "utils.hpp"



extern std::unordered_map<int, std::string> machineDict;

namespace Ehdr{

struct magic{
    std::string operator()(Elf32_Ehdr* );
    std::string operator()(Elf64_Ehdr* );
};

struct ident_class{
    std::string operator()(Elf32_Ehdr* );
    std::string operator()(Elf64_Ehdr* );
};

struct ident_data{
    std::string operator()(Elf32_Ehdr* );
    std::string operator()(Elf64_Ehdr* );
};

struct ident_version{
    std::string operator()(Elf32_Ehdr* );
    std::string operator()(Elf64_Ehdr* );
};

struct type{
    pr operator()(Elf32_Ehdr* );
    pr operator()(Elf64_Ehdr* );
};

struct machine{
    pr operator()(Elf32_Ehdr* );
    pr operator()(Elf64_Ehdr* );
};

struct version{
    pr operator()(Elf32_Ehdr* );
    pr operator()(Elf64_Ehdr* );
};

struct entry{
    std::string operator()(Elf32_Ehdr* );
    std::string operator()(Elf64_Ehdr* );
};

struct phoff{
    std::string operator()(Elf32_Ehdr* );
    std::string operator()(Elf64_Ehdr* );
};

struct shoff{
    std::string operator()(Elf32_Ehdr* );
    std::string operator()(Elf64_Ehdr* );
};

struct flags{
    std::string operator()(Elf32_Ehdr* );
    std::string operator()(Elf64_Ehdr* );
};

struct ehsize{
    std::string operator()(Elf32_Ehdr* );
    std::string operator()(Elf64_Ehdr* );
};

struct phentsize{
    std::string operator()(Elf32_Ehdr* );
    std::string operator()(Elf64_Ehdr* );
};

struct phnum{
    std::string operator()(Elf32_Ehdr* );
    std::string operator()(Elf64_Ehdr* );
};

struct shentsize{
    std::string operator()(Elf32_Ehdr* );
    std::string operator()(Elf64_Ehdr* );
};

struct shnum{
    std::string operator()(Elf32_Ehdr* );
    std::string operator()(Elf64_Ehdr* );
};

struct shstrndx{
    std::string operator()(Elf32_Ehdr* );
    std::string operator()(Elf64_Ehdr* );
};

}
