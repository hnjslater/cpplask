#pragma once

#include <string>
#include <map>
#include <response.hpp>
#include <vector>

namespace cpplask {

class request {
public:
    virtual ~request() {};

// Accessors
    virtual const std::string& path() const = 0;
    virtual const std::string& query() const = 0;
    virtual const std::vector<std::string> headers(const std::string& name) const = 0;
    virtual const std::vector<std::pair<std::string,std::string>> headers() const = 0;
    virtual const std::optional<std::string> cookie(const std::string& name) const = 0;

// Fields
    virtual impl::response& response() = 0;
};

}
