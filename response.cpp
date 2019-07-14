
#include <string>
#include <map>
#include <sstream>

#include <response.hpp>

namespace cpplask::impl {

response::response() : m_code(200), m_status("OK"), m_mime_type("text/html"), m_buffer() { }

unsigned int& response::code() {
    return m_code;
}
void response::write(char* buffer, int count) {
    m_buffer.write(buffer, count);
}
std::string response::str() {
    return m_buffer.str();
}
std::string& response::status() {
    return m_status;
}
std::string& response::mime_type() {
    return m_mime_type;
}

}
