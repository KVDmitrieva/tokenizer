#include "functions.h"
#include "error.h"

std::string QuoteFunction::ObjectHelper(std::shared_ptr<Object> obj) {
    if (Is<Number>(obj)) {
        return std::to_string(As<Number>(obj)->GetValue());
    }
    if (Is<Bool>(obj)) {
        return As<Bool>(obj)->GetBool() ? "#t" : "#f";
    }
    if (Is<Symbol>(obj)) {
        return As<Symbol>(obj)->GetName();
    }
    return CellHelper(As<Cell>(obj));
}

std::string QuoteFunction::CellHelper(std::shared_ptr<Cell> cell) {
    if (!cell->GetFirst()) {
        return "()";
    }
    if (!cell->GetSecond()) {
        return ObjectHelper(cell->GetFirst());
    }
    if (Is<Number>(cell->GetFirst()) && Is<Number>(cell->GetSecond())) {
        return std::to_string(As<Number>(cell->GetFirst())->GetValue()) + " . " +
               std::to_string(As<Number>(cell->GetSecond())->GetValue());
    }
    return ObjectHelper(cell->GetFirst()) + " " + ObjectHelper(cell->GetSecond());
}

std::string QuoteFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 1) {
        throw RuntimeError();
    }
    if (args[0] == nullptr) {
        return "()";
    }
    if (Is<Symbol>(args[0])) {
        auto ptr = As<Symbol>(args[0]);
        return ptr->GetName();
    }
    if (Is<Bool>(args[0])) {
        auto ptr = As<Bool>(args[0]);
        return (ptr->GetBool()) ? "#t" : "#f";
    }
    if (Is<Number>(args[0])) {
        auto ptr = As<Number>(args[0]);
        return std::to_string(ptr->GetValue());
    }
    return "(" + CellHelper(As<Cell>(args[0])) + ")";
}

std::string AddFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    int64_t res = 0;
    for (auto& arg : args) {
        if (!arg || !Is<Number>(arg)) {
            throw RuntimeError();
        }
        res += As<Number>(arg)->GetValue();
    }
    return std::to_string(res);
}

std::string MultiplyFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    int64_t res = 1;
    for (auto& arg : args) {
        if (!arg || !Is<Number>(arg)) {
            throw RuntimeError();
        }
        res *= As<Number>(arg)->GetValue();
    }
    return std::to_string(res);
}

std::string SubstrFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.empty() || !Is<Number>(args[0])) {
        throw RuntimeError();
    }
    int64_t res = As<Number>(args[0])->GetValue();
    for (size_t i = 1; i < args.size(); ++i) {
        if (!args[i] || !Is<Number>(args[i])) {
            throw RuntimeError();
        }
        res -= As<Number>(args[i])->GetValue();
    }
    return std::to_string(res);
}

std::string DivideFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.empty() || !Is<Number>(args[0])) {
        throw RuntimeError();
    }
    int64_t res = As<Number>(args[0])->GetValue();
    for (size_t i = 1; i < args.size(); ++i) {
        if (!args[i] || !Is<Number>(args[i])) {
            throw RuntimeError();
        }
        res /= As<Number>(args[i])->GetValue();
    }
    return std::to_string(res);
}

std::string MaxFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.empty() || !Is<Number>(args[0])) {
        throw RuntimeError();
    }
    int64_t res = As<Number>(args[0])->GetValue();
    for (auto& arg : args) {
        if (!arg || !Is<Number>(arg)) {
            throw RuntimeError();
        }
        res = std::max(res, As<Number>(arg)->GetValue());
    }
    return std::to_string(res);
}

std::string MinFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.empty() || !Is<Number>(args[0])) {
        throw RuntimeError();
    }
    int64_t res = As<Number>(args[0])->GetValue();
    for (auto& arg : args) {
        if (!arg || !Is<Number>(arg)) {
            throw RuntimeError();
        }
        res = std::min(res, As<Number>(arg)->GetValue());
    }
    return std::to_string(res);
}

std::string AbsFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 1 || !Is<Number>(args[0])) {
        throw RuntimeError();
    }
    int64_t res = std::abs(As<Number>(args[0])->GetValue());
    return std::to_string(res);
}

