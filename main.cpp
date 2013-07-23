#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <memory>
#include <sstream>
#include <url_scanner.hpp>
#include <service.hpp>
#include <basic_server.hpp>



int main() {
    service_t s;

    s.map<int>("/page/%") = [](request_t& req, int x) {
        req.response() << x;
    };

    s.map<int,int>("/page/%/%") = [](request_t& req, int x, int y) {
        req.response() << x << " " << y;
    };

    basic_server_t bs;
    bs.serve(s, 8000);
}
