#include "printableehdr.h"
#include <stdexcept>
#include <unordered_map>

class PrintableEhdr64 : public PrintableEhdr{

private:
    Elf64_Ehdr* ehdr64_ptr;
    std::string intToStrHex(long long val);

public:
    PrintableEhdr64(void* mem_ptr);

     virtual std::string magic() override;
     virtual std::string ident_class() override;
    virtual std::string ident_data() override;
    virtual std::string ident_version() override;

    virtual pr type() override;
    virtual pr machine() override;
    virtual pr version() override;
    
    virtual std::string entry() override;
    virtual std::string phoff() override;
    virtual std::string shoff() override;
    virtual std::string flags() override;
    virtual std::string ehsize() override;
    virtual std::string phentsize() override;
    virtual std::string phnum() override;
    virtual std::string shentsize() override;
    virtual std::string shnum() override;
    virtual std::string shstrndx() override;

private:
static std::unordered_map<int, std::string> e_type;
};