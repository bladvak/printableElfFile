#include <exception>
#include <filesystem>
#include <iomanip>
#include "printableelf.hpp"
#include "printable_phdr.hpp"
  
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
    //std::cout<<file.gcount();
    //init all of the structures
    auto arch = mem[EI_CLASS];

    if(arch == ELFCLASS32){
            ehdr =(Elf32_Ehdr*) static_cast<void*>(mem.get());
    } else if (arch == ELFCLASS64){
            ehdr =(Elf64_Ehdr*) static_cast<void*>(mem.get());
    } else {
        exit(EXIT_FAILURE);
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