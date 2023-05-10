#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
using namespace std;

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int egyptian_fraction_count(int numerator, int denominator)
{
    int count = 0;
    vector<pair<int, int>> fractions;

    while (numerator != 0)
    {
        int ceil_val = ceil((float)denominator / numerator);
        fractions.push_back(make_pair(1, ceil_val));

        int new_numerator = numerator * ceil_val - denominator;
        int new_denominator = denominator * ceil_val;

        int g = gcd(new_numerator, new_denominator);
        numerator = new_numerator / g;
        denominator = new_denominator / g;

        count++;
    }

    return count;
}

int main()
{
    int numerator, denominator;
    while (cin >> numerator >> denominator)
    {
        int count = egyptian_fraction_count(numerator, denominator);
        cout << "The given fraction can be represented as a sum of at least " << count << " Egyptian fractions." << endl;
    }
    return 0;
}
