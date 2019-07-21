
#include <string>
#include <map>
#include <sstream>

#include <response.hpp>

using namespace std::string_literals;

namespace cpplask::impl {

response::response() : m_code(200), m_status("OK"), m_mime_type("text/html"), m_buffer(), m_header_buffer() { }

unsigned int& response::code() {
    return m_code;
}
void response::write(char* buffer, int count) {
    m_buffer.write(buffer, count);
}
std::string response::str() {
    return m_buffer.str();
}
std::string response::headers_str() {
    return m_header_buffer.str();
}
std::string& response::status() {
    return m_status;
}
std::string& response::mime_type() {
    return m_mime_type;
}

void response::add_header(const std::string& name, const std::string& value) {
    m_header_buffer.write(name.c_str(), name.length());
    m_header_buffer.put(':');
    m_header_buffer.put(' ');
    m_header_buffer.write(value.c_str(), value.length());
    m_header_buffer.put('\n');
}


}
