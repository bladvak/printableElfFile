#include "printable_phdr.hpp"

namespace Phdr{

    std::string type::operator()(Elf32_Phdr *phdr)
    {
        return typeDict[phdr->p_type];
    }

    std::string type::operator()(Elf64_Phdr *phdr)
    {
        return typeDict[phdr->p_type];
    }

    std::string flags::operator()(Elf32_Phdr *phdr)
    {
        std::string f;
        long copy = phdr->p_flags;

         if(copy & PF_R)
            f += "R";
        else
            f += "-";

        if(copy & PF_W)
            f+= "W";
        else
            f += "-";

        if(copy & PF_X)
            f += "X";
        else
            f += "-";

        return f;
    }

    std::string flags::operator()(Elf64_Phdr *phdr)
    {
        std::string f;
        long copy = phdr->p_flags;

         if(copy & PF_R)
            f += "R";
        else
            f += "-";

        if(copy & PF_W)
            f+= "W";
        else
            f += "-";

        if(copy & PF_X)
            f += "X";
        else
            f += "-";

        return f;
    }

    std::string offset::operator()(Elf32_Phdr *phdr)
    {
        return asAddressHex(phdr->p_offset);
    }

    std::string offset::operator()(Elf64_Phdr *phdr)
    {
        return asAddressHex(phdr->p_offset);
    }
    std::string vaddr::operator()(Elf32_Phdr *phdr)
    {
        return asAddressHex(phdr->p_vaddr);
    }
    std::string vaddr::operator()(Elf64_Phdr *phdr)
    {
        return asAddressHex(phdr->p_vaddr);
    }
    std::string paddr::operator()(Elf32_Phdr *phdr)
    {
        return asAddressHex(phdr->p_paddr);
    }
    std::string paddr::operator()(Elf64_Phdr *phdr)
    {
        return asAddressHex(phdr->p_paddr);
    }
    long filesz::operator()(Elf32_Phdr *phdr)
    {
        return phdr->p_filesz;
    }
    long filesz::operator()(Elf64_Phdr *phdr)
    {
        return phdr->p_filesz;
    }
    long memsz::operator()(Elf32_Phdr *phdr)
    {
        return phdr->p_memsz;
    }
    long memsz::operator()(Elf64_Phdr *phdr)
    {
        return phdr->p_memsz;
    }
    long align::operator()(Elf32_Phdr *phdr)
    {
        return phdr->p_align;
    }
    long align::operator()(Elf64_Phdr *phdr)
    {
        return phdr->p_align;
    }
}

std::unordered_map<int, std::string> Phdr::typeDict = {
     {	PT_NULL, " Program header table entry unused"},
{ PT_LOAD, "LOAD"},
{ PT_DYNAMIC, "DYNAMIC"},
{ PT_INTERP, "INTERP"},
{ PT_NOTE, "NOTE"},
{ PT_SHLIB, "SHLIB"},
{ PT_PHDR, "PHDR"},
{ PT_TLS, "TLS"},
{	PT_NUM, "NUM"},
{ PT_LOOS, "LOOS"},
{ PT_GNU_EH_FRAME, "GNU_EH_FRAME"},
{ PT_GNU_STACK, "GNU_STACK"},
{ PT_GNU_RELRO, "GNU_RELRO"},
{ PT_GNU_PROPERTY, "GNU_PROPERTY"},
{ PT_LOSUNW	, "LOSUNW"},
{ PT_SUNWBSS, "SUNWBSS"},
{ PT_SUNWSTACK, "SUNWSTACK"},
{ PT_HISUNW, "HISUNW"},
{ PT_HIOS, "HIOS"},
{ PT_LOPROC, "LOPROC"},
{ PT_HIPROC, "HIPROC"} };

/*
{	PT_NULL, " Program header table entry unused"},
{ PT_LOAD, " Loadable program segment"},
{ PT_DYNAMIC, " Dynamic linking information"},
{ PT_INTERP, " Program interpreter"},
{ PT_NOTE, " Auxiliary information"},
{ PT_SHLIB, " Reserved"},
{ PT_PHDR, " Entry for header table itself"},
{ PT_TLS, " Thread-local storage segment"},
{	PT_NUM, " Number of defined types"},
{ PT_LOOS, " Start of OS-specific"},
{ PT_GNU_EH_FRAME, " GCC .eh_frame_hdr segment"},
{ PT_GNU_STACK, " Indicates stack executability"},
{ PT_GNU_RELRO, " Read-only after relocation"},
{ PT_GNU_PROPERTY, " GNU property"},
{ PT_LOSUNW	, " LO SUN"},
{ PT_SUNWBSS, " Sun Specific segment"},
{ PT_SUNWSTACK, " Stack segment"},
{ PT_HISUNW, " HI SUN"},
{ PT_HIOS, " End of OS-specific"},
{ PT_LOPROC, " Start of processor-specific"},
{ PT_HIPROC, " End of processor-specific"}
*/