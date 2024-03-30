#include <cstdarg>
#include <iomanip>
#include <concepts>
#include <cstdio>
#include <ctime>
#include <bit>
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
using namespace std;

void solve()
{
    // Boolean values
    bool myBool{true};
    cout << "This is the default: " << myBool << endl;
    cout << "This should be true: " << boolalpha << myBool << endl;
    cout << "This should be 1: " << noboolalpha << myBool << endl;
    // Simulate printf-style "%6d" with streams
    int i{123};
    printf("This should be ' 123': %6d\n", i);
    cout << "This should be ' 123': " << setw(6) << i << endl;
    // Simulate printf-style "%06d" with streams
    printf("This should be '000123': %06d\n", i);
    cout << "This should be '000123': " << setfill('0') << setw(6) << i << endl;
    // Fill with *
    cout << "This should be '***123': " << setfill('*') << setw(6) << i << endl;
    // Reset fill character
    cout << setfill(' ');
    // Floating-point values
    double dbl{1.452};
    double dbl2{5};
    cout << "This should be ' 5': " << setw(2) << noshowpoint << dbl2 << endl;
    cout << "This should be @@1.452: " << setw(7) << setfill('@') << dbl << endl;
    // Reset fill character
    cout << setfill(' ');
    // Instructs cout to start formatting numbers according to your location.
    // Chapter 21 explains the details of the imbue() call and the locale object.

    cout.imbue(locale{""});

    // Format numbers according to your location
    cout << "This is 1234567 formatted according to your location: " << 1234567
         << endl;
    // Monetary value. What exactly a monetary value means depends on your
    // location. For example, in the USA, a monetary value of 120000 means 120000
    // dollar cents, which is 1200.00 dollars.
    cout << "This should be a monetary value of 120000, "
         << "formatted according to your location: "
         << put_money("120000") << endl;
    // Date and time
    time_t t_t{time(nullptr)}; // Get current system time.
    tm *t{localtime(&t_t)};    // Convert to local time.
    cout << "This should be the current date and time "
         << "formatted according to your location: "
         << put_time(t, "%c") << endl;
    // Quoted string
    cout << "This should be: \"Quoted string with \\\"embedded quotes\\\".\": "
         << quoted("Quoted string with \"embedded quotes\".") << endl;
}

int main()
{
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
    clock_t startTime{clock()};
    solve();
    clock_t endTime{clock()};
    std::cout << "time cost: " << endTime - startTime << std::endl;
    return 0;
}
