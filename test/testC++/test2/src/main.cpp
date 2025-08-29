#include "header.h"
using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<string>& board) {
        int n=board.size();
        std::vector<std::unordered_set<int>> row(n),col(n);
        std::vector<std::vector<std::unordered_set<int>>> square(n/3,std::vector<std::unordered_set<int>>(n/3));
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                char x=board[i][j];
                if(x=='.'){
                    continue;
                }
                
                if(row[i].contains(x)){
                    return false;
                }
                row[i].insert(x);
                
                if(col[j].contains(x)){
                    return false;
                }
                col[j].insert(x);

                if(square[i/3][j/3].contains(x)){
                    return false;
                }
                square[i/3][j/3].insert(x);
            }
        }
        return true;
    }
};

int main() {
    std::vector<std::string> board{"53..7....",
                                    "6..195...",
                                    ".98....6.",
                                    "8...6...3",
                                    "4..8.3..1",
                                    "7...2...6",
                                    ".6....28.",
                                    "...419..5",
                                    "....8..79"};
    auto result=Solution{}.isValidSudoku(board);
    std::print("{}\n",result);
}