#ifndef PRINTABLEELF_HPP
#define PRINTABLEELF_HPP

#include "printable_ehdr.hpp"
#include "printable_phdr.hpp"
#include "printable_shdr.hpp"
#include "printable_sym.hpp"
#include <vector>
#include <memory>
#include <fstream>
#include <variant>

class PrintableElf{

public:
    PrintableElf(const std::string& path, std::ostream& os = std::cout);
    PrintableElf(PrintableElf&& ) = delete;
    PrintableElf(PrintableElf& ) = delete;
    ~PrintableElf();

    void info();
    void FileHeader();
    void SectionHeaders();
    void ProgramHeaders();
    void SymbolsTable();

private:
    
    const std::string file_path;
    std::ostream& os;
    std::ifstream file;
    std::unique_ptr<char[]> mem;
    char* strtab_ptr;

    std::variant<Elf32_Ehdr*,Elf64_Ehdr*> ehdr;
    std::vector< std::variant<Elf32_Phdr*, Elf64_Phdr*>> phdrs;
    std::vector< std::variant<Elf32_Shdr*, Elf64_Shdr*>> shdrs;
    std::vector< std::variant<Elf32_Sym*, Elf64_Sym*>> symbols;
};

#endif