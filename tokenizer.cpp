#include "tokenizer.h"
#include "error.h"

Tokenizer::Tokenizer(std::istream *in) {
    in_ = in;
    Next();
}

bool Tokenizer::IsEnd() {
    return end_;
}

void Tokenizer::Next() {
    char first = in_->get();
    while (std::isspace(first)) {
        first = in_->get();
    }
    std::set<char> allowed = {'<', '=', '>', '*', '/', '#'};
    if (first == EOF) {
        end_ = true;
    } else if (first == '(') {
        tokens_ = BracketToken{BracketToken::OPEN};
    } else if (first == ')') {
        tokens_ = BracketToken{BracketToken::CLOSE};
    } else if (first == '\'') {
        tokens_ = QuoteToken();
    } else if (first == '.') {
        tokens_ = DotToken();
    } else if (std::isdigit(first) || first == '+' || first == '-') {
        std::string tmp;
        tmp.push_back(first);
        first = in_->get();
        while (std::isdigit(first)) {
            tmp.push_back(first);
            first = in_->get();
        }
        in_->unget();

        if (tmp == "+" || tmp == "-") {
            tokens_ = SymbolToken(tmp);
        } else {
            tokens_ = ConstantToken(std::stoi(tmp));
        }
    } else if (std::isalpha(first) || allowed.find(first) != allowed.end()) {
        std::string tmp;
        tmp.push_back(first);
        allowed.insert('?');
        allowed.insert('!');
        allowed.insert('-');
        first = in_->get();
        while (std::isalpha(first) || std::isdigit(first) || allowed.find(first) != allowed.end()) {
            tmp.push_back(first);
            first = in_->get();
        }
        in_->unget();
        if (tmp == "#t" || tmp == "#f") {
            tokens_ = BoolToken(tmp);
        } else {
            tokens_ = SymbolToken(tmp);
        }
    } else {
        throw SyntaxError();
    }
}

Token Tokenizer::GetToken() {
    return tokens_;
}