#include <utility>
#include <elf.h>
#include <string>

typedef std::pair<std::string, std::string> pr;

class PrintableEhdr{
public:
    PrintableEhdr() = default;
    
    virtual std::string magic() = 0;

    virtual std::string ident_class() = 0;
    virtual std::string ident_data() = 0;
    virtual std::string ident_version() = 0;

    virtual pr type() = 0;
    virtual pr machine() = 0;
    virtual pr version() = 0;

    virtual std::string entry() = 0;
    virtual std::string phoff() = 0;
    virtual std::string shoff() = 0;
    virtual std::string flags() = 0;
    virtual std::string ehsize() = 0;
    virtual std::string phentsize() = 0;
    virtual std::string phnum() = 0;
    virtual std::string shentsize() = 0;
    virtual std::string shnum() = 0;
    virtual std::string shstrndx() = 0;
    
};