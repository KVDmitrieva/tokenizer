#include "parser.h"
#include "error.h"

std::shared_ptr<Object> MakeCell(std::queue<std::shared_ptr<Object>>& objects) {
    if (objects.empty()) {
        return nullptr;
    }
    std::shared_ptr<Object> first, second;
    first = objects.front();
    objects.pop();
    if (Is<Symbol>(first) && As<Symbol>(first)->GetName() == ".") {
        throw SyntaxError();
    }
    if (objects.empty()) {
        second = nullptr;
    } else if (objects.size() == 1 && !objects.front()) {
        if (Is<Symbol>(first)) {
            second = std::make_shared<Cell>(nullptr, nullptr);
        }
    } else if (Is<Symbol>(objects.front()) && As<Symbol>(objects.front())->GetName() == ".") {
        if (objects.size() == 2) {
            second = objects.back();
            objects.pop();
            objects.pop();
        } else {
            throw SyntaxError();
        }
    } else {
        second = MakeCell(objects);
    }
    return std::make_shared<Cell>(first, second);
}

std::shared_ptr<Object> Read(Tokenizer* tokenizer) {
    if (tokenizer->IsEnd()) {
        throw SyntaxError();
    }
    auto token = tokenizer->GetToken();
    tokenizer->Next();

    if (ConstantToken* x = std::get_if<ConstantToken>(&token)) {
        return std::make_shared<Number>(x->value);
    } else if (BoolToken* b = std::get_if<BoolToken>(&token)) {
        return std::make_shared<Bool>(b->bool_);
    } else if (SymbolToken* symbol = std::get_if<SymbolToken>(&token)) {
        return std::make_shared<Symbol>(symbol->name);
    } else if (std::get_if<QuoteToken>(&token)) {
        if (tokenizer->IsEnd()) {
            throw SyntaxError();
        }
        std::queue<std::shared_ptr<Object>> objects;
        objects.push(std::make_shared<Symbol>("quote"));
        auto arg = Read(tokenizer);
        objects.push(arg);
        return MakeCell(objects);
    } else if (std::get_if<DotToken>(&token)) {
        return std::make_shared<Symbol>(".");
    } else if (BracketToken* bracket = std::get_if<BracketToken>(&token)) {
        if (*bracket == BracketToken::CLOSE) {
            return std::make_shared<Symbol>(")");
        } else {
            return ReadList(tokenizer);
        }
    }
    return nullptr;
}

std::shared_ptr<Object> ReadList(Tokenizer* tokenizer) {
    if (tokenizer->IsEnd()) {
        throw SyntaxError();
    }
    std::queue<std::shared_ptr<Object>> objects;
    while (true) {
        auto tmp = Read(tokenizer);
        if (Is<Symbol>(tmp) && As<Symbol>(tmp)->GetName() == ")") {
            break;
        }
        objects.push(tmp);
        if (tokenizer->IsEnd()) {
            throw SyntaxError();
        }
    }
    return MakeCell(objects);
}
