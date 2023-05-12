#ifndef PRINTABLE_SYM_HPP
#define PRINTABLE_SYM_HPP
#include "elf.h"
#include <iostream>
#include "utils.hpp"

namespace Sym{
    
    struct name{
        long operator()(Elf32_Sym* sym);
        long operator()(Elf64_Sym* sym);
    };

    struct infoBind{
        std::string operator()(Elf32_Sym* sym);
        std::string operator()(Elf64_Sym* sym);
    };

     struct infoType{
        std::string operator()(Elf32_Sym* sym);
        std::string operator()(Elf64_Sym* sym);
    };

    struct other{
        std::string operator()(Elf32_Sym* sym);
        std::string operator()(Elf64_Sym* sym);
    };

    struct shndx{
        long operator()(Elf32_Sym* sym);
        long operator()(Elf64_Sym* sym);
    };

    struct value{
        std::string operator()(Elf32_Sym* sym);
        std::string operator()(Elf64_Sym* sym);
    };

    struct size{
        long operator()(Elf32_Sym* sym);
        long operator()(Elf64_Sym* sym);
    };

}

#endif