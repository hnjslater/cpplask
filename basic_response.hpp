#pragma once

#include <string>
#include <map>
#include <sstream>

#include <response.hpp>

// Namespace is so we can have a method called basic_response in request. Not ideal.
namespace cpplask::impl {

class basic_response : public response {
    unsigned int m_code;
    std::string m_status;
    std::string m_mime_type;
    std::stringstream m_buffer;
    std::stringstream m_header_buffer;

public:
// Constructors
    basic_response();

// Accessors
    std::string headers_str();
    std::string str();

// Mutators
    template<typename T>
    std::stringstream& operator<<(T value);

    void serve_file(const std::string path);
    void write(const char* buffer, int count);
    void add_header(const std::string& name, const std::string& value);
    void add_cookie(const std::string& name, const std::string& value);

// Fields
    unsigned int& code();
    std::string& status();
    std::string& mime_type();
};
}
