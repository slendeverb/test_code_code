#include <bits/stdc++.h>
using namespace std;

class OrderedStream {
   private:
    int n;
    vector<string> stream;
    int ptr;

   public:
    OrderedStream(int n) : n(n), stream(n + 1, ""), ptr(1) {}
    vector<string> insert(int idKey, string value) {
        stream[idKey] = value;
        vector<string> result;

        if (ptr == idKey && !stream[idKey].empty()) {
            for (int i = ptr; i <= n; ++i) {
                if (!stream[i].empty()) {
                    result.push_back(stream[i]);
                    ptr = i + 1;
                } else {
                    break;
                }
            }
        }

        return result;
    }
};

/**
 * Your OrderedStream object will be instantiated and called as such:
 * OrderedStream* obj = new OrderedStream(n);
 * vector<string> param_1 = obj->insert(idKey,value);
 */

void print(const auto& v) {
    for (const auto& x : v) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}

int main() {
    OrderedStream os(5);
    vector<string> result;
    result = os.insert(3, "ccccc");  // 插入 (3, "ccccc")，返回 []
    print(result);
    result = os.insert(1, "aaaaa");  // 插入 (1, "aaaaa")，返回 ["aaaaa"]
    print(result);
    result = os.insert(2, "bbbbb");  // 插入 (2, "bbbbb")，返回 ["bbbbb", "ccccc"]
    print(result);
    result = os.insert(5, "eeeee");  // 插入 (5, "eeeee")，返回 []
    print(result);
    result = os.insert(4, "ddddd");  // 插入 (4, "ddddd")，返回 ["ddddd", "eeeee"]
    print(result);
}
