#pragma once

#include "functions.h"
#include "object.h"

#include <map>
#include <memory>
#include <string>

class Interpreter {
public:
    Interpreter();
    std::string Run(const std::string& expression);

private:
    std::string Expand(std::shared_ptr<Object> object);
    std::string Evaluate(std::shared_ptr<Cell> object, bool optimizer = false);
    void UnpackArgs(std::vector<std::shared_ptr<Object>>& args, std::shared_ptr<Object> obj,
                    bool optimizer = false);
    std::shared_ptr<Object> CheckString(const std::string& obj);
    std::map<std::string, std::shared_ptr<IFunction>> funcs_;
};