#include <url_scanner.hpp>
#include <response.hpp>
#include <request.hpp>

#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <memory>
#include <sstream>
#include <fstream>
#include <map>

namespace cpplask {

bool serve_static_file(request& req, path path) {
    req.response().serve_file(path.str);
    return true;
}

std::function<void(request&)> static_file_action(const std::string path) {
    return [path](request& req) {
        req.response().serve_file(path);
    };
}

}
