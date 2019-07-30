#include <request.hpp>

#include <algorithm>
#include <iterator>

namespace cpplask {

request::request(const std::string& path, const std::string& query, std::vector<std::pair<std::string, std::string>>&& headers) : 
    m_path(path), m_query(query), m_headers(headers), m_response()
{ }

request::request(std::string path, std::string query, std::vector<std::pair<std::string, std::string>> headers) :
    m_path(path), m_query(query), m_headers(headers), m_response() 
{ }

const std::string& request::path() const {
    return m_path;
}

const std::string& request::query() const {
    return m_query;
}

impl::response& request::response() {
    return m_response;
}

const std::vector<std::string> request::headers(const std::string& name) const {
    auto comp = [](auto x, auto y) {
            return x.first < y.first;
        };

    const std::pair needle { name, "" };

    // When C++20 arrives we can use equal_range

    const auto first = std::lower_bound(
        m_headers.begin(),
        m_headers.end(),
        needle,
        comp
    );

    const auto last = std::upper_bound(
        m_headers.begin(),
        m_headers.end(),
        needle,
        comp
    );

    if (first == std::end(m_headers)) {
        return {};
    }
    
    std::vector<std::string> result (std::distance(first, last));

    std::transform(
        first,
        last,
        result.begin(),
        [](auto p) { return p.second; }
    );

    return result;
}

const std::optional<std::string> request::cookie(const std::string& name) const {

    const auto value_prefix = name + "=";

    for (auto cookie_header : headers("Cookie")) {
        if (std::equal(
            cookie_header.begin(),
            cookie_header.begin() + std::min(cookie_header.length(), value_prefix.length()),
            value_prefix.begin())
        ) {
            return {cookie_header.substr(value_prefix.length())};
        }
    }

    return {};
}


const std::vector<std::pair<std::string,std::string>> request::headers() const {
    return m_headers;
}

}
