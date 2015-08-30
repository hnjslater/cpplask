CPPFLAGS+=-std=c++11 -Wall -Werror -Wextra -pedantic -Weffc++ -I. -Wundef
all:    main

main: main.o
	${CXX} $^ -o $@

main.o: main.cpp
	${CXX} ${CPPFLAGS} -c main.cpp -o main.o

tests: url_scanner_test.cpp url_scanner.hpp
	${CXX} ${CPPFLAGS} -o $@ url_scanner_test.cpp -pthread -lgtest -lgtest_main
	./tests

clean:
	rm -f main tests main.o

# DO NOT DELETE
