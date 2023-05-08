#include "printable_shdr.hpp"

namespace Shdr{

    long name::operator()(Elf32_Shdr *shdr)
    {
        return shdr->sh_name;
    }

    long name::operator()(Elf64_Shdr *shdr)
    {
        return shdr->sh_name;
    }
    pr type::operator()(Elf32_Shdr *shdr)
    {
        return {std::to_string(shdr->sh_type), typeDict[shdr->sh_type]};
    }
    pr type::operator()(Elf64_Shdr *shdr)
    {
        return {std::to_string(shdr->sh_type), typeDict[shdr->sh_type]};
    }
    std::string flags::operator()(Elf32_Shdr *shdr)
    {
        std::string result{};
        const auto& f = shdr->sh_flags;
        if(f & SHF_WRITE)
           result+= "W";               // W (write)
        if(f & SHF_ALLOC)
           result+= "A";               // A (alloc)
        if(f & SHF_EXECINSTR)
           result+= "X";               // X (execute)
        if(f & SHF_MERGE)
           result+= "M";               // M (merge)
        if(f & SHF_STRINGS)         // S (strings)
           result+= "S";
        if(f & SHF_INFO_LINK)       // I (info link)
           result+= "I";
        if(f & SHF_LINK_ORDER)      // L (link order)
           result+= "L";
        if(f & SHF_OS_NONCONFORMING)// O (non-standard OS specific processing)
           result+= "O";
        if(f & SHF_GROUP)           // G (group)
           result+= "G";
        if(f & SHF_TLS)             // T (TLS)
           result+= "T";
        if(f & SHF_COMPRESSED)      // C (compressed)
           result+= "C";
        if(f & SHF_MASKOS)          // o (OS specific)
           result+= "o";
        if(f & SHF_MASKPROC)        // p (processor specific)
           result+= "p";
        if(f & SHF_GNU_RETAIN)      // R (retain)
           result+= "R";
        if(f & SHF_ORDERED)         // s (special ordering required)
           result+= "s";
        if(f & SHF_EXCLUDE)         // E (exclude)
           result+= "E";

        return result;

    }
    std::string flags::operator()(Elf64_Shdr *shdr)
    {
        std::string result{};
        const auto& f = shdr->sh_flags;
        if(f & SHF_WRITE)
           result+= "W";               // W (write)
        if(f & SHF_ALLOC)
           result+= "A";               // A (alloc)
        if(f & SHF_EXECINSTR)
           result+= "X";               // X (execute)
        if(f & SHF_MERGE)
           result+= "M";               // M (merge)
        if(f & SHF_STRINGS)         // S (strings)
           result+= "S";
        if(f & SHF_INFO_LINK)       // I (info link)
           result+= "I";
        if(f & SHF_LINK_ORDER)      // L (link order)
           result+= "L";
        if(f & SHF_OS_NONCONFORMING)// O (non-standard OS specific processing)
           result+= "O";
        if(f & SHF_GROUP)           // G (group)
           result+= "G";
        if(f & SHF_TLS)             // T (TLS)
           result+= "T";
        if(f & SHF_COMPRESSED)      // C (compressed)
           result+= "C";
        if(f & SHF_MASKOS)          // o (OS specific)
           result+= "o";
        if(f & SHF_MASKPROC)        // p (processor specific)
           result+= "p";
        if(f & SHF_GNU_RETAIN)      // R (retain)
           result+= "R";
        if(f & SHF_ORDERED)         // s (special ordering required)
           result+= "s";
        if(f & SHF_EXCLUDE)         // E (exclude)
           result+= "E";

        return result;
    }

    std::string addr::operator()(Elf32_Shdr *shdr)
    {
        return intToStrHex(shdr->sh_addr);
    }

