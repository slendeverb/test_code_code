#include <stdlib.h>
#include <windows.h>
#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <compare>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <format>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <numbers>
#include <optional>
#include <set>
#include <span>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
//
class SpreadsheetCell {
   public:
    virtual ~SpreadsheetCell() = default;
    virtual void set(std::string_view value) = 0;
    virtual std::string getString() const = 0;
};

class StringSpreadsheetCell : public SpreadsheetCell {
   public:
    void set(std::string_view value) override { m_value = value; }
    std::string getString() const override { return m_value.value_or(""); }

   private:
    std::optional<std::string> m_value;
};

class DoubleSpreadsheetCell : public SpreadsheetCell {
   public:
    virtual void set(double value) { m_value = value; }
    void set(std::string_view value) override {
        m_value = stringToDouble(value);
    }
    std::string getString() const override {
        return (m_value.has_value() ? doubleToString(m_value.value()) : "");
    }

   private:
    static std::string doubleToString(double value) {
        return std::to_string(value);
    }
    static double stringToDouble(std::string_view value) {
        double retValue;
        std::from_chars(value.data(), value.data() + value.size(), retValue);
        return retValue;
    }
    std::optional<double> m_value;
};

int main() {
    clock_t startTime{clock()};

    clock_t endTime{clock()};
    std::cout << endTime - startTime << std::endl;
    return 0;
}
