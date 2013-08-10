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

#include <map>
#include <vector>
#include <sstream>

class basic_server_t {
    public:
    void serve(cpplask::service_t& service, int port) {
        sockaddr_in server_address;

        int listen_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (listen_socket_fd < 0) {
            throw std::runtime_error("error during socket opening");
        }

        bzero((char *) &server_address, sizeof(server_address));

        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = INADDR_ANY;
        server_address.sin_port = htons(port);

        if (bind(listen_socket_fd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
              throw std::runtime_error("Error during socket binding");
        }
        while (true) {
            listen(listen_socket_fd,5);
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
        close(listen_socket_fd);
    } 
};
