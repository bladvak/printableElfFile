#ifndef PRINTABLEPHDR64_H
#define PRINTABLEPHDR64_H

#include <elf.h>
#include <string>
#include "printablephdr.h"
#include <unordered_map>

class PrintablePhdr64 : public PrintablePhdr {
    public:
    PrintablePhdr64(void* );

    virtual std::string type() override;
    virtual std::string flags() override;
    virtual long offset() override;
    virtual long vaddr() override;
    virtual long paddr() override;
    virtual long filesz() override;
    virtual long memsz() override;
    virtual long align() override;

    private:
    Elf64_Phdr* phdr;

    static std::unordered_map<int, std::string> p_type;
};

#endif