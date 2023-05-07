#include <exception>
#include <filesystem>
#include <iomanip>
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

void PrintableElf::ProgramHeaders()
{
    os<<"\n__________________Program header table___\n";
    os<<"\n"<<std::left<<std::setw(20)<<"Type"<<std::setw(20)<<"Offset"<<std::setw(20)<<
        "Virtual addres"<<"Physical address\n"<<std::setw(20)<<""<<std::setw(20)<<
        "File size"<<std::setw(20)<<"Memory size"<<std::setw(10)<<"Flags"<<"Allign";

    for(const auto& p : phdrs){
        os<<"\n"<<std::left<<std::setw(20)<<std::visit(Phdr::type(),p)<<std::setw(20)<<std::visit(Phdr::offset(),p)<<std::setfill(' ')<<std::left<< std::setw(20)<<
        std::visit(Phdr::vaddr(),p)<<std::visit(Phdr::paddr(),p)<<"\n"<<std::setw(20)<<""<<std::setw(20)<<
        std::visit(Phdr::filesz(),p)<<std::setw(20)<<std::visit(Phdr::memsz(),p)<<std::setw(10)<<std::visit(Phdr::flags(),p)<<
        std::visit(Phdr::align(),p);
    }
    os<<"\n\n";
}
