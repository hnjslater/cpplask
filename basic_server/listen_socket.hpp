#pragma once

#include <atomic>
#include <service.hpp>

namespace cpplask {

struct listen_socket {
    int listen_socket_fd;
    listen_socket(uint32_t port); 

    void serve(cpplask::service& service);
    ~listen_socket();
};

}
