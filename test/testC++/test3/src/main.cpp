#include "header.h"
using namespace std;

class Solution {
public:
    vector<vector<int>> differenceOfDistinctValues(vector<vector<int>>& grid) {
        int m=grid.size();
        int n=grid[0].size();
        std::vector ans(m,std::vector<int>(n,0));
        std::unordered_set<int> st;

        for(int k=1;k<m+n;k++){
            int min_j=std::max(n-k,0);
            int max_j=std::min(m+n-1-k,n-1);

            st.clear();
            for(int j=min_j;j<=max_j;j++){
                int i=k+j-n;
                ans[i][j]=st.size();
                st.insert(grid[i][j]);
            }

            st.clear();
            for(int j=max_j;j>=min_j;j--){
                int i=k+j-n;
                ans[i][j]=abs(ans[i][j]-static_cast<int>(st.size()));
                st.insert(grid[i][j]);
            }
        }
        return ans;
    }
};

class ThreadPool {
    std::vector<std::thread> m_pool;
public:
    void push_back(std::thread t) {
        m_pool.push_back(std::move(t));
    }

    ~ThreadPool() {
        for (auto& t : m_pool) {
            if (t.joinable()) t.join();
        }
    }
};

ThreadPool tpool;

void download(std::string_view download_file) {
    for (int i=0;i<10;i++) {
        fmt::print("Downloading {} ({}%)...\n",download_file,i*10);
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
    fmt::print("Download complete {}\n",download_file);
}

void myFunc() {
    std::thread t1{[&]() {
        download("hello.zip");
    }};
    tpool.push_back(std::move(t1));
}

void interact() {
    QString output="为进行Qt终端测试，请输入你的名字: ";
    qout<<output;
    qout.flush();
    QString name=qin.readLine();
    output="你好, ";
    qout<<output<<name<<"\n";
    qout.flush();
}

int main() {
    // myFunc();
    interact();
    std::vector vec{1,2,3,4,5};
    fmt::print("{}\n",vec);

    std::future<void> fu=std::async([&]() {
        download("hello.zip");
    });
}
