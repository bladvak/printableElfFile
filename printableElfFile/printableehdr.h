#include <utility>
#include <elf.h>
#include <string>

typedef std::pair<std::string, std::string> pr;

class PrintableEhdr{
public:
    PrintableEhdr() = default;
    
    virtual std::string ident() = 0;
    virtual pr type() = 0;
    virtual pr machine() = 0;
    virtual pr version() = 0;
    virtual pr entry() = 0;
    virtual pr phoff() = 0;
    virtual pr shoff() = 0;
    virtual pr flags() = 0;
    virtual pr ehsize() = 0;
    virtual pr phentsize() = 0;
    virtual pr phnum() = 0;
    virtual pr shentsize() = 0;
    virtual pr shnum() = 0;
    virtual pr shstrndx() = 0;
    
};