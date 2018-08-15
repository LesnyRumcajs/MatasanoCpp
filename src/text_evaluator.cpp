#include <algorithm>
#include "text_evaluator.hpp"

int TextEvaluator::score(const std::string &text) const {
    return std::accumulate(text.begin(), text.end(), 0, [](int sum, char ch) {
        return sum + evaluate(ch);
    });
}

int TextEvaluator::score(char ch) const {
    return evaluate(ch);
}

int TextEvaluator::score(const std::vector<uint8_t> &text) const {
    return std::accumulate(text.begin(), text.end(), 0, [](int sum, char ch) {
        return sum + evaluate(ch);
    });
}

int TextEvaluator::evaluate(char ch) {
    static const int BINARY_CHAR_SCORE{0};
    static const int PRINTABLE_CHAR_SCORE{2};
    static const int ALPHA_CHAR_SCORE{4};
    static const int POPULAR_CHAR_SCORE{5};

    static const std::vector<uint8_t> popular_chars{'e', 't', 'a', 'i', 'n', ' ', 's', 'h', 'r', 'd', 'l', 'u',
                                                    'E', 'T', 'A', 'I', 'N', ' ', 'S', 'H', 'R', 'D', 'L', 'U'};
    if (ch >= 0x20 && ch < 0x7F) {
        if (std::find(popular_chars.begin(), popular_chars.end(), ch) != popular_chars.end()) {
            return POPULAR_CHAR_SCORE;
        } else if (std::isalpha(ch)) {
            return ALPHA_CHAR_SCORE;
        }
        return PRINTABLE_CHAR_SCORE;
    }

    return BINARY_CHAR_SCORE;
}
