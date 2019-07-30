#pragma once

#include <string>
#include <map>
#include <sstream>

#include <response.hpp>

// Namespace is so we can have a method called response in request. Not ideal.
namespace cpplask::impl {

class response {
    unsigned int m_code;
    std::string m_status;
    std::string m_mime_type;
    std::stringstream m_buffer;
    std::stringstream m_header_buffer;

public:
// Constructors
    response();

// Accessors
    std::string headers_str();
    std::string str();

// Mutators
    template<typename T>
    std::stringstream& operator<<(T value);

    void serve_file(const std::string path);
    void write(char* buffer, int count);
    void add_header(const std::string& name, const std::string& value);
    void add_cookie(const std::string& name, const std::string& value);

// Fields
    unsigned int& code();
    std::string& status();
    std::string& mime_type();
};

template<typename T>
std::stringstream& response::operator<<(T value) {
    m_buffer << value;
    return m_buffer;
}

}
