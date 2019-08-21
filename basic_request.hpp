#pragma once

#include <string>
#include <map>
#include <response.hpp>
#include <vector>
#include <request.hpp>
#include <basic_response.hpp>

namespace cpplask {

class basic_request : public request {
    std::string m_path;
    std::string m_query;
    std::vector<std::pair<std::string, std::string>> m_headers;

    impl::basic_response m_response;
public:
    
// Constuctors
    basic_request(std::string path, std::string query, std::vector<std::pair<std::string, std::string>> headers);
    virtual ~basic_request() = default;
// Accessors
    virtual const std::string& path() const;
    virtual const std::string& query() const;
    virtual const std::vector<std::string> headers(const std::string& name) const;
    virtual const std::vector<std::pair<std::string,std::string>> headers() const;
    virtual const std::optional<std::string> cookie(const std::string& name) const;

// Fields
    virtual impl::response& response();
};

}
