#pragma once
#include <url_scanner.hpp>
#include <response.hpp>
#include <request.hpp>

#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <memory>
#include <sstream>
#include <fstream>
#include <map>

namespace cpplask {
bool serve_static_file(request& req, path path);

class route {
protected:
    route() { };
    virtual ~route() { };
public:
    virtual bool operator()(request& path) = 0;
};

template<typename... PARAMS>
class route_impl : public route {
    std::string m_pattern;
    std::function<void(request&, PARAMS...)> m_f;

public:
    route_impl(std::string pattern) : m_pattern(pattern), m_f() {
    }
    template<typename LAMDA>
    route_impl<PARAMS...>& operator=(LAMDA f) {
        // this assignment fails if f doesn't match the params passed in, which is good
        m_f = f;
        return *this;
    }
    bool operator()(request& req) {
        std::function<void(PARAMS...)> wrapped_func = [&](PARAMS... params) { m_f(req, params...); };
        return url_scan(m_pattern, req.path(), wrapped_func);
    }
};

template <typename... PARAMS>
class route_proxy {
    typedef std::shared_ptr<route_impl<PARAMS...>> route_sptr;  
    route_sptr m_route;
public:
    route_proxy(route_sptr route) : m_route(route) { }
    template<typename LAMDA>
    route_proxy<PARAMS...>& operator=(LAMDA route) {
        m_route->operator=(route);
        return *this;
    }
    route_proxy<PARAMS...>& operator=(route_proxy other_proxy) = delete; 
};

class service {

    std::vector<std::shared_ptr<route>> m_routes;
public:
    service() : m_routes() { }
    template<typename... PARAMS>
    route_proxy<PARAMS...> map(std::string pattern) {
        std::shared_ptr<route_impl<PARAMS...>> route = std::make_shared<route_impl<PARAMS...>>(pattern);
        m_routes.push_back(route);
        return route_proxy<PARAMS...>(route);
    }

    request& serve(request& req) {
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

}
