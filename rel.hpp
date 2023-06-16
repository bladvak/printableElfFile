#pragma once

#include <elf.h>
#include <string>
#include <unordered_map>
namespace Rel {

}

namespace Rela {
    struct addend {
        std::string operator()(Elf32_Rela* rela);
        std::string operator()(Elf64_Rela* rela);
    };

    struct offset {
        std::string operator()(Elf32_Rela* rela);
        std::string operator()(Elf64_Rela* rela);
    };

    struct sym {
        long operator()(Elf32_Rela* rela);
        long operator()(Elf64_Rela* rela);
    };

    struct type {
        std::string operator()(Elf32_Rela* rela, uint32_t machine = EM_X86_64);
        std::string operator()(Elf64_Rela* rela, uint32_t machine = EM_X86_64);
    };

    struct info {
        std::string operator()(Elf32_Rela* rela);
        std::string operator()(Elf64_Rela* rela);
    };
    
}

extern std::unordered_map<int, std::string> Rel_AMD64;

