#include <string>
#include <map>
#include <sstream>
#include <fstream>

#include <basic_response.hpp>

using namespace std::string_literals;

namespace cpplask::impl {

basic_response::basic_response() : m_code(200), m_status("OK"), m_mime_type("text/html"), m_buffer(), m_header_buffer() { }

unsigned int& basic_response::code() {
    return m_code;
}
void basic_response::write(const char* buffer, int count) {
    m_buffer.write(buffer, count);
}
std::string basic_response::str() {
    return m_buffer.str();
}
std::string basic_response::headers_str() {
    return m_header_buffer.str();
}
std::string& basic_response::status() {
    return m_status;
}
std::string& basic_response::mime_type() {
    return m_mime_type;
}

void basic_response::add_header(const std::string& name, const std::string& value) {
    m_header_buffer.write(name.c_str(), name.length());
    m_header_buffer.put(':');
    m_header_buffer.put(' ');
    m_header_buffer.write(value.c_str(), value.length());
    m_header_buffer.put('\n');
}

void basic_response::add_cookie(const std::string& name, const std::string& value) {
    add_header("Set-Cookie", name + "=" + value);
}

void basic_response::serve_file(const std::string path) {
    std::ifstream file(path);
    if (file.fail()) {
        code() = 404;
        status() = "Not Found";
        return;
    }
    copy(std::istreambuf_iterator<char>(file),
         std::istreambuf_iterator<char>(),
         std::ostreambuf_iterator<char>(m_buffer));
}

}
