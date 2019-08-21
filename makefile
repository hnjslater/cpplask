CPPFLAGS+=-std=c++17 -Wall -Werror -Wextra -pedantic -Weffc++ -I. -Wundef -Wold-style-cast
OBJS:=service.o basic_request.o response.o basic_response.o
OBJS+=basic_server/basic_server.o basic_server/client_socket.o basic_server/listen_socket.o

all:    main

main: ${OBJS} main.o
	${CXX} $^ -o $@ -pthread

%.o: %.cpp
	${CXX} -c ${CPPFLAGS} $< -o $@

tests: url_scanner_test.cpp basic_request_test.cpp basic_request.o basic_response.o response.o
	${CXX} ${CPPFLAGS} -o $@ $^ -pthread -lgtest -lgtest_main
	./tests

clean:
	rm -f main tests ${OBJS}

deps:
	makedepend -Y. *.cpp basic_server/*.cpp

examples/microblog/server: ${OBJS} examples/microblog/server.o
	${CXX} $^ -o $@ -pthread

# DO NOT DELETE

basic_request.o: ./basic_request.hpp ./response.hpp ./request.hpp
basic_request.o: ./basic_response.hpp
basic_request_test.o: ./basic_request.hpp ./response.hpp ./request.hpp
basic_request_test.o: ./basic_response.hpp
basic_response.o: ./basic_response.hpp ./response.hpp
main.o: ./service.hpp ./url_scanner.hpp ./response.hpp ./request.hpp
main.o: ./basic_server/basic_server.hpp
response.o: ./basic_response.hpp ./response.hpp
service.o: ./url_scanner.hpp ./response.hpp ./request.hpp
url_scanner_test.o: ./url_scanner.hpp
basic_server/basic_server.o: ./basic_server/basic_server.hpp ./service.hpp
basic_server/basic_server.o: ./url_scanner.hpp ./response.hpp ./request.hpp
basic_server/basic_server.o: ./basic_server/signal_stopper.hpp
basic_server/basic_server.o: ./basic_server/listen_socket.hpp
basic_server/basic_server.o: ./basic_server/client_socket.hpp
basic_server/client_socket.o: ./basic_server/client_socket.hpp ./service.hpp
basic_server/client_socket.o: ./url_scanner.hpp ./response.hpp ./request.hpp
basic_server/client_socket.o: ./basic_request.hpp ./basic_response.hpp
basic_server/listen_socket.o: ./basic_server/listen_socket.hpp ./service.hpp
basic_server/listen_socket.o: ./url_scanner.hpp ./response.hpp ./request.hpp
basic_server/listen_socket.o: ./basic_server/client_socket.hpp
