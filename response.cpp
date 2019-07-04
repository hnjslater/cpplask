
#include <string>
#include <map>
#include <sstream>

#include <response.hpp>

namespace cpplask {

response_t::response_t() : m_code(200), m_status("OK"), m_mime_type("text/html"), m_buffer() { }

unsigned int& response_t::code() {
    return m_code;
}
void response_t::write(char* buffer, int count) {
    m_buffer.write(buffer, count);
}
std::string response_t::str() {
    return m_buffer.str();
}
std::string& response_t::status() {
    return m_status;
}
std::string& response_t::mime_type() {
    return m_mime_type;
}

}
