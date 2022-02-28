#pragma once

#include <memory>

class Object : public std::enable_shared_from_this<Object> {
public:
    virtual ~Object() = default;
    virtual std::string ToString() = 0;
};

class Number : public Object {
public:
    Number(int v) : val_(v) {
    }

    int64_t GetValue() const {
        return val_;
    }

    std::string ToString() override {
        return std::to_string(val_);
    }

private:
    int64_t val_;
};

class Bool : public Object {
public:
    Bool(bool b) : bool_(b) {
    }

    bool GetBool() {
        return bool_;
    }

    std::string ToString() override {
        return (bool_) ? "#t" : "#f";
    }

private:
    bool bool_;
};

class Symbol : public Object {
public:
    Symbol(const std::string& s) : name_(s) {
    }

    const std::string& GetName() const {
        return name_;
    }

    std::string ToString() override {
        return name_;
    }

private:
    std::string name_;
};

class Cell : public Object {
public:
    Cell(const std::shared_ptr<Object>& f, const std::shared_ptr<Object>& s)
        : first_(f), second_(s) {
    }

    std::shared_ptr<Object> GetFirst() const {
        return first_;
    }
    std::shared_ptr<Object> GetSecond() const {
        return second_;
    }

    std::string ToString() override {
        if (first_ && second_) {
            return first_->ToString() + second_->ToString();
        }
        if (first_) {
            return first_->ToString();
        }
        if (second_) {
            return second_->ToString();
        }
        return "()";
    }

private:
    std::shared_ptr<Object> first_, second_;
};

template <class T>
std::shared_ptr<T> As(const std::shared_ptr<Object>& obj) {
    return std::dynamic_pointer_cast<T>(obj);
}

template <class T>
bool Is(const std::shared_ptr<Object>& obj) {
    return dynamic_cast<T*>(obj.get());
}
