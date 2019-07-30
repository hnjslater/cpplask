#pragma once

#include <string>
#include <map>
#include <response.hpp>
#include <vector>

namespace cpplask {

class request {
    std::string m_path;
    std::string m_query;
    std::vector<std::pair<std::string, std::string>> m_headers;

    impl::response m_response;
public:

    
// Constuctors
    request(const std::string& path, const std::string& query, std::vector<std::pair<std::string, std::string>>&& headers);
    request(std::string path, std::string query, std::vector<std::pair<std::string, std::string>> headers);

// Accessors
    const std::string& path() const;
    const std::string& query() const;
    const std::vector<std::string> headers(const std::string& name) const;
    const std::vector<std::pair<std::string,std::string>> headers() const;
    const std::optional<std::string> cookie(const std::string& name) const;

// Fields
    impl::response& response();
};

}
