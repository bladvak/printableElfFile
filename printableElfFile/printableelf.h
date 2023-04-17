#ifndef PRINTABLEELF_H
#define PRINTABLEELF_H

#include "printableehdr32.h"
#include "printableehdr64.h"
#include "printablephdr32.h"
#include "printablephdr64.h"
#include "printableshdr32.h"
#include "printableshdr64.h"
#include <iostream>
#include <vector>

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

    PrintableEhdr* ehdr;
    std::vector<PrintablePhdr* > phdrs;
    std::vector<PrintableShdr* > shdrs;
};

#endif