#pragma once

#include <string>
#include <map>
#include <sstream>

#include <response.hpp>

// Namespace is so we can have a method called response in request. Not ideal.
namespace cpplask::impl {

class response {
public:
    virtual ~response() {};

// Accessors
    virtual std::string headers_str() = 0;
    virtual std::string str() = 0;

// Mutators
    virtual void serve_file(const std::string path) = 0;
    virtual void write(const char* buffer, int count) = 0;
    virtual void add_header(const std::string& name, const std::string& value) = 0;
    virtual void add_cookie(const std::string& name, const std::string& value) = 0;

// Fields
    virtual unsigned int& code() = 0;
    virtual std::string& status() = 0;
    virtual std::string& mime_type() = 0;
};

template<typename T>
response& operator<<(response& r, T value) {
    auto s = std::to_string(value);
    r.write(s.c_str(), s.length());
    return r;
}

template<>
response& operator<<(response& r, std::string s);

template<>
response& operator<<(response& r, const char* s);
}
