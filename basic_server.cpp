#include <basic_server.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <csignal>

#include <map>
#include <vector>
#include <sstream>
#include <atomic>
#include <thread>

namespace cpplask {

namespace
{
    std::atomic<bool> g_keep_going;
}

extern "C" {
    static void signal_handler(int)
    {
        g_keep_going = false; 
    }
}

void serve(cpplask::service_t& service, int listen_socket_fd);
void basic_serve(cpplask::service_t& service, uint32_t port) {
    g_keep_going=true;

    sockaddr_in server_address;

    int listen_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_socket_fd < 0) {
        throw std::runtime_error("error during socket opening");
    }

    try {

        bzero((char *) &server_address, sizeof(server_address));

        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = INADDR_ANY;
        server_address.sin_port = htons(port);

        if (bind(listen_socket_fd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
            throw std::runtime_error("Error during socket binding");
        }
        sigset_t set;
        sigset_t orig_set;
        sigfillset(&set);
        sigprocmask(SIG_SETMASK, &set, &orig_set);
        std::cerr << "listening on port " << port << std::endl;
        serve(service, listen_socket_fd);
        sigprocmask(SIG_SETMASK, &orig_set, NULL);
    }
    catch (...) {
        close(listen_socket_fd);
        throw;
    }
}


void serve(cpplask::service_t& service, int listen_socket_fd) {
    while (g_keep_going) {
        listen(listen_socket_fd,5);

        fd_set rfds;

        FD_ZERO(&rfds);
        FD_SET(listen_socket_fd, &rfds);

        std::signal(SIGQUIT, signal_handler);
        std::signal(SIGINT, signal_handler);
        std::signal(SIGTERM, signal_handler);

        sigset_t mask;
        sigemptyset (&mask);

        pselect(listen_socket_fd+1, &rfds, NULL, NULL, NULL, &mask);
        if (!g_keep_going) {
            break;
        }
        else if (FD_ISSET(listen_socket_fd, &rfds)) {
            
            sockaddr_in client_address;
            socklen_t client_address_len = sizeof(client_address);

            int accept_socket_fd = accept(listen_socket_fd, 
                     (struct sockaddr *) &client_address, 
                     &client_address_len);
            if (accept_socket_fd < 0) {
                throw std::runtime_error("Error during accept");
            }
            char buffer[2048] = {0};
            int num_read = read(accept_socket_fd,buffer,2040);
            if (num_read < 0) {
                throw std::runtime_error("ERROR reading from socket");
            }
            char* strtok_state;
            char* current_line_buf = 0;

            std::string verb = strtok_r(buffer, " ", &strtok_state);
            std::string path = strtok_r(NULL, " ", &strtok_state);
            std::map<std::string, std::string> query_params;

            std::string version = strtok_r(NULL, "\n", &strtok_state);
            std::map<std::string, std::string> headers;
            do {
                current_line_buf = strtok_r(NULL, "\n", &strtok_state);
                const std::string current_line(current_line_buf);
                size_t index_of_colon = current_line.find(":"); 
                if (index_of_colon != std::string::npos) {
                    const std::string name = current_line.substr(0, index_of_colon);
                    const std::string value = current_line.substr(index_of_colon+2, current_line.length()-index_of_colon-3);
                    headers[name] = value;
                }
            } while (strlen(current_line_buf) > 1);
            std::cerr << verb << " " << path << "\n";

            cpplask::request_t req(path, std::move(headers)); 
            service.serve(req);

            std::string message = req.response().str();

            std::stringstream ss;
            ss << "HTTP/1.1 " << req.response().code() << " " << req.response().status() << "\n";
            ss << "Content-Type: text/plain\n";
            ss << "Content-length: " << message.size() << "\n\n";
            ss << message;
            int num_written = write(accept_socket_fd,ss.str().c_str(),ss.str().size());
            if (num_written < 0) {
                throw std::runtime_error("Error during writing to socket");
            }
            close(accept_socket_fd);
        }
    }
    close(listen_socket_fd);
    std::cerr << "exiting" << std::endl;
} 

}
