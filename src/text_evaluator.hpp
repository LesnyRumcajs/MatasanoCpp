#ifndef MATASANOCPP_TEXT_EVALUATOR_HPP
#define MATASANOCPP_TEXT_EVALUATOR_HPP


#include <map>
#include <vector>

class TextEvaluator {
public:
    int score(const std::string &text) const;

    int score(char ch) const;

    int score(const std::vector<uint8_t> &text) const;

private:
    static int evaluate(char ch);
};


#endif //MATASANOCPP_TEXT_EVALUATOR_HPP
