
a.out : main.o printableelf.o printable_ehdr.o printable_phdr.o printable_shdr.o utils.o printable_sym.o rel.o
	   g++ main.o printableelf.o printable_ehdr.o printable_phdr.o rel.o \
	   printable_shdr.o utils.o printable_sym.o  -L /usr/lib/x86_64-linux-gnu -l boost_program_options
	   

main.o : main.cpp
	g++ -c main.cpp -g

printableelf.o : printableelf.cpp printableelf.hpp
	g++ -c printableelf.cpp -g

printable_ehdr.o : printable_ehdr.cpp printable_ehdr.hpp 
	g++ -c printable_ehdr.cpp -g

printable_phdr.o : printable_phdr.cpp printable_phdr.hpp 
	g++ -c printable_phdr.cpp -g

printable_shdr.o : printable_shdr.cpp printable_shdr.hpp 
	g++ -c printable_shdr.cpp -g

utils.o : utils.cpp utils.hpp
	g++ -c utils.cpp -g

printable_sym: printable_sym.cpp printable_sym.hpp
	g++ -c printable_sym.cpp -g

rel.o : rel.cpp rel.hpp 
	g++ -c rel.cpp -g


clean:
	rm a.out *.o