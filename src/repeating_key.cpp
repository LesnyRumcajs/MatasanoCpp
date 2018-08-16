//
// Created by rumcajs on 8/16/18.
//

#include <stdexcept>
#include <vector>
#include "repeating_key.hpp"

RepeatingKey::RepeatingKey(const std::vector<uint8_t> &key) : m_key(key) {
    init_key();
}

RepeatingKey::RepeatingKey(const std::string &key) : m_key(key.begin(), key.end()) {
    init_key();
}

uint8_t RepeatingKey::next() {
    auto result = *m_current_pos;

    if (m_current_pos == m_key.end() - 1) {
        m_current_pos = m_key.begin();
    } else {
        ++m_current_pos;
    }

    return result;
}

void RepeatingKey::init_key() {
    if (m_key.empty()) {
        throw std::invalid_argument("key can't be empty!");
    }
    m_current_pos = m_key.begin();
}
