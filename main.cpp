#include <string>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <utility>
#include <variant>
#include <vector>
using namespace std;
#include "printableelf.hpp"

struct A{
    std::string s;
};
struct B{
    std::string s;
};

struct printS{
    string operator()(A* a){return "AAA";}
    string operator()(B* b){return "BBB";}
};
//just for testing as for now
int main(){

PrintableElf e("exe");
//e.FileHeader(); e.ProgramHeaders();
//e.SectionHeaders(); 
e.SymbolsTable();

    return 0;
}