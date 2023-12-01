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



int main() {
    clock_t startTime{clock()};

    clock_t endTime{clock()};
    std::cout << endTime - startTime << std::endl;
    return 0;
}
