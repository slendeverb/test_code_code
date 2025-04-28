#include "header.h"
using namespace std;

// 读取CSV
vector<vector<string>> readCSV(string filename) {
    vector<vector<string>> data;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        vector<string> row;
        stringstream ss(line);
        string field;
        while (getline(ss, field, ',')) {
            row.push_back(field);
        }
        data.push_back(row);
    }
    return data;
}

// 统计CSV中某一列的hashmap，columnName映射到index
unordered_map<string,int> countColumn(vector<vector<string>> data,int columnIndex){
    unordered_map<string,int> cnt;
    for(auto row:data){
        cnt[row[columnIndex]]++;
    }
    return cnt;
}

signed main() {
    std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
    vector<vector<string>> data = readCSV(
        "D:/Tencent Files/QQ Files/Tencent Files/571641990/FileRecv/"
        "气象信息系统工程/实验/实验1/实验1 2006年至2016年塞格德的气象数据/weatherHistory.csv");
    // 统计Formatted Date列的hashmap，如果value大于1，则输出
    unordered_map<string,int> cnt = countColumn(data,0);
    for(auto [key,value]:cnt){
        if(value>1){
            cout << key << " " << value << endl;
        }
    }
    // 根据Formatted Date列的hashmap，将data中重复的行删除，不要inplace
    vector<vector<string>> data2;
    for(auto row:data){
        if(cnt[row[0]]==1){
            data2.push_back(row);
        }
    }
    data = data2;
    // 根据Formatted Date列排序，不要把表头也排序
    sort(data.begin()+1,data.end(),[&](vector<string> a,vector<string> b){
        return a[0] < b[0];
    });
    // 输出data
    for(auto row:data){
        for(auto field:row){
            cout << field << " ";
        }
        cout << endl;
    }
    return 0;
}