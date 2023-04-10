#include "printablephdr32.h"

PrintablePhdr32::PrintablePhdr32(void* mem_ptr) :
    phdr(static_cast<Elf32_Phdr*>(mem_ptr)){

}

std::string PrintablePhdr32::type()
{
    return p_type[phdr->p_type];
}

std::string PrintablePhdr32::flags()
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

long PrintablePhdr32::offset()
{
    phdr->p_offset;
}

long PrintablePhdr32::vaddr()
{
    phdr->p_vaddr;
}

long PrintablePhdr32::paddr()
{
    phdr->p_paddr;
}

long PrintablePhdr32::filesz()
{
    phdr->p_filesz;
}

long PrintablePhdr32::memsz()
{
    phdr->p_memsz;
}

long PrintablePhdr32::align()
{
    return phdr->p_align;
}

std::unordered_map<int, std::string> PrintablePhdr32::p_type = {
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
{ PT_HIPROC, " End of processor-specific"} };
