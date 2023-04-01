#include <utility>
#include <string>
#include <unordered_map>
#include <elf.h>

typedef std::pair<std::string, std::string> pr;

class PrintableShdr {
public:
PrintableShdr() = default;

virtual int name_index() = 0;
virtual pr type() = 0;
virtual pr flags() = 0;

virtual std::string addr() = 0;
virtual std::string offset() = 0;
virtual std::string size() = 0;

virtual int link() = 0;
virtual int info() = 0;

//virtual addralign() =0;
//virtual entsize() = 0;

};