std::string NumberFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 1) {
        throw RuntimeError();
    }
    return (Is<Number>(args[0])) ? "#t" : "#f";
}

std::string EqFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    bool res = true;
    if (!args.empty() && !Is<Number>(args[0])) {
        throw RuntimeError();
    }
    int64_t prev = 0;
    if (!args.empty()) {
        prev = As<Number>(args[0])->GetValue();
    }
    for (size_t i = 1; i < args.size() && res; ++i) {
        if (!args[i] || !Is<Number>(args[i])) {
            throw RuntimeError();
        }
        int cur = As<Number>(args[i])->GetValue();
        res = prev == cur;
        prev = cur;
    }
    return (res) ? "#t" : "#f";
}

std::string LFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    bool res = true;
    if (!args.empty() && !Is<Number>(args[0])) {
        throw RuntimeError();
    }
    int64_t prev = 0;
    if (!args.empty()) {
        prev = As<Number>(args[0])->GetValue();
    }
    for (size_t i = 1; i < args.size() && res; ++i) {
        if (!args[i] || !Is<Number>(args[i])) {
            throw RuntimeError();
        }
        int cur = As<Number>(args[i])->GetValue();
        res = prev < cur;
        prev = cur;
    }
    return (res) ? "#t" : "#f";
}

std::string LEqFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    bool res = true;
    if (!args.empty() && !Is<Number>(args[0])) {
        throw RuntimeError();
    }
    int64_t prev = 0;
    if (!args.empty()) {
        prev = As<Number>(args[0])->GetValue();
    }
    for (size_t i = 1; i < args.size() && res; ++i) {
        if (!args[i] || !Is<Number>(args[i])) {
            throw RuntimeError();
        }
        int cur = As<Number>(args[i])->GetValue();
        res = prev <= cur;
        prev = cur;
    }
    return (res) ? "#t" : "#f";
}

std::string GFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    bool res = true;
    if (!args.empty() && !Is<Number>(args[0])) {
        throw RuntimeError();
    }
    int64_t prev = 0;
    if (!args.empty()) {
        prev = As<Number>(args[0])->GetValue();
    }
    for (size_t i = 1; i < args.size() && res; ++i) {
        if (!args[i] || !Is<Number>(args[i])) {
            throw RuntimeError();
        }
        int cur = As<Number>(args[i])->GetValue();
        res = prev > cur;
        prev = cur;
    }
    return (res) ? "#t" : "#f";
}

std::string GEqFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    bool res = true;
    if (!args.empty() && !Is<Number>(args[0])) {
        throw RuntimeError();
    }
    int64_t prev = 0;
    if (!args.empty()) {
        prev = As<Number>(args[0])->GetValue();
    }
    for (size_t i = 1; i < args.size() && res; ++i) {
        if (!args[i] || !Is<Number>(args[i])) {
            throw RuntimeError();
        }
        int cur = As<Number>(args[i])->GetValue();
        res = prev >= cur;
        prev = cur;
    }
    return (res) ? "#t" : "#f";
}

std::string BoolFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 1 || !args[0]) {
        throw RuntimeError();
    }
    return (Is<Bool>(args[0]) ? "#t" : "#f");
}

std::string NotFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 1) {
        throw RuntimeError();
    }
    bool res = false;
    if (args[0] && Is<Bool>(args[0]) && !As<Bool>(args[0])->GetBool()) {
        res = true;
    }
    return (res) ? "#t" : "#f";
}

std::string PairFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 1 || !Is<Symbol>(args[0])) {
        throw RuntimeError();
    }
    auto str = As<Symbol>(args[0])->GetName();
    bool res = true;
    if (str.front() != '(' || str.back() != ')') {
        res = false;
    }
    size_t count = 0;
    bool del = true;
    for (size_t i = 1; i < str.size() - 1 && res; ++i) {
        if (std::isdigit(str[i])) {
            if (del) {
                del = false;
                ++count;
            }
        } else if (str[i] == ' ' || str[i] == '.') {
            del = true;
        }
    }
    if (count != 2) {
        res = false;
    }
    return (res) ? "#t" : "#f";
}

std::string ListFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 1 || !Is<Symbol>(args[0])) {
        throw RuntimeError();
    }
    return (As<Symbol>(args[0])->GetName().find(".") == std::string::npos) ? "#t" : "#f";
}

std::string NullFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 1 || !Is<Symbol>(args[0])) {
        throw RuntimeError();
    }
    return (As<Symbol>(args[0])->GetName() == "()") ? "#t" : "#f";
}

std::string AndFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.empty()) {
        return "#t";
    }
    for (auto& arg : args) {
        if (arg && Is<Bool>(arg) && !As<Bool>(arg)->GetBool()) {
            return "#f";
        }
    }
    if (args.back()) {
        return args.back()->ToString();
    }
    return "";
}

std::string OrFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.empty()) {
        return "#f";
    }
    for (auto& arg : args) {
        if (arg && Is<Bool>(arg) && As<Bool>(arg)->GetBool()) {
            return "#t";
        }
    }
    if (args.back()) {
        return args.back()->ToString();
    }
    return "";
}

std::string MakeListFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    std::string res;
    for (auto& arg : args) {
        if (!arg || !Is<Number>(arg)) {
            throw RuntimeError();
        }
        res += arg->ToString() + ' ';
    }
    if (!res.empty()) {
        res.pop_back();
    }
    return "(" + res + ")";
}

std::string ConsFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    std::string res;
    for (auto& arg : args) {
        if (!arg || !Is<Number>(arg)) {
            throw RuntimeError();
        }
        res += arg->ToString() + " . ";
    }
    if (!res.empty()) {
        res = res.substr(0, res.size() - 3);
    }
    return "(" + res + ")";
}

std::string CarFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 1 || !args[0] || args[0]->ToString() == "()") {
        throw RuntimeError();
    }
    std::string cur = args[0]->ToString();
    std::string res;
    for (size_t i = 1; i < cur.size() - 1; ++i) {
        if (std::isdigit(cur[i])) {
            res += cur[i];
        } else {
            break;
        }
    }
    return res;
}

std::string CdrFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 1 || !args[0] || args[0]->ToString() == "()") {
        throw RuntimeError();
    }
    std::string cur = args[0]->ToString();
    if (cur.find(' ') == cur.npos) {
        return "()";
    }
    if (cur.find('.') != cur.npos && cur.find(' ') + 1 == cur.find('.')) {
        cur.pop_back();
        return cur.substr(cur.find('.') + 2, cur.size());
    }
    return "(" + cur.substr(cur.find(' ') + 1, cur.size());
}

std::string RefFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 2 || !Is<Symbol>(args[0]) || !Is<Number>(args[1])) {
        throw RuntimeError();
    }
    auto str = As<Symbol>(args[0])->GetName();
    int64_t num = As<Number>(args[1])->GetValue();

    if (str.front() != '(' || str.back() != ')') {
        throw RuntimeError();
    }
    int64_t count = 0;
    std::string res;
    bool del = true;
    for (size_t i = 1; i < str.size() - 1; ++i) {
        if (std::isdigit(str[i])) {
            if (del) {
                del = false;
                ++count;
            }
            if (count - 1 == num) {
                res += str[i];
            }
        } else if (str[i] == ' ' || str[i] == '.') {
            del = true;
            if (count - 1 == num) {
                break;
            }
        }
    }
    if (res.empty()) {
        throw RuntimeError();
    }
    return res;
}

std::string TailFunction::Invoke(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 2 || !Is<Symbol>(args[0]) || !Is<Number>(args[1])) {
        throw RuntimeError();
    }
    auto str = As<Symbol>(args[0])->GetName();
    int64_t num = As<Number>(args[1])->GetValue();

    if (str.front() != '(' || str.back() != ')') {
        throw RuntimeError();
    }
    int64_t count = 0;
    std::string res;
    bool del = true;
    for (size_t i = 1; i < str.size() - 1; ++i) {
        if (std::isdigit(str[i])) {
            if (del) {
                del = false;
                ++count;
            }
            if (count - 1 >= num) {
                res += str[i];
            }
        } else if (str[i] == ' ' || str[i] == '.') {
            del = true;
            if (count - 1 >= num) {
                res += str[i];
            }
        }
    }
    if (res.empty() && count < num) {
        throw RuntimeError();
    }

    return "(" + res + ")";
}
