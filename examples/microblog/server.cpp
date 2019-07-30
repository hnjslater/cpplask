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
        req.response() << "<html><body><h1>Hello World</h1></body></html>";
    };

    s.map<>("/signup") = static_file_action("signup.html");

    s.map<>("/user/create") = [](request& req) {
        req.response() << "<html><body><h1>created</h1></body></html>";
    };

    basic_serve(s, 5000);
}
