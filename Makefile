CPPFLAGS+=-std=c++11 -Wall -Werror -Wextra -pedantic -Weffc++ -I.

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

main.o: ./url_scanner.hpp ./service.hpp ./basic_server.hpp
main.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
main.o: /usr/include/sys/_symbol_aliasing.h
main.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
main.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
main.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
main.o: /usr/include/i386/_types.h /usr/include/secure/_stdio.h
main.o: /usr/include/secure/_common.h /usr/include/stdlib.h
main.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
main.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
main.o: /usr/include/i386/signal.h /usr/include/i386/_structs.h
main.o: /usr/include/sys/_structs.h /usr/include/machine/_structs.h
main.o: /usr/include/sys/resource.h /usr/include/machine/endian.h
main.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
main.o: /usr/include/libkern/_OSByteOrder.h
main.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
main.o: /usr/include/machine/types.h /usr/include/i386/types.h
main.o: /usr/include/string.h /usr/include/strings.h
main.o: /usr/include/secure/_string.h /usr/include/unistd.h
main.o: /usr/include/sys/unistd.h /usr/include/sys/select.h
main.o: /usr/include/sys/_select.h /usr/include/sys/types.h
main.o: /usr/include/sys/socket.h /usr/include/machine/_param.h
main.o: /usr/include/i386/_param.h /usr/include/netinet/in.h
main.o: /usr/include/stdint.h /usr/include/netinet6/in6.h
url_scanner_test.o: ./url_scanner.hpp
basic_server.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
basic_server.o: /usr/include/sys/_symbol_aliasing.h
basic_server.o: /usr/include/sys/_posix_availability.h
basic_server.o: /usr/include/Availability.h
basic_server.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
basic_server.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
basic_server.o: /usr/include/i386/_types.h /usr/include/secure/_stdio.h
basic_server.o: /usr/include/secure/_common.h /usr/include/stdlib.h
basic_server.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
basic_server.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
basic_server.o: /usr/include/i386/signal.h /usr/include/i386/_structs.h
basic_server.o: /usr/include/sys/_structs.h /usr/include/machine/_structs.h
basic_server.o: /usr/include/sys/resource.h /usr/include/machine/endian.h
basic_server.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
basic_server.o: /usr/include/libkern/_OSByteOrder.h
basic_server.o: /usr/include/libkern/i386/_OSByteOrder.h
basic_server.o: /usr/include/alloca.h /usr/include/machine/types.h
basic_server.o: /usr/include/i386/types.h /usr/include/string.h
basic_server.o: /usr/include/strings.h /usr/include/secure/_string.h
basic_server.o: /usr/include/unistd.h /usr/include/sys/unistd.h
basic_server.o: /usr/include/sys/select.h /usr/include/sys/_select.h
basic_server.o: /usr/include/sys/types.h /usr/include/sys/socket.h
basic_server.o: /usr/include/machine/_param.h /usr/include/i386/_param.h
basic_server.o: /usr/include/netinet/in.h /usr/include/stdint.h
basic_server.o: /usr/include/netinet6/in6.h
