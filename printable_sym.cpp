#include "printable_sym.hpp"

namespace Sym{
    long name::operator()(Elf32_Sym *sym)
    {
        return sym->st_name;
    }
    long name::operator()(Elf64_Sym *sym)
    {
        return sym->st_name;
    }
    std::string infoBind::operator()(Elf32_Sym *sym)
    {
        auto val = ELF32_ST_BIND(sym->st_info);
        switch(val){
            case STB_LOCAL: return "LCOAL";
            case STB_GLOBAL: return "GLOBAL";
            case STB_WEAK: return "WEAK";
            case STB_NUM: return "NUM";
            //case STB_LOOS: return "LOOS"; why
            case STB_GNU_UNIQUE: return "UNIQUE";
            case STB_HIOS: return "HIOS";
            case STB_LOPROC: return "LOPROC";
            case STB_HIPROC: return "HIPROC";
            default : return "undef";
        }
    }
    std::string infoBind::operator()(Elf64_Sym *sym)
    {
        auto val = ELF64_ST_BIND(sym->st_info);
          switch(val){
            case STB_LOCAL: return "LCOAL";
            case STB_GLOBAL: return "GLOBAL";
            case STB_WEAK: return "WEAK";
            case STB_NUM: return "NUM";
            //case STB_LOOS: return "LOOS"; why
            case STB_GNU_UNIQUE: return "UNIQUE";
            case STB_HIOS: return "HIOS";
            case STB_LOPROC: return "LOPROC";
            case STB_HIPROC: return "HIPROC";
            default : return "undef";
        }
    }
    std::string other::operator()(Elf32_Sym *sym)
    {
        auto val = ELF32_ST_VISIBILITY(sym->st_other);
        switch(val){
            case STV_DEFAULT: return "DEFAULT";
            case STV_INTERNAL: return "INTERNAL";
            case STV_HIDDEN: return "HIDDEN";
            case STV_PROTECTED: return "PROTECTED";
            default: return "undef";
        }
    }
    std::string other::operator()(Elf64_Sym *sym)
    {
        auto val = ELF32_ST_VISIBILITY(sym->st_other);
        switch(val){
            case STV_DEFAULT: return "DEFAULT";
            case STV_INTERNAL: return "INTERNAL";
            case STV_HIDDEN: return "HIDDEN";
            case STV_PROTECTED: return "PROTECTED";
            default: return "undef";
        }
    }
    std::string infoType::operator()(Elf32_Sym *sym)
    {
        auto val = ELF32_ST_TYPE(sym->st_info);
        switch(val){
            case STT_NOTYPE: return "NOTYPE";
            case STT_FUNC: return "FUNC";
            case STT_OBJECT: return "OBJECT";
            case STT_SECTION: return "SECTION";
            case STT_FILE: return "FILE";
            case STT_COMMON: return "COMMON";
            case STT_TLS: return "TLS";
            default: return " ";
            //there is more options
        }
    }
    std::string infoType::operator()(Elf64_Sym *sym)
    {
        auto val = ELF64_ST_TYPE(sym->st_info);
        switch(val){
            case STT_NOTYPE: return "NOTYPE";
            case STT_FUNC: return "FUNC";
            case STT_OBJECT: return "OBJECT";
            case STT_SECTION: return "SECTION";
            case STT_FILE: return "FILE";
            case STT_COMMON: return "COMMON";
            case STT_TLS: return "TLS";
            default: return " ";
            //there is more options
        }
    }
    long shndx::operator()(Elf32_Sym *sym)
    {
        return sym->st_shndx;
    }
    long shndx::operator()(Elf64_Sym *sym)
    {
        return sym->st_shndx;
    }
    std::string value::operator()(Elf32_Sym *sym)
    {
        return asAddressHex(sym->st_value);
    }
    std::string value::operator()(Elf64_Sym *sym)
    {
        return asAddressHex(sym->st_value);
    }
    long size::operator()(Elf32_Sym *sym)
    {
        return sym->st_size;
    }
    long size::operator()(Elf64_Sym *sym)
    {
        return sym->st_size;
    }
}