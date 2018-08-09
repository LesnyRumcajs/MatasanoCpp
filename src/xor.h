#ifndef MATASANO_XOR_H
#define MATASANO_XOR_H

#include <string>
#include <stdexcept>

namespace matasano {
    std::string xor_hex(const std::string& first, const std::string& second);

    template <class T>
    T xor_container(const T& t1, const T& t2) {
        if (t1.size() != t2.size()) throw std::invalid_argument("buffers not equal!");

        T result;
        for (auto it_first = t1.begin(), it_second = t2.begin(); it_first != t1.end(); ++it_first, ++it_second) {
            result.emplace_back(*it_first ^ *it_second);
        }

        return result;
    }
}

#endif //MATASANO_XOR_H
