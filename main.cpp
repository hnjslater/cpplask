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
        req.response() << req.headers("User-Agent")[0];
    };

    s.map<path>("/file/%") = [](request& req, auto path) {
        serve_static_file(req, path);
    };

    s.map<>("/info") = [](request& req) {
        req.response().add_header("Server", "cpplask 0.1");
        req.response() << "<htm><body><h1>Hello World</h1></body></html>";
    };

    s.map<>("/login") = [](request& req) {
        req.response().add_cookie("logged-in", "true");
    };

    s.map<>("/user") = [](request& req) {
        if (req.cookie("logged-in") == "true") {
            req.response() << "Logged in";
        }
        else {
            req.response() << "Not logged in" << req.cookie("logged-in").value_or("");
        }
    };

    s.map<>("/headers") = [](request& req) {
        for (auto [name, value] : req.headers()) {
            req.response()  << name << "=" << value << "<br/>";
        }
        req.response() << "Query String: " << req.query() << "<br />";
    };

    basic_serve(s, 5000);
}
