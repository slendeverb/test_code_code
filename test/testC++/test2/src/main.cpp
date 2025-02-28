#include <bits/stdc++.h>
using namespace std;

class FoodRatings {
public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        int n = foods.size();
        for (int i = 0; i < n; ++i) {
            foodRating[foods[i]] = ratings[i];
            cuisineMap[cuisines[i]].insert({-ratings[i], foods[i]});
        }
    }
    
    void changeRating(string food, int newRating) {
        // 更新食物的评分
        auto& oldRating = foodRating[food];
        auto& cuisineSet = cuisineMap[cuisineOfFood[food]];
        
        // 从旧的评分集合中移除旧的食物
        cuisineSet.erase({-oldRating, food});
        
        // 更新食物的新评分并插入到新的评分集合中
        oldRating = newRating;
        cuisineSet.insert({-newRating, food});
    }
    
    string highestRated(string cuisine) {
        auto& cuisineSet = cuisineMap[cuisine];
        return cuisineSet.begin()->second; // 返回评分最高的食物（字典序最小）
    }
private:
    map<string, int> foodRating; // 存储食物及其当前评分
    map<string, set<pair<int, string>>> cuisineMap; // 存储每个烹饪方式下的所有食物及其评分
    map<string, string> cuisineOfFood; // 存储每个食物对应的烹饪方式
};

/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */

int main() {
    
}