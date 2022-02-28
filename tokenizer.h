#pragma once

#include "../error.h"

#include <variant>
#include <optional>
#include <istream>
#include <vector>
#include <set>
#include <memory>

struct SymbolToken {
    std::string name;

    SymbolToken(const std::string& s) : name(s) {
    }

    bool operator==(const SymbolToken& other) const {
        return name == other.name;
    }
};

struct QuoteToken {
    bool operator==(const QuoteToken&) const {
        return true;
    }
};

struct DotToken {
    bool operator==(const DotToken&) const {
        return true;
    }
};

enum class BracketToken { OPEN, CLOSE };

struct ConstantToken {
    int value;

    ConstantToken(int val) : value(val) {
    }

    bool operator==(const ConstantToken& other) const {
        return value == other.value;
    }
};

struct BoolToken {
    bool bool_;

    BoolToken(const std::string& b) {
        bool_ = b == "#t";
    }

    bool operator==(const BoolToken& other) const {
        return (bool_ && other.bool_) || (!bool_ && !other.bool_);
    }
};

using Token =
    std::variant<ConstantToken, BracketToken, SymbolToken, QuoteToken, DotToken, BoolToken>;

class Tokenizer {
public:
    Tokenizer(std::istream* in);

    bool IsEnd();

    void Next();

    Token GetToken();

private:
    std::istream* in_;
    bool end_ = false;
    Token tokens_ = DotToken();
};