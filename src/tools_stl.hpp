#ifndef MATASANOCPP_TOOLS_STL_HPP
#define MATASANOCPP_TOOLS_STL_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

namespace tools::stl {
    template<typename T>
    struct VectorHash {
        size_t operator()(const std::vector<T> &v) const {
            std::hash<T> hasher;
            size_t seed{0};
            for (auto i : v) {
                seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}

#endif //MATASANOCPP_TOOLS_STL_HPP
