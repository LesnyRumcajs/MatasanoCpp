#ifndef MATASANOCPP_ENCRYPTION_ORACLE_HPP
#define MATASANOCPP_ENCRYPTION_ORACLE_HPP


#include <cstdint>
#include <vector>

class EncryptionOracle {
public:
    enum class ORACLE_MODE {
        ECB,
        CBC
    };

    std::pair<std::vector<uint8_t>, ORACLE_MODE> encrypt(std::vector<uint8_t> plaintext);

private:
    void add_random_bytes(std::vector<uint8_t> &data, std::vector<uint8_t>::iterator iterator);

    static unsigned long generate_random_number(unsigned long lower_bound, unsigned long upper_bound);
};


#endif //MATASANOCPP_ENCRYPTION_ORACLE_HPP
