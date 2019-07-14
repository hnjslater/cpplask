#include <service.hpp>
#include <basic_server/basic_server.hpp>

#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <memory>
#include <sstream>
#include <random>

using namespace cpplask;

int main() {
    service s;

    s.map<>("/") = [](request& req) {
        req.response() << "<htm><body><h1>Hello World</h1></body></html>";
    };

    s.map<int>("/page/%") = [](request& req, auto x) {
        req.response() << x;
    };

    s.map<int,int>("/page/%/%") = [](request& req, auto x, auto y) {
        req.response() << x << " " << y;
    };

    s.map<std::string>("/title/%") = [](request& req, std::string) {
        req.response() << req.headers("User-Agent");
    };

    s.map<path>("/file/%") = [](request& req, auto path) {
        serve_static_file(req, path);
    };

    basic_serve(s, 5000);
}
