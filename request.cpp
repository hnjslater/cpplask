#include <request.hpp>

namespace cpplask {

request_t::request_t(const std::string& path, std::map<std::string, std::string>&& headers) : 
    m_path(path), m_response(), m_headers(headers) 
{ }

request_t::request_t(std::string path, std::map<std::string, std::string> headers) :
    m_path(path), m_response(), m_headers(headers) 
{ }
const std::string& request_t::path() {
    return m_path;
}

response_t& request_t::response() {
    return m_response;
}

const std::string& request_t::headers(const std::string& name) {
    return m_headers[name]; 
}

}
