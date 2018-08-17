#ifndef MATASANOCPP_REPEATING_KEY_HPP
#define MATASANOCPP_REPEATING_KEY_HPP


#include <string>
#include <vector>

class RepeatingKey {
public:
    explicit RepeatingKey(const std::vector<uint8_t> &key);

    explicit RepeatingKey(const std::string &key);

    /**
     * gets the next key character and rotates
     * @return next key character
     */
    uint8_t next();

private:
    void init_key();

    std::vector<uint8_t>::const_iterator m_current_pos;
    std::vector<uint8_t> m_key;
};


#endif //MATASANOCPP_REPEATING_KEY_HPP
