#include <string>
#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
using namespace std;
#include "printableelf.hpp"

namespace po = boost::program_options;

int main(int argc, char** argv){

po::options_description desc("Usage: viewelf <options> elf-file");
desc.add_options()
    ("help, h", "Display help")
    ("all, a", "all options combined")
    ("file-header,f", "display the file header")
    ("section-headers, s", "display the section header table")
    ("program-headers, p", "display the program header table")
    ("symbols, S", "display symbol table")
    ("info, i", "basic information")
    ("relocations, r", "relocations")
    //("note, n", "note sections info")
    ("filename", po::value<std::vector<std::string>>(),"file to be processed");

po::positional_options_description pos;
pos.add("filename", -1);

po::variables_map vm;
po::store(po::command_line_parser(argc, argv).options(desc).positional(pos).allow_unregistered().run(), vm);
po::notify(vm);


if(vm.empty() || vm.count("help")){
    std::cout<<desc;
    return -1;
} else {
    if(vm.count("filename")){
        auto filename = vm["filename"].as<std::vector<std::string>>()[0];
        
        try{
            PrintableElf pr(filename);
            if(vm.count("all")){
                 pr.FileHeader();
                 pr.SectionHeaders();
                 pr.ProgramHeaders();
                 pr.SymbolsTable();
             } else {
            if(vm.count("info"))
                pr.info();
            if(vm.count("file-header"))
                pr.FileHeader();
            if(vm.count("section-headers"))
                pr.SectionHeaders();
            if(vm.count("program-headers"))
                pr.ProgramHeaders();
            if(vm.count("symbols"))
                pr.SymbolsTable();
            if(vm.count("relocations"))
                pr.Relocs();
        }
        } catch(std::ios_base::failure& e){
            std::cout<<e.what(); return -1;
        }
            
    } else {
        std::cout<<desc;
        return -1;
    }

}



    return 0;
}