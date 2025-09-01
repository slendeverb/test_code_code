#include "header.h"
using namespace std;

class Solution {
public:
    std::bitset<9> getPossibleStatus(int x,int y){
        return ~(rows[x] | cols[y] | cells[x/3][y/3]);
    }

    std::vector<int> getNext(std::vector<std::vector<char>>& board){
        std::vector<int> ret;
        int min_cnt=10;
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[i].size();j++){
                if(board[i][j]!='.'){
                    continue;
                }
                auto cur=getPossibleStatus(i,j);
                if(cur.count()>=min_cnt){
                    continue;
                }
                ret={i,j};
                min_cnt=cur.count();
            }
        }
        return ret;
    }

    void fillNum(int x,int y,int n,bool filled){
        rows[x][n]=(filled)?1:0;
        cols[y][n]=(filled)?1:0;
        cells[x/3][y/3][n]=(filled)?1:0;
    }

    bool dfs(std::vector<std::vector<char>>& board,int cnt){
        if(cnt==0){
            return true;
        }

        auto next=getNext(board);
        auto bits=getPossibleStatus(next[0],next[1]);
        for(int n=0;n<bits.size();n++){
            if(!bits.test(n)){
                continue;
            }
            fillNum(next[0],next[1],n,true);
            board[next[0]][next[1]]=n+'1';
            if(dfs(board,cnt-1)){
                return true;
            }
            board[next[0]][next[1]]='.';
            fillNum(next[0],next[1],n,false);
        }
        return false;
    }

    void solveSudoku(vector<vector<char>>& board) {
        rows=std::vector<std::bitset<9>>(9,std::bitset<9>());
        cols=std::vector<std::bitset<9>>(9,std::bitset<9>());
        cells=std::vector<std::vector<std::bitset<9>>>(3,std::vector<std::bitset<9>>(3,std::bitset<9>()));

        int cnt=0;
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[i].size();j++){
                if(board[i][j]=='.'){
                    cnt+=1;
                    continue;
                }
                int n=board[i][j]-'1';
                rows[i]|=(1<<n);
                cols[j]|=(1<<n);
                cells[i/3][j/3]|=(1<<n);
            }
        }
        dfs(board,cnt);
    }

private:
    std::vector<std::bitset<9>> rows;
    std::vector<std::bitset<9>> cols;
    std::vector<std::vector<std::bitset<9>>> cells;
};

int main() {
    std::vector<std::string> board_string_version{
        "53..7....",
        "6..195...",
        ".98....6.",
        "8...6...3",
        "4..8.3..1",
        "7...2...6",
        ".6....28.",
        "...419..5",
        "....8..79"};
    std::vector<std::vector<char>> board(board_string_version.size(),std::vector<char>(board_string_version[0].size()));
    for(int i=0;i<board_string_version.size();i++){
        for(int j=0;j<board_string_version[i].size();j++){
            board[i][j]=board_string_version[i][j];
        }
    }
    Solution{}.solveSudoku(board);
    for(int i=0;i<board.size();i++){
        std::print("{}\n",board[i]);
    }
}