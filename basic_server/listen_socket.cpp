#include <basic_server/listen_socket.hpp>
#include <basic_server/client_socket.hpp>

#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <csignal>
#include <map>
#include <vector>
#include <sstream>
#include <atomic>
#include <thread>
#include <algorithm>

namespace
{
    std::atomic<bool> g_keep_going;
}

extern "C" {
    static void signal_handler(int)
    {
        std::cerr << "SIGINT received" << std::endl;
        g_keep_going = false; 
    }
}

cpplask::listen_socket::listen_socket(uint32_t port) : 
    listen_socket_fd(-1) {

    g_keep_going = true;

    sockaddr_in server_address;

    try {
        listen_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (listen_socket_fd < 0) {
            throw std::runtime_error("error during socket opening");
        }

        bzero(reinterpret_cast<char*>(&server_address), sizeof(server_address));

        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = INADDR_ANY;
        server_address.sin_port = htons(port);

        if (bind(listen_socket_fd, reinterpret_cast<struct sockaddr*>(&server_address), sizeof(server_address)) < 0) {
            throw std::runtime_error(std::string("Error during socket binding: ") + strerror(errno));
        }
    }
    catch (...) {
        if (listen_socket_fd >= 0) {
            close(listen_socket_fd);
        }
        throw;
    }
}

cpplask::listen_socket::~listen_socket() {
    close(listen_socket_fd);
}

void cpplask::listen_socket::serve(cpplask::service& service) {

    struct sigaction new_action;
    sigemptyset (&new_action.sa_mask);
    new_action.sa_flags = 0;
    new_action.sa_handler = signal_handler;
    sigaction(SIGINT, &new_action, NULL);
    sigaction(SIGQUIT, &new_action, NULL);
    sigaction(SIGTERM, &new_action, NULL);

    std::vector<client_socket> clients;

    listen(listen_socket_fd, 50);
    while (g_keep_going) {
        fd_set rfds, wfds, xfds;

        FD_ZERO(&rfds);
        FD_ZERO(&wfds);
        FD_ZERO(&xfds);

        FD_SET(listen_socket_fd, &rfds);
        int max_fd = listen_socket_fd;

        for (auto&& client : clients) {
            client.add_fds(rfds, wfds, xfds);
            max_fd = std::max(max_fd, client.socket_fd);
        }

        sigset_t mask;
        sigemptyset (&mask);

        int pselect_rtn = pselect(max_fd+1, &rfds, &wfds, &xfds, NULL, &mask);
        if (pselect_rtn < 0) {
            perror("pselect");
        }
        if (!g_keep_going) {
            break;
        }
        if (pselect_rtn > 0 && FD_ISSET(listen_socket_fd, &rfds)) {
            // new client connecting    
            clients.emplace_back(listen_socket_fd, service);
        }

        // incoming data
        for (auto& client : clients) {
            if (FD_ISSET(client.socket_fd, &rfds)) {
                client.ingest();
            }
        }

        // outgoing data and delete them when we're done.
        clients.erase(std::remove_if(clients.begin(), clients.end(), [&](auto&& client) {
            if (FD_ISSET(client.socket_fd, &wfds)) {
                return client.send_data();
            }
            else {
                return false;
            }
        }), clients.end());

        // get rid of errored clients.
        clients.erase(std::remove_if(clients.begin(), clients.end(), [&](auto&& client) {
            return (FD_ISSET(client.socket_fd, &xfds));
        }), clients.end());
    }
} 
