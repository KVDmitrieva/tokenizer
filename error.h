#pragma once

#include <stdexcept>

class SyntaxError : public std::runtime_error {
public:
    SyntaxError() : std::runtime_error("syntax error") {
    }
};

class RuntimeError : public std::runtime_error {
public:
    RuntimeError() : std::runtime_error("runtime error") {
    }
};

class NameError : public std::runtime_error {
public:
    NameError() : std::runtime_error("name error") {
    }
};