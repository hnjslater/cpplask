#pragma once

#include <string>
#include <map>
#include <response.hpp>

namespace cpplask {

class request_t {
    std::string m_path;
    response_t m_response;
    std::map<std::string, std::string> m_headers;

public:
    request_t(const std::string& path, std::map<std::string, std::string>&& headers);
    request_t(std::string path, std::map<std::string, std::string> headers);
    const std::string& path();
    response_t& response();
    const std::string& headers(const std::string& name);
};

}
