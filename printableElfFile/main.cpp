#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
using namespace std;
#include "printableehdr64.h"


int main(){

fstream f("exe");
void *ptr;
if(f.is_open())
    f.read(static_cast<char*>(ptr), sizeof(Elf64_Ehdr));
PrintableEhdr64 e(ptr);
auto a = e.machine();
std::cout<<a.first<<" "<<a.second;

f.close();

    return 0;
}