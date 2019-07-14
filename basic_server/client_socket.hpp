#pragma once

#include <service.hpp>

namespace cpplask {

struct client_socket {
    int socket_fd;
    bool request_complete;
    std::string buffer;
    cpplask::service* service;
    client_socket(int listen_socket_fd, cpplask::service& serv);

    client_socket(const client_socket&) = delete;
    client_socket(client_socket&& c);
    client_socket& operator=(const client_socket&) = delete;
    client_socket& operator=(client_socket&& c);

    void swap(client_socket& c);

    void add_fds(fd_set& rfds, fd_set& wfds, fd_set& xfds);
    void ingest();
    bool send_data();
    ~client_socket();
};

}
