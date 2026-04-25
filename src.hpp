#include <vector>

template <typename T>
class Validator {
private:
    T value;
    bool result;
    bool negate_mode;

public:
    Validator(const T& val) : value(val), result(true), negate_mode(false) {}

    Validator& toBe(const T& other) {
        bool condition = (value == other);
        if (negate_mode) {
            condition = !condition;
        }
        result = result && condition;
        return *this;
    }

    Validator& toBeOneOf(const std::vector<T>& vec) {
        bool found = false;
        for (const T& elem : vec) {
            if (value == elem) {
                found = true;
                break;
            }
        }
        bool condition = found;
        if (negate_mode) {
            condition = !condition;
        }
        result = result && condition;
        return *this;
    }

    Validator& le(const T& other) {
        bool condition = !(other < value);  // value <= other is equivalent to !(other < value)
        if (negate_mode) {
            condition = !condition;
        }
        result = result && condition;
        return *this;
    }

    Validator& ge(const T& other) {
        bool condition = !(value < other);  // value >= other is equivalent to !(value < other)
        if (negate_mode) {
            condition = !condition;
        }
        result = result && condition;
        return *this;
    }

    Validator& lt(const T& other) {
        bool condition = (value < other);
        if (negate_mode) {
            condition = !condition;
        }
        result = result && condition;
        return *this;
    }

    Validator& gt(const T& other) {
        bool condition = (other < value);  // value > other is equivalent to other < value
        if (negate_mode) {
            condition = !condition;
        }
        result = result && condition;
        return *this;
    }

    Validator& Not() {
        negate_mode = true;
        return *this;
    }

    operator bool() const {
        return result;
    }
};

template <typename T>
Validator<T> expect(const T& value) {
    return Validator<T>(value);
}
