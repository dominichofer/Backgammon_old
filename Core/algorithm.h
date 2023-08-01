#pragma once
#include <algorithm>
#include <cstdint>
#include <map>
#include <string>

namespace detail
{
    template <typename T>
    struct reversion_wrapper { T& iterable; };

    template <typename T>
    auto begin(reversion_wrapper<T> w) { return std::rbegin(w.iterable); }

    template <typename T>
    auto end(reversion_wrapper<T> w) { return std::rend(w.iterable); }
}

template <typename T>
detail::reversion_wrapper<T> reverse(T&& iterable) { return {iterable}; }


inline uint64_t Binomial(uint64_t n, uint64_t k)
{
    uint64_t res = 1; 
    if (k > n - k) 
        k = n - k; 
    for (uint64_t i = 0; i < k; ++i)
    { 
        res *= (n - i); 
        res /= (i + 1); 
    }
    return res;
}

// The number of ways in which n indistinguishable balls can be distributed into k distinguishable boxes.
inline uint64_t MultisetNumber(int n, int k) { return Binomial(n + k - 1, n); }

template <class Iterable>
std::string join(const std::string& delimiter, const Iterable& iterable)
{
    using std::to_string;

    if (std::empty(iterable))
        return {};
    
    std::string ret = to_string(*std::begin(iterable));
    for (auto it = std::begin(iterable) + 1; it != std::end(iterable); ++it)
        ret += delimiter + to_string(*it);
    return ret;
}

template <class Iterable>
std::string join(char delimiter, const Iterable& iterable)
{
    return join(std::string{delimiter}, iterable);
}
