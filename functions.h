#pragma once

#include "object.h"

#include <string>
#include <vector>

class IFunction {
public:
    virtual ~IFunction() = default;
    virtual std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) = 0;
};

class QuoteFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;

private:
    std::string CellHelper(std::shared_ptr<Cell> cell);
    std::string ObjectHelper(std::shared_ptr<Object> obj);
};

class AddFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class MultiplyFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class SubstrFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class DivideFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class MaxFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class MinFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class AbsFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class NumberFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class EqFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class LFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};
class LEqFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class GFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};
class GEqFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class BoolFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class NotFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class PairFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class ListFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class NullFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class AndFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class OrFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class MakeListFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class RefFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class TailFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class ConsFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class CarFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};

class CdrFunction : public IFunction {
public:
    std::string Invoke(const std::vector<std::shared_ptr<Object>>& args) override;
};
