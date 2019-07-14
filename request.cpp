#include <request.hpp>

namespace cpplask {

request::request(const std::string& path, std::map<std::string, std::string>&& headers) : 
    m_path(path), m_response(), m_headers(headers) 
{ }

request::request(std::string path, std::map<std::string, std::string> headers) :
    m_path(path), m_response(), m_headers(headers) 
{ }
const std::string& request::path() {
    return m_path;
}

impl::response& request::response() {
    return m_response;
}

const std::string& request::headers(const std::string& name) {
    return m_headers[name]; 
}

}