    std::string addr::operator()(Elf64_Shdr *shdr)
    {
        return asAddressHex(shdr->sh_addr);
    }
    std::string offset::operator()(Elf32_Shdr *shdr)
    {
        return asAddressHex(shdr->sh_offset);
    }
    std::string offset::operator()(Elf64_Shdr *shdr)
    {
        return intToStrHex(shdr->sh_offset);
    }
    long size::operator()(Elf32_Shdr *shdr)
    {
        return shdr->sh_size;
    }
    long size::operator()(Elf64_Shdr *shdr)
    {
        return shdr->sh_size;
    }
    long link::operator()(Elf32_Shdr *shdr)
    {
        return shdr->sh_link;
    }
    long link::operator()(Elf64_Shdr *shdr)
    {
        return shdr->sh_link;
    }
    long info::operator()(Elf32_Shdr *shdr)
    {
        return shdr->sh_info;
    }
    long info::operator()(Elf64_Shdr *shdr)
    {
        return shdr->sh_info;
    }
    long addralign::operator()(Elf32_Shdr *shdr)
    {
        return shdr->sh_addralign;
    }
    long addralign::operator()(Elf64_Shdr *shdr)
    {
        return shdr->sh_addralign;
    }
    long entsize::operator()(Elf32_Shdr *shdr)
    {
        return shdr->sh_entsize;
    }
    long entsize::operator()(Elf64_Shdr *shdr)
    {
        return shdr->sh_entsize;
    }

    void infoFlags(std::ostream &os)
    {   // exactly the same keys as in readelf
        os<<"W (write), A (alloc), X (execute), M (merge),"
            "S (strings), \n I (info link), L (link order), O (non-standard OS specific processing),\n"
            "G (group), T (TLS), C (compressed), o (OS specific), p (processor specific),\n"
            "R (retain), s (special ordering required), E (exclude)\n";
    }

}

std::unordered_map<int, std::string> Shdr::typeDict{
    {SHT_NULL,"unused Section header table entry"}, 
{SHT_PROGBITS,"Program data "},    
{SHT_SYMTAB,"Symbol table "},    
{SHT_STRTAB,"String table "},    
{SHT_RELA,"Relocation entries with addends "},  
{SHT_HASH,"Symbol hash table "},   
{SHT_DYNAMIC,"Dynamic linking information "},   
{SHT_NOTE,"Note "},     
{SHT_NOBITS,"Program space with no data (bss) "},
{SHT_REL,"Relocation entries, no addends "},  
{SHT_SHLIB,"Reserved "},     
{SHT_DYNSYM,"Dynamic linker symbol table "},  
{SHT_INIT_ARRAY,"Array of constructors "},   
{SHT_FINI_ARRAY,"Array of destructors "},   
{SHT_PREINIT_ARRAY,"Array of pre-constructors "},   
{SHT_GROUP,"Section group "},    
{SHT_SYMTAB_SHNDX,"Extended section indices "},   
{SHT_NUM,"Number of defined types. "},  
{SHT_LOOS,"Start OS-specific. "},    
{SHT_GNU_ATTRIBUTES,"Object attributes. "},    
{SHT_GNU_HASH,"GNU-style hash table. "},   
{SHT_GNU_LIBLIST,"Prelink library list "},   
{SHT_CHECKSUM,"Checksum for DSO content. "},  
{SHT_LOSUNW,"Sun-specific low bound. "},   
{SHT_SUNW_move,"SUNW move"},      
{SHT_SUNW_COMDAT,"SUNW comdat"},      
{SHT_SUNW_syminfo,"SUNW syminfo"},      
{SHT_GNU_verdef,"Version definition section. "},   
{SHT_GNU_verneed,"Version needs section. "},   
{SHT_GNU_versym,"Version symbol table. "},   
{SHT_HISUNW,"Sun-specific high bound. "},   
{SHT_HIOS,"End OS-specific type "},   
{SHT_LOPROC,"Start of processor-specific "},   
{SHT_HIPROC,"End of processor-specific "},   
{SHT_LOUSER,"Start of application-specific "},   
{SHT_HIUSER,"End of application-specific "}};  