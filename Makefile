CPPFLAGS+=-std=c++11 -Wall -Werror -Wextra -pedantic -Weffc++ -I.

all:    main

main: main.o
	${CXX} $^ -o $@


main.o:
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
server.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
server.o: /usr/include/sys/_symbol_aliasing.h
server.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
server.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
server.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
server.o: /usr/include/i386/_types.h /usr/include/secure/_stdio.h
server.o: /usr/include/secure/_common.h /usr/include/stdlib.h
server.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
server.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
server.o: /usr/include/i386/signal.h /usr/include/i386/_structs.h
server.o: /usr/include/sys/_structs.h /usr/include/machine/_structs.h
server.o: /usr/include/sys/resource.h /usr/include/machine/endian.h
server.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
server.o: /usr/include/libkern/_OSByteOrder.h
server.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
server.o: /usr/include/machine/types.h /usr/include/i386/types.h
server.o: /usr/include/string.h /usr/include/strings.h
server.o: /usr/include/secure/_string.h /usr/include/unistd.h
server.o: /usr/include/sys/unistd.h /usr/include/sys/select.h
server.o: /usr/include/sys/_select.h /usr/include/sys/types.h
server.o: /usr/include/sys/socket.h /usr/include/machine/_param.h
server.o: /usr/include/i386/_param.h /usr/include/netinet/in.h
server.o: /usr/include/stdint.h /usr/include/netinet6/in6.h
url_scanner_test.o: ./url_scanner.hpp
