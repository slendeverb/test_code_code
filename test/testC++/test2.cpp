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
class Base {
   public:
    virtual void someMethod(double d);

   protected:
    int m_protectedInt{0};

   private:
    int m_privateInt{0};
};

void Base::someMethod(double d){
    std::cout<<"This is Base's version of someMethod()."<<std::endl;
}

class Derived : public Base {
   public:
    void someMethod(double d) override;
    virtual void someOtherMethod();
};

void Derived::someMethod(double d){
    std::cout<<"This is Derived's version of someMethod()."<<std::endl;
}

void Derived::someOtherMethod(){
    std::cout<<"This is Derived's version of someOtherMethod()."<<std::endl;
}

int main() {
    clock_t startTime{clock()};
    Derived myDerived;
    Base& ref{myDerived};
    ref.someMethod(1.1);
    clock_t endTime{clock()};
    std::cout << endTime - startTime << std::endl;
    return 0;
}
