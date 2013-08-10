#include <service.hpp>
#include <basic_server.hpp>

#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <memory>
#include <sstream>

using namespace cpplask;

int main() {
    service_t s;

    s.map<int>("/page/%") = [](request_t& req, int x) {
        req.response() << x;
    };

    s.map<int,int>("/page/%/%") = [](request_t& req, int x, int y) {
        req.response() << x << " " << y;
    };

    s.map<std::string>("/title/%") = [](request_t& req, std::string) {
        req.response() << req.headers("User-Agent");
    };

    s.map<path_t>("/file/%") = [](request_t& req, path_t path) {
        serve_static_file(req, path);
    };

    basic_server_t bs;
    bs.serve(s, 8000);
}
