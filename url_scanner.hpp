#pragma once
#include <tuple>
#include <string>
#include <stdexcept>
#include <functional>

template<typename...PARAMS, typename ITERATOR>
bool url_scan2(std::tuple<>, ITERATOR pattern,ITERATOR path,ITERATOR pattern_end,ITERATOR path_end, std::function<void(PARAMS...)>& f, PARAMS... params) {
    while (path != path_end && pattern != pattern_end) {
        // There maybe some text after the last %, deal with it.
        if (*path != *pattern) {
            return false;
        }
        path++;
        pattern++;
    }
    if (path != path_end || pattern != pattern_end) {
        return false;
    }
    f(params...);
    return true;
}

template<typename... PARAMS, typename... PARAMS_IN, typename... PARAMS_OUT, typename ITERATOR>
bool url_scan2(std::tuple<int,PARAMS_IN...>, ITERATOR pattern, ITERATOR path, ITERATOR pattern_end, ITERATOR path_end, std::function<void(PARAMS...)>& f, PARAMS_OUT... params) {

    // At this point we know there's at least one more % to find as the std::tuple has at least one type in it (PARAMS_IN... could be empty).
    // effectively each recursion takes the head of the tuple's types and moves it to the back of the arguments list (PARAMS_OUT).

    // this should never happen....
    static_assert(sizeof...(PARAMS_IN) + sizeof...(PARAMS_OUT) + 1 == sizeof...(PARAMS), "template error:expected 1+PARAMS_IN+PARAMS_OUT=PARAMS");

    // probably pointless templating...
    typename ITERATOR::value_type current_pattern;
    typename ITERATOR::value_type current_path;
    // I feel bad about a while(true) but this genuinely feels like the cleanest
    //  fastest way. Loop until we see a % or something goes wrong.
    while (true) {
        current_pattern = *pattern;
        current_path = *path;
        path++;
        pattern++;
        if (current_pattern == '%') {
            break;
        }
        else if (current_pattern != current_path) {
            return false;
        }
        else if (pattern == pattern_end || path == path_end) {
            return false;
        }

    }
    std::string raw_value(1,current_path);


    // this is the only bit that's specifically about ints, needs to be refactored out.
    if (!std::isdigit(current_path))
        return false;

    while (std::isdigit(*path) && path != path_end) {
        raw_value += *path;
        path++;
    };
    int value = std::stoi(raw_value);

    return url_scan2(std::tuple<PARAMS_IN...>(), pattern, path, pattern_end, path_end, f, params..., value);
}



template<typename... PARAMS>
bool url_scan(std::string pattern, std::string path, std::function<void(PARAMS...)>& f) {
    // Have to do something awkward with tuples as parameter unpacking doesn't seem to work properly
    //  with explicit templates.
    return url_scan2(std::tuple<PARAMS...>(), pattern.begin(), path.begin(), pattern.end(), path.end(), f);
}


