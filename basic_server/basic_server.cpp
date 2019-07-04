#include <basic_server/basic_server.hpp>
#include <basic_server/signal_stopper.hpp>
#include <basic_server/listen_socket.hpp>
#include <basic_server/client_socket.hpp>

#include <iostream>

namespace cpplask {

void basic_serve(cpplask::service_t& service, uint32_t port) {
    listen_socket listen_socket(port);
    std::cerr << "listening on port " << port << std::endl;
    signal_stopper_t stopper;
    listen_socket.serve(service);
    stopper.restore_signals();
    std::cerr << "Exiting" << std::endl;
}

}
