
a.out : main.o printableelf.o printable_ehdr.o
	   g++ main.o printableelf.o printable_ehdr.o

main.o : main.cpp
	g++ -c main.cpp -g

printableelf.o : printableelf.cpp printableelf.hpp
	g++ -c printableelf.cpp -g

printable_ehdr.o : printable_ehdr.cpp printable_ehdr.hpp utils.hpp
	g++ -c printable_ehdr.cpp -g

clean:
	rm a.out *.o