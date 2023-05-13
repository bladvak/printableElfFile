#include <exception>
#include <filesystem>
#include <iomanip>
#include <algorithm>
#include "printableelf.hpp"
  
PrintableElf::PrintableElf(const std::string& path, std::ostream &os) :
    file_path(path), os(os), file(std::ifstream())
{
    file.open(file_path, std::ios_base::in | std::ios_base::binary); //under linux ::bin doesn't matter
    if(!file)
        throw std::ios_base::failure("Cannot open. Check if the file exists.");

    //tbc ;read the file, check for type and fill the vector members
    auto size = std::filesystem::file_size(path);
    mem = std::make_unique<char[]>(size); //might throw bad_alloc
    file.read(mem.get(),size);            //might throw
    
    auto arch = mem[EI_CLASS];

    if(arch == ELFCLASS32){             //initialize structures for x32
            ehdr =(Elf32_Ehdr*) static_cast<void*>(mem.get());
            const auto eh = static_cast<Elf32_Ehdr*>(static_cast<void*>(mem.get()));

            for(int i = 0; i < eh->e_phnum; i++){
                phdrs.push_back((Elf32_Phdr*)(void*)(mem.get() + eh->e_phoff +
                                i * eh->e_phentsize));
            }

            for(int i = 0; i < eh->e_shnum; i++){
                shdrs.push_back((Elf32_Shdr*)(void*)(mem.get() + eh->e_shoff +
                                i * eh->e_shentsize));
            }

            //symbol table
            auto symtabIt = std::find_if(shdrs.cbegin(),shdrs.cend(), [](auto p){
                return std::visit(Shdr::type(), p).second == Shdr::typeDict[SHT_SYMTAB]; } );
            if(symtabIt != shdrs.cend()){
                auto symCount = std::visit(Shdr::size(), *symtabIt) / std::visit(Shdr::entsize(), *symtabIt);
                auto offset = std::stoi(std::visit(Shdr::offset(), *symtabIt), 0, 16);
                auto& strtab = shdrs[ std::visit(Shdr::link(), *symtabIt)];
                strtab_ptr = mem.get() + std::stoi(std::visit(Shdr::offset(),strtab), 0, 16);
                for(int i = 0; i < symCount; i++)
                    symbols.push_back((Elf32_Sym*)(void*) (mem.get() + offset + (i * std::visit(Shdr::entsize(), *symtabIt))));
            }

    } else if (arch == ELFCLASS64){     //initialize structures for x64
            ehdr =(Elf64_Ehdr*) static_cast<void*>(mem.get());
            const auto eh = static_cast<Elf64_Ehdr*>(static_cast<void*>(mem.get()));

            for(int i = 0; i < eh->e_phnum; i++){
                phdrs.push_back((Elf64_Phdr*)(void*)(mem.get() + eh->e_phoff +
                                i * eh->e_phentsize));
            }

            for(int i = 0; i < eh->e_shnum; i++){
                shdrs.push_back((Elf64_Shdr*)(void*)(mem.get() + eh->e_shoff +
                                i * eh->e_shentsize));
            }
            //symbol table
            auto symtabIt = std::find_if(shdrs.cbegin(),shdrs.cend(), [](auto p){
                return std::visit(Shdr::type(), p).second == Shdr::typeDict[SHT_SYMTAB]; } );
            if(symtabIt != shdrs.cend()){
                auto symCount = std::visit(Shdr::size(), *symtabIt) / std::visit(Shdr::entsize(), *symtabIt);
                auto offset = std::stoi(std::visit(Shdr::offset(), *symtabIt), 0, 16);
                auto& strtab = shdrs[ std::visit(Shdr::link(), *symtabIt)];
                strtab_ptr = mem.get() + std::stoi(std::visit(Shdr::offset(),strtab), 0, 16);
                for(int i = 0; i < symCount; i++)
                    symbols.push_back((Elf64_Sym*)(void*) (mem.get() + offset + (i * std::visit(Shdr::entsize(), *symtabIt))));
            }
    } else {
        exit(EXIT_FAILURE); // !!! handle this case properly later !!!
    }

} 

PrintableElf::~PrintableElf()
{
    file.close(); //for clarity
}

void PrintableElf::info(){
    
    os<<"\n"<<"File: "<< file_path<<" - "<<std::visit(Ehdr::ident_class(),ehdr)<<","
        " compiled for "<<std::visit(Ehdr::machine(), ehdr).second;

}

void PrintableElf::FileHeader(){  
    
    os<<"\n__________________File header___\n"<<std::left;
    os<<std::setw(36)<<"Magic:"<<std::visit(Ehdr::magic(),ehdr)<<"\n";
    os<<std::setw(36)<<"Class:"<<std::visit(Ehdr::ident_class(),ehdr)<<"\n";
    os<<std::setw(36)<<"Encoding:"<<std::visit(Ehdr::ident_data(),ehdr)<<"\n";
    os<<std::setw(36)<<"Version:"<<std::visit(Ehdr::ident_version(),ehdr)<<"\n";    
    auto atype = std::visit(Ehdr::type(),ehdr);
    os<<std::setw(36)<<"Type:"<<atype.second<<"\n";
    auto amachine = std::visit(Ehdr::machine(), ehdr);
    os<<std::setw(36)<<"Machine:"<<amachine.second<<"\n";
    os<<std::setw(36)<<"Flags:"<<std::visit(Ehdr::flags(),ehdr)<<"\n";
    // version
    os<<std::setw(36)<<"Entry point:"<<std::visit(Ehdr::entry(),ehdr)<<"\n";
    os<<std::setw(36)<<"Program header offset:"<<std::visit(Ehdr::phoff(),ehdr)<<"\n";
    os<<std::setw(36)<<"Section header offset:"<<std::visit(Ehdr::shoff(),ehdr)<<"\n";
    os<<std::setw(36)<<"File header size:"<<std::visit(Ehdr::ehsize(),ehdr)<<" (bytes)"<<"\n";
    os<<std::setw(36)<<"Program header size:"<<std::visit(Ehdr::phentsize(),ehdr)<<" (bytes)"<<"\n";
    os<<std::setw(36)<<"Number of program headers:"<<std::visit(Ehdr::phnum(),ehdr)<<"\n";
    os<<std::setw(36)<<"Section header size:"<<std::visit(Ehdr::shentsize(),ehdr)<<" (bytes)"<<"\n";
    os<<std::setw(36)<<"Number of section headers:"<<std::visit(Ehdr::shnum(),ehdr)<<"\n";
    os<<std::setw(36)<<"Index of string table:"<<std::visit(Ehdr::shstrndx(),ehdr)<<"\n";
}

void PrintableElf::SectionHeaders()
{
    int counter = 0;
    os<<"\n__________________Section header table___\n";
    os<<std::left<<std::setw(6)<<"[nr]"<<std::setw(20)<<"Name"<<std::setw(20)<<"Type"
        <<std::setw(20)<<"Address"<<"Offset\n"<<std::setw(6)<<""<<std::setw(20)<<"Size"
        <<std::setw(20)<<"Entry size"<<std::setw(7)<<"Flags"<<std::setw(8)<<"Link"
        <<std::setw(5)<<"Info"<<"Allign\n";
        /*uint shnum, shoff, shsize;
        const uint shoff = std::stoi(std::visit(Ehdr::shoff(),ehdr));
        const uint shnum = std::stoi(std::visit(Ehdr::shnum(),ehdr));
        const uint shsiz = std::stoi(std::visit(Ehdr::shentsize(),ehdr));
        const uint shstr = std::stoi(std::visit(Ehdr::shstrndx(),ehdr));*/

        const auto& shstrPtr = shdrs[stoi(std::visit(Ehdr::shstrndx(),ehdr))];
        auto arr = mem.get() + std::stoi(std::visit(Shdr::offset(), shstrPtr),0,16);
    for(const auto& s : shdrs){

        os<<std::left<<std::setw(6)<<counter<<std::setw(20)<<std::string(arr + std::visit(Shdr::name(),s))
        <<std::setw(20)<<std::visit(Shdr::type(), s).second.substr(0,17)<<std::setw(20)<<std::visit(Shdr::addr(), s)
        <<std::visit(Shdr::offset(), s)<<"\n"<<std::setw(6)<<""<<std::setw(20)<<std::visit(Shdr::size(), s)
        <<std::setw(20)<<std::visit(Shdr::entsize(), s)<<std::setw(7)<<std::visit(Shdr::flags(), s)
        <<std::setw(8)<<std::visit(Shdr::link(), s)<<std::setw(5)<<std::visit(Shdr::info(), s)<<std::setw(20)
        <<std::visit(Shdr::addralign(), s)<<"\n";

        counter++;
    }
    Shdr::infoFlags(os);
}

void PrintableElf::ProgramHeaders()
{
    os<<"\n__________________Program header table___\n";
    os<<"\n"<<std::left<<std::setw(20)<<"Type"<<std::setw(20)<<"Offset"<<std::setw(20)<<
        "Virtual addres"<<"Physical address\n"<<std::setw(20)<<""<<std::setw(20)<<
        "File size"<<std::setw(20)<<"Memory size"<<std::setw(10)<<"Flags"<<"Allign\n";

    for(const auto& p : phdrs){
        os<<std::left<<std::setw(20)<<std::visit(Phdr::type(),p)<<std::setw(20)<<std::visit(Phdr::offset(),p)<<std::setfill(' ')<<std::left<< std::setw(20)<<
        std::visit(Phdr::vaddr(),p)<<std::visit(Phdr::paddr(),p)<<"\n"<<std::setw(20)<<""<<std::setw(20)<<
        std::visit(Phdr::filesz(),p)<<std::setw(20)<<std::visit(Phdr::memsz(),p)<<std::setw(10)<<std::visit(Phdr::flags(),p)<<
        std::visit(Phdr::align(),p)<<"\n";
    }
    os<<"\n\n";
}

void PrintableElf::SymbolsTable()
{
    
    std::cout<<"\n.symtab contains "<<symbols.size()<<"symbols:\n";
    std::cout<<std::left<<std::setw(5)<<"Num:"<<std::setw(20)<<"Value"<<std::setw(6)<<
                "Size"<<std::setw(12)<<"Type"<<std::setw(10)<<"Bind"<<std::setw(14)<<"Vis"<<
                std::setw(6)<<"Ndx"<<"Name\n";
    int count = 0;
   for(auto& s : symbols){
        
        std::cout<<std::left<<std::setw(5)<<count<<std::setw(20)<<std::visit(Sym::value(),s)<<std::setw(6)<<
                std::visit(Sym::size(),s)<<std::setw(12)<<std::visit(Sym::infoType(),s)<<std::setw(10)<<std::visit(Sym::infoBind(),s)<<std::setw(14)<<
                std::visit(Sym::other(),s)<<std::setw(6)<<std::visit(Sym::shndx(),s)<<std::string(std::visit(Sym::name(),s) + strtab_ptr).substr(0,16)<<"\n";
                count++;
        
   }

}
