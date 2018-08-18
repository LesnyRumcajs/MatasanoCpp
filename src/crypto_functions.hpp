#ifndef MATASANOCPP_CRYPTO_FUNCTIONS_HPP
#define MATASANOCPP_CRYPTO_FUNCTIONS_HPP

#include <stdexcept>
#include <boost/range/combine.hpp>

namespace crypto::functions {
    /**
     * Calculates the Hamming Distance (number of differing bits) between two strings
     * @tparam T container type
     * @param first first container
     * @param second second container
     * @return Hamming Distance
     */
    template<typename T>
    int hamming_distance(const T &first, const T &second) {
        if (first.size() != second.size()) {
            throw std::invalid_argument("objects not of equal size!");
        }

        int distance{0};
        for (const auto &i : boost::combine(first, second)) {
            unsigned el1, el2;
            boost::tie(el1, el2) = i;
            distance += __builtin_popcount(el1 ^ el2);
        }
        return distance;
    }
}

#endif //MATASANOCPP_CRYPTO_FUNCTIONS_HPP
