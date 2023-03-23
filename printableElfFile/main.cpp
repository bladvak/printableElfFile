#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
using namespace std;
#include "printableehdr32.h"


int main(){

fstream f("exe");
void *ptr = new char[sizeof(Elf32_Ehdr)];
if(f.is_open()){
    f.read(static_cast<char*>(ptr), sizeof(Elf32_Ehdr));
PrintableEhdr32 e(ptr);
auto a = e.type();
std::cout<<e.ident_class()<<"\n";
std::cout<<e.ident_data()<<"\n";
std::cout<<e.ident_version()<<"\n";
std::cout<<a.first<<" "<<a.second<<"\n";
std::cout<<e.shoff()<< " "<<e.phoff();
f.close();
}


    return 0;
}