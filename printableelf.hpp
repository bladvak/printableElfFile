#ifndef PRINTABLEELF_HPP
#define PRINTABLEELF_HPP

#include "printable_ehdr.hpp"

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

private:

    const std::string file_path;
    std::ostream& os;
    std::ifstream file;
    std::unique_ptr<char[]> mem;

    std::variant<Elf32_Ehdr*,Elf64_Ehdr*> ehdr;
    //std::vector<PrintablePhdr* > phdrs;
    //std::vector<PrintableShdr* > shdrs;
};

#endif