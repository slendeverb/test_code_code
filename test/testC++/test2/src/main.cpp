#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int minSwaps(string s) {
        stack<char> st;
        int swaps = 0;

        for (char c : s) {
            if (c == '[') {
                st.push(c);
            } else {
                if (!st.empty() && st.top() == '[') {
                    st.pop();
                } else {
                    swaps++;
                }
            }
        }

        return (swaps + 1) / 2;
    }
};

int main() {}