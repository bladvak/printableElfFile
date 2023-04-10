#ifndef PRINTABLEPHDR_H
#define PRINTABLEPHDR_H

#include <elf.h>
#include <string>

class PrintablePhdr {
    public:
    PrintablePhdr() = default;

    virtual std::string type() = 0;
    virtual std::string flags() = 0;
    virtual long offset() = 0;
    virtual long vaddr() = 0;
    virtual long paddr() = 0;
    virtual long filesz() = 0;
    virtual long memsz() = 0;
    virtual long align() = 0;

};

#endif