
a.out : main.o printableelf.o printable_ehdr.o printable_phdr.o printable_shdr.o utils.o
	   g++ main.o printableelf.o printable_ehdr.o printable_phdr.o \
	   printable_shdr.o utils.o

main.o : main.cpp
	g++ -c main.cpp -g

printableelf.o : printableelf.cpp printableelf.hpp
	g++ -c printableelf.cpp -g

printable_ehdr.o : printable_ehdr.cpp printable_ehdr.hpp utils.hpp
	g++ -c printable_ehdr.cpp -g

printable_phdr.o : printable_phdr.cpp printable_phdr.hpp utils.hpp
	g++ -c printable_phdr.cpp -g

printable_shdr.o : printable_shdr.cpp printable_shdr.hpp utils.hpp
	g++ -c printable_shdr.cpp -g

utils.o : utils.cpp utils.o
	g++ -c utils.cpp -g
clean:
	rm a.out *.o