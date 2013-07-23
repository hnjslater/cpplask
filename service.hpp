#pragma once
#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <memory>
#include <sstream>

class response_t {
    unsigned int m_code;
    std::string m_status;
    std::string m_mime_type;

    std::stringstream m_buffer;
public:
    response_t() : m_code(200), m_status("OK"), m_mime_type("text/html"), m_buffer() { }
    unsigned int& code() { return m_code; }
    template<typename T>
    std::stringstream& operator<<(T value) {
        m_buffer << value;
        return m_buffer;
    }
    std::string str() {
        return m_buffer.str();
    }
    std::string& status() {
        return m_status;
    }



};

class request_t {
    std::string m_path;
    response_t m_response;

public:
    request_t(const std::string& path) : m_path(path), m_response() { }
    const std::string& path() { return m_path; }
    response_t& response() { return m_response; }

    request_t(const request_t&) = delete;
    request_t& operator=(const request_t&) = delete;

};

class route_t {
protected:
    route_t() { };
    virtual ~route_t() { };
public:
    virtual bool operator()(request_t& path) = 0;
};

template<typename... PARAMS>
class route_impl_t : public route_t {
    std::string m_pattern;
    std::function<void(request_t&, PARAMS...)> m_f;

public:
    route_impl_t(std::string pattern) : m_pattern(pattern), m_f() {
    }
    template<typename LAMDA>
    route_impl_t<PARAMS...>& operator=(LAMDA f) {
        // this assignment fails if f doesn't match the params passed in, which is good
        m_f = f;
        return *this;
    }
    bool operator()(request_t& req) {
        std::function<void(PARAMS...)> wrapped_func = [&](PARAMS... params) { m_f(req, params...); };
        return url_scan(m_pattern, req.path(), wrapped_func);
    }
};

template <typename... PARAMS>
class route_proxy_t {
    typedef std::shared_ptr<route_impl_t<PARAMS...>> route_sptr;  
    route_sptr m_route;
public:
    route_proxy_t(route_sptr route) : m_route(route) { }
    template<typename LAMDA>
    route_proxy_t<PARAMS...>& operator=(LAMDA route) {
        m_route->operator=(route);
        return *this;
    }
    route_proxy_t<PARAMS...>& operator=(route_proxy_t other_proxy) = delete; 
};

class service_t {

    std::vector<std::shared_ptr<route_t>> m_routes;
public:
    service_t() : m_routes() { }
    template<typename... PARAMS>
    route_proxy_t<PARAMS...> map(std::string pattern) {
        std::shared_ptr<route_impl_t<PARAMS...>> route = std::make_shared<route_impl_t<PARAMS...>>(pattern);
        m_routes.push_back(route);
        return route_proxy_t<PARAMS...>(route);
    }

    request_t& serve(request_t& req) {
        bool found = false;
        for (auto& r : m_routes) {
            if (r->operator()(req)) {
                found = true;
                break;
            }
        }
        if (found) {

        }
        else {
            req.response().code() = 404; 
            req.response().status() = "Resource not found"; 
        }
        return req;

    }
};

