#include "printableshdr32.h"
#include <stdexcept>
#include <sstream>

PrintableShdr32::PrintableShdr32(void *mem_ptr) : 
        shdr_ptr(static_cast<Elf32_Shdr*>(mem_ptr))
{
    if(shdr_ptr == nullptr)
        throw std::runtime_error("pointer to Shdr struct cannot be null.");
}

int PrintableShdr32::name_index()
{
    return shdr_ptr->sh_name;
}

pr PrintableShdr32::type()
{
    return {intToStrHex(shdr_ptr->sh_type),s_type[shdr_ptr->sh_type]};
}

std::string PrintableShdr32::addr()
{
    return intToStrHex(shdr_ptr->sh_addr);
}

std::string PrintableShdr32::offset()
{
    return intToStrHex(shdr_ptr->sh_offset);
}

std::string PrintableShdr32::size()
{
    return intToStrHex(shdr_ptr->sh_size);
}

int PrintableShdr32::link()
{
    return shdr_ptr->sh_link;
}

int PrintableShdr32::info()
{
    return shdr_ptr->sh_info;
}

std::string PrintableShdr32::intToStrHex(long long val)
{
    std::ostringstream ss;
    ss<<"0x"<<std::hex<<val;
    return ss.str();
}

std::unordered_map<int, std::string> PrintableShdr32::s_type{
    {SHT_NULL,"Section header table entry unused "}, 
{SHT_PROGBITS,"Program data "},    
{SHT_SYMTAB,"Symbol table "},    
{SHT_STRTAB,"String table "},    
{SHT_RELA,"Relocation entries with addends "},  
{SHT_HASH,"Symbol hash table "},   
{SHT_DYNAMIC,"Dynamic linking information "},   
{SHT_NOTE,"Notes "},     
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