CPPFLAGS+=-std=c++11 -Wall -Werror -Wextra -pedantic -Weffc++ -I. -Wundef
all:    main

main: main.o
	${CXX} $^ -o $@

main.o: main.cpp
	${CXX} ${CPPFLAGS} -c main.cpp -o main.o

tests: url_scanner_test.cpp url_scanner.hpp
	${CXX} ${CPPFLAGS} -isystem ${GTEST_DIR}/include/ -L ${GTEST_DIR}  -lgtest  -lgtest_main -o $@ url_scanner_test.cpp
	./tests
clean:
	rm -f main tests main.o
# DO NOT DELETE
