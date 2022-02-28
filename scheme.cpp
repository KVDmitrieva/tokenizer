#include "error.h"
#include "parser.h"
#include "scheme.h"
#include "tokenizer.h"

#include <sstream>

Interpreter::Interpreter() {
    funcs_["quote"] = std::make_shared<QuoteFunction>(QuoteFunction{});
    funcs_["+"] = std::make_unique<AddFunction>(AddFunction{});
    funcs_["*"] = std::make_shared<MultiplyFunction>(MultiplyFunction{});
    funcs_["-"] = std::make_shared<SubstrFunction>(SubstrFunction{});
    funcs_["/"] = std::make_shared<DivideFunction>(DivideFunction{});
    funcs_["max"] = std::make_shared<MaxFunction>(MaxFunction{});
    funcs_["min"] = std::make_shared<MinFunction>(MinFunction{});
    funcs_["abs"] = std::make_shared<AbsFunction>(AbsFunction{});
    funcs_["number?"] = std::make_shared<NumberFunction>(NumberFunction{});
    funcs_["="] = std::make_shared<EqFunction>(EqFunction{});
    funcs_[">"] = std::make_shared<GFunction>(GFunction{});
    funcs_[">="] = std::make_shared<GEqFunction>(GEqFunction{});
    funcs_["<"] = std::make_shared<LFunction>(LFunction{});
    funcs_["<="] = std::make_shared<LEqFunction>(LEqFunction{});
    funcs_["boolean?"] = std::make_shared<BoolFunction>(BoolFunction{});
    funcs_["not"] = std::make_shared<NotFunction>(NotFunction{});
    funcs_["pair?"] = std::make_shared<PairFunction>(PairFunction{});
    funcs_["list?"] = std::make_shared<ListFunction>(ListFunction{});
    funcs_["null?"] = std::make_shared<NullFunction>(NullFunction{});
    funcs_["and"] = std::make_shared<AndFunction>(AndFunction{});
    funcs_["or"] = std::make_shared<OrFunction>(OrFunction{});
    funcs_["cons"] = std::make_shared<ConsFunction>(ConsFunction{});
    funcs_["car"] = std::make_shared<CarFunction>(CarFunction{});
    funcs_["cdr"] = std::make_shared<CdrFunction>(CdrFunction{});
    funcs_["list"] = std::make_shared<MakeListFunction>(MakeListFunction{});
    funcs_["list-ref"] = std::make_shared<RefFunction>(RefFunction{});
    funcs_["list-tail"] = std::make_shared<TailFunction>(TailFunction{});
}

std::shared_ptr<Object> Interpreter::CheckString(const std::string &obj) {
    if (obj.empty()) {
        return nullptr;
    }
    if (obj == "#t" || obj == "#f") {
        return std::make_shared<Bool>(Bool{obj == "#t"});
    }
    if (obj[0] == '-' || std::isdigit(obj[0])) {
        return std::make_shared<Number>(Number{std::stoi(obj)});
    }
    return std::make_shared<Symbol>(Symbol{obj});
}

void Interpreter::UnpackArgs(std::vector<std::shared_ptr<Object>> &args,
                             std::shared_ptr<Object> object, bool optimizer) {
    if (!object) {
        return;
    }
    if (!Is<Cell>(object)) {
        args.push_back(object);
        return;
    }
    auto obj = As<Cell>(object);
    if (!obj->GetFirst()) {
        args.push_back(nullptr);
        return;
    }
    if (Is<Cell>(obj->GetFirst())) {
        auto cell = As<Cell>(obj->GetFirst());
        if (cell->GetFirst() && Is<Symbol>(cell->GetFirst())) {
            auto res = Evaluate(cell, optimizer);
            args.push_back(CheckString(res));
        } else {
            UnpackArgs(args, cell, optimizer);
        }
    } else {
        args.push_back(obj->GetFirst());
    }
    if (!obj->GetSecond()) {
        return;
    }
    if (Is<Cell>(obj->GetSecond())) {
        auto cell = As<Cell>(obj->GetSecond());
        if (cell->GetFirst() && Is<Symbol>(cell->GetFirst())) {
            auto res = Evaluate(cell);
            args.push_back(CheckString(res));
        } else {
            UnpackArgs(args, cell, optimizer);
        }
    } else {
        args.push_back(obj->GetSecond());
    }
}

std::string Interpreter::Evaluate(std::shared_ptr<Cell> object, bool optimizer) {
    auto first = object->GetFirst();
    if (!first || !Is<Symbol>(first)) {
        throw RuntimeError();
    }
    auto second = object->GetSecond();
    auto symbol = As<Symbol>(first);

    std::vector<std::shared_ptr<Object>> args;

    if (funcs_.find(symbol->GetName()) == funcs_.end()) {
        if (optimizer) {
            return symbol->GetName();
        } else {
            throw NameError();
        }
    }
    auto func = funcs_[symbol->GetName()];
    if (symbol->GetName() == "quote") {
        auto cell = As<Cell>(second);
        args.push_back(cell->GetFirst());
        return func->Invoke(args);
    }
    if (symbol->GetName() == "and" || symbol->GetName() == "or") {
        optimizer = true;
    }
    UnpackArgs(args, second, optimizer);
    if (args.size() > 1 && !args.back()) {
        args.pop_back();
    }
    return func->Invoke(args);
}

std::string Interpreter::Expand(std::shared_ptr<Object> object) {
    if (!object) {
        throw RuntimeError();
    }
    if (Is<Number>(object)) {
        return std::to_string(As<Number>(object)->GetValue());
    }
    if (Is<Bool>(object)) {
        return (As<Bool>(object)->GetBool()) ? "#t" : "#f";
    }
    if (Is<Symbol>(object)) {
        auto symbol = As<Symbol>(object);
        if (funcs_.find(symbol->GetName()) == funcs_.end()) {
            throw NameError();
        }
        throw RuntimeError();
    }
    return Evaluate(As<Cell>(object));
}

std::string Interpreter::Run(const std::string &expression) {
    std::stringstream exp{expression};
    Tokenizer tokenizer{&exp};
    auto obj = Read(&tokenizer);
    if (!tokenizer.IsEnd()) {
        throw SyntaxError();
    }
    return Expand(obj);
}