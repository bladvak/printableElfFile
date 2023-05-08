#ifndef PRINTABLE_SHDR_HPP
#define PRINTABLE_SHDR_HPP
#include <elf.h>
#include "utils.hpp"

namespace Shdr{

extern std::unordered_map<int, std::string> typeDict;

    struct name{
        long operator()(Elf32_Shdr* );
        long operator()(Elf64_Shdr* );
    };

    struct type{
        pr operator()(Elf32_Shdr* );
        pr operator()(Elf64_Shdr* );
    };

    struct flags{
        std::string operator()(Elf32_Shdr* );
        std::string operator()(Elf64_Shdr* );
    };

    struct addr{
        std::string operator()(Elf32_Shdr* );
        std::string operator()(Elf64_Shdr* );
    };

    struct offset{
        std::string operator()(Elf32_Shdr* );
        std::string operator()(Elf64_Shdr* );
    };

    struct size{
        long operator()(Elf32_Shdr* );
        long operator()(Elf64_Shdr* );
    };

    struct link{
        long operator()(Elf32_Shdr* );
        long operator()(Elf64_Shdr* );
    };

    struct info{
        long operator()(Elf32_Shdr* );
        long operator()(Elf64_Shdr* );
    };

    struct addralign{
        long operator()(Elf32_Shdr* );
        long operator()(Elf64_Shdr* );
    };
    
    struct entsize{
        long operator()(Elf32_Shdr* );
        long operator()(Elf64_Shdr* );
    };

    void infoFlags(std::ostream& os);
}

#endif
/*

string flags info = "W (write), A (alloc), X (execute), M (merge),
S (strings), I (info link), L (link order), O (non-standard OS specific processing),
G (group), T (TLS), C (compressed), o (OS specific), p (processor specific), 
R (retain), s (special ordering required), E (exclude)"

*/