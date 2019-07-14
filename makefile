CPPFLAGS+=-std=c++17 -Wall -Werror -Wextra -pedantic -Weffc++ -I. -Wundef -Wold-style-cast
OBJS:=main.o service.o request.o response.o
OBJS+=basic_server/basic_server.o basic_server/client_socket.o basic_server/listen_socket.o

all:    main

main: ${OBJS}
	${CXX} $^ -o $@ -pthread

%.o: %.cpp
	${CXX} -c ${CPPFLAGS} $< -o $@

tests: url_scanner_test.cpp url_scanner.hpp
	${CXX} ${CPPFLAGS} -o $@ url_scanner_test.cpp -pthread -lgtest -lgtest_main
	./tests

clean:
	rm -f main tests ${OBJS}

deps:
	makedepend -Y. *.cpp basic_server/*.cpp

# DO NOT DELETE

main.o: ./service.hpp ./url_scanner.hpp ./response.hpp ./request.hpp
main.o: ./basic_server/basic_server.hpp
request.o: ./request.hpp ./response.hpp
response.o: ./response.hpp
service.o: ./url_scanner.hpp ./response.hpp ./request.hpp
url_scanner_test.o: ./url_scanner.hpp
basic_server/basic_server.o: ./basic_server/basic_server.hpp ./service.hpp
basic_server/basic_server.o: ./url_scanner.hpp ./response.hpp ./request.hpp
basic_server/basic_server.o: ./basic_server/signal_stopper.hpp
basic_server/basic_server.o: ./basic_server/listen_socket.hpp
basic_server/basic_server.o: ./basic_server/client_socket.hpp
basic_server/client_socket.o: ./basic_server/client_socket.hpp ./service.hpp
basic_server/client_socket.o: ./url_scanner.hpp ./response.hpp ./request.hpp
basic_server/listen_socket.o: ./basic_server/listen_socket.hpp ./service.hpp
basic_server/listen_socket.o: ./url_scanner.hpp ./response.hpp ./request.hpp
basic_server/listen_socket.o: ./basic_server/client_socket.hpp
