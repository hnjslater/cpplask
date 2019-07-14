#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include <csignal>
#include <cstdio>
#include <cstring>

#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <atomic>
#include <thread>
#include <algorithm>

#include <basic_server/client_socket.hpp>

// returns true if there is no more data to send.
bool cpplask::client_socket::send_data() {
    int& write_socket_fd = socket_fd;
    std::string& buffstr = buffer;
    int total_written = 0;
    ssize_t num_written = 0;

    do {
        //FIXME MSG_NOSIGNAL is a bit hacky
        //FIXME is writing 1200 at a time really a good idea?
        num_written = send(write_socket_fd,buffstr.c_str(),std::min(static_cast<size_t>(1200), buffstr.size()), MSG_DONTWAIT| MSG_NOSIGNAL);
        std::cerr << "Written " << num_written << " of " << buffstr.size() << std::endl;

        if (num_written < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                total_written += num_written;
                buffstr = std::string(buffstr.begin() + num_written, buffstr.end());
                return false;
            }
            else {
                return true;
            }
        }
        else if (num_written == static_cast<ssize_t>(buffstr.size())) {
            return true;
        }
        else {
            total_written += num_written;
            buffstr = std::string(buffstr.begin() + num_written, buffstr.end());
        }
    } while (num_written > 0);

    return false;
}


cpplask::client_socket::client_socket(int listen_socket_fd, cpplask::service& serv) : 
    socket_fd(0), request_complete(false), buffer(), service(&serv) 
{
    std::cerr << "client connected" << std::endl;
    sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);

    socket_fd = accept(listen_socket_fd, 
             reinterpret_cast<struct sockaddr*>(&client_address), 
             &client_address_len);
    if (socket_fd < 0) {
        throw std::runtime_error("Error during accept");
    }
}

cpplask::client_socket::client_socket(client_socket&& c) : socket_fd(-1), request_complete(false), buffer(), service(nullptr) {
    swap(c);
}

cpplask::client_socket& cpplask::client_socket::operator=(client_socket&& c) {
    swap(c);
    return *this;
}

void cpplask::client_socket::swap(client_socket& c) {
    std::swap(socket_fd,c.socket_fd);
    std::swap(request_complete, c.request_complete);
    std::swap(buffer,c.buffer);
    std::swap(service,c.service);
}

void cpplask::client_socket::add_fds(fd_set& rfds, fd_set& wfds, fd_set& xfds) {
    if (request_complete) {
        FD_SET(socket_fd, &wfds);
    }
    else {
        FD_SET(socket_fd, &rfds);
    }
    FD_SET(socket_fd, &xfds);
}

cpplask::client_socket::~client_socket() {
    if (socket_fd >= 0) {
        close(socket_fd);
    }
}

static auto parse_request(std::string bufferstr) -> auto {
    char* buffer = const_cast<char*>(bufferstr.c_str());

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

    return std::make_pair(path, headers); 
}

void cpplask::client_socket::ingest() {
    char cbuffer[2048] = {0};
    int num_read = read(socket_fd,cbuffer,2040);
    if (num_read < 0) {
        throw std::runtime_error(std::string("ERROR reading from socket:") + std::to_string(socket_fd) + strerror(errno));
    }

    buffer += std::string(cbuffer, num_read);
    std::string marker = "\r\n\r\n";

    if (std::search(buffer.begin(), buffer.end(), marker.begin(), marker.end()) != buffer.end()) {

        auto parameters = parse_request(buffer);
        cpplask::request req(std::get<0>(parameters), std::get<1>(parameters));
        service->serve(req);

        std::string message = req.response().str();

        std::stringstream ss;
        ss << "HTTP/1.1 " << req.response().code() << " " << req.response().status() << "\n";
        ss << "Content-Type: " << req.response().mime_type() << "\n";
        ss << "Content-length: " << message.size() << "\n\n";
        ss << message;

        buffer = ss.str();
        request_complete = true;
    }
}
