#include "rel.hpp"
#include "utils.hpp"

std::string Rela::addend::operator()(Elf32_Rela *rela)
{
    return intToStrHex(rela->r_addend);
}

std::string Rela::addend::operator()(Elf64_Rela *rela)
{
    return intToStrHex(rela->r_addend);
}

std::string Rela::offset::operator()(Elf32_Rela *rela)
{
    return asAddressHex(rela->r_offset);
}

std::string Rela::offset::operator()(Elf64_Rela *rela)
{
    return asAddressHex(rela->r_offset);
}

long Rela::sym::operator()(Elf32_Rela *rela)
{
    return ELF32_R_SYM(rela->r_info);
}

long Rela::sym::operator()(Elf64_Rela *rela)
{
    return ELF64_R_SYM(rela->r_info);
}

std::string Rela::info::operator()(Elf32_Rela *rela)
{
    return intToStrHex(rela->r_info);
}

std::string Rela::info::operator()(Elf64_Rela *rela)
{
    return intToStrHex(rela->r_info);
}

std::string Rela::type::operator()(Elf32_Rela *rela, uint32_t machine)//switch based on ehdr.e_machine
{
    switch(machine){
        case EM_X86_64:
            return Rel_AMD64[ELF32_R_TYPE(rela->r_info)];
        break;
        default:
            return std::string();
    }
}

std::string Rela::type::operator()(Elf64_Rela *rela, uint32_t machine)
{
    switch(machine){
        case EM_X86_64:
            return Rel_AMD64[ELF64_R_TYPE(rela->r_info)];
        break;
        default:
            return std::string();
    }
}

std::unordered_map<int, std::string> Rel_AMD64 = 
 {{R_X86_64_NONE	," No reloc "},
 {R_X86_64_64	," Direct 64 bit  "},
 {R_X86_64_PC32	," PC relative 32 bit signed "},
 {R_X86_64_GOT32	," 32 bit GOT entry "},
 {R_X86_64_PLT32	," 32 bit PLT address "},
 {R_X86_64_COPY	," Copy symbol at runtime "},
{R_X86_64_GLOB_DAT	," Create GOT entry "},
 {R_X86_64_JUMP_SLOT	,"R_X86_64_JUMP_SLOT"},
 {R_X86_64_RELATIVE	," Adjust by program base "},
 {R_X86_64_GOTPCREL	," 32 bit signed PC relative    offset to GOT "},
 {R_X86_64_32	," Direct 32 bit zero extended "},
 {R_X86_64_32S	," Direct 32 bit sign extended "},
 {R_X86_64_16	," Direct 16 bit zero extended "},
 {R_X86_64_PC16	," 16 bit sign extended pc relative "},
 {R_X86_64_8	," Direct 8 bit sign extended  "},
 {R_X86_64_PC8	," 8 bit sign extended pc relative "},
 {R_X86_64_DTPMOD64	," ID of module containing symbol "},
 {R_X86_64_DTPOFF64	," Offset in module's TLS block "},
 {R_X86_64_TPOFF64	," Offset in initial TLS block "},
 {R_X86_64_TLSGD	," 32 bit signed PC relative offset to two GOT entries for GD symbol "},
 {R_X86_64_TLSLD	," 32 bit signed PC relative offset to two GOT entries for LD symbol "},
 {R_X86_64_DTPOFF32	," Offset in TLS block "},
 {R_X86_64_GOTTPOFF	," 32 bit signed PC relative offset    to GOT entry for IE symbol "},
 {R_X86_64_TPOFF32	," Offset in initial TLS block "},
 {R_X86_64_PC64	," PC relative 64 bit "},
 {R_X86_64_GOTOFF64	," 64 bit offset to GOT "},
 {R_X86_64_GOTPC32	," 32 bit signed pc relative    offset to GOT "},
 {R_X86_64_GOT64	," 64-bit GOT entry offset "},
 {R_X86_64_GOTPCREL64	," 64-bit PC relative offset    to GOT entry "},
 {R_X86_64_GOTPC64	," 64-bit PC relative offset to GOT "},
 {R_X86_64_GOTPLT64	," like GOT64, says PLT entry needed "},
 {R_X86_64_PLTOFF64	," 64-bit GOT relative offset    to PLT entry "},
 {R_X86_64_SIZE32	," Size of symbol plus 32-bit addend "},
 {R_X86_64_SIZE64	," Size of symbol plus 64-bit addend "},
 {R_X86_64_GOTPC32_TLSDESC 	," GOT offset for TLS descriptor.  "},
 {R_X86_64_TLSDESC_CALL   	," Marker for call through TLS    descriptor.  "},
 {R_X86_64_TLSDESC        	," TLS descriptor.  "},
 {R_X86_64_IRELATIVE	," Adjust indirectly by program base "},
 {R_X86_64_RELATIVE64	," 64-bit adjust by program base "},
 {R_X86_64_GOTPCRELX	," Load from 32 bit signed pc relative    offset to GOT entry without REX ,"},
 {R_X86_64_REX_GOTPCRELX	," Load from 32 bit signed pc relative    offset to GOT entry with REX prefix ,"},
 {R_X86_64_NUM	," Num" }};