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

public:
    response();

    template<typename T>
    std::stringstream& operator<<(T value);

    unsigned int& code();
    void write(char* buffer, int count);
    std::string str();
    std::string& status();
    std::string& mime_type(); 
};

template<typename T>
std::stringstream& response::operator<<(T value) {
    m_buffer << value;
    return m_buffer;
}

}
