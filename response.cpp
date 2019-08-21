#include <string>
#include <map>
#include <sstream>
#include <fstream>
#include <cstring>

#include <response.hpp>

namespace cpplask::impl {

template<>
response& operator<<(response& r, std::string s) {
    r.write(s.c_str(), s.length());
    return r;
}

template<>
response& operator<<(response& r, const char* s) {
    r.write(s, std::strlen(s));
    return r;
}

}
