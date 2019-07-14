#pragma once

#include <string>
#include <map>
#include <response.hpp>

namespace cpplask {

class request {
    std::string m_path;
    impl::response m_response;
    std::map<std::string, std::string> m_headers;

public:
    request(const std::string& path, std::map<std::string, std::string>&& headers);
    request(std::string path, std::map<std::string, std::string> headers);
    const std::string& path();
    impl::response& response();
    const std::string& headers(const std::string& name);
};

}
