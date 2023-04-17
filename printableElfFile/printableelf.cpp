#include "printableelf.h"
#include <exception>
#include <fstream>

PrintableElf::PrintableElf(const std::string& path, std::ostream &os) :
    file_path(path), os(os), file(std::ifstream())
{
    file.open(file_path, std::ios_base::in);
    if(!file)
        throw std::ios_base::failure("Cannot open. Check if the file exists.");

    //tbc ;read the file, check for type and fill the vector members
}

PrintableElf::~PrintableElf()
{
    file.close();
}

void PrintableElf::FileHeader()
{

}