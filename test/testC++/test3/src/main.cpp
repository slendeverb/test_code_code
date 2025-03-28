#include "header.h"
using namespace std;

class ThreadPool {
    std::vector<std::thread> m_pool;

public:
    void push_back(std::thread t) {
        m_pool.push_back(std::move(t));
    }

    ~ThreadPool() {
        for (auto &t: m_pool) {
            if (t.joinable()) t.join();
        }
    }
};

ThreadPool tpool;

class MTVector {
    std::vector<int> m_arr;
    mutable std::shared_mutex m_mutex;

public:
    class Accessor {
        MTVector &m_vec;
        std::unique_lock<std::shared_mutex> m_lock;

    public:
        Accessor(MTVector &vec) : m_vec{vec}, m_lock{vec.m_mutex} {}

        void push_back(int val) {
            m_vec.m_arr.push_back(val);
        }
    };

    class ConstAccessor {
        const MTVector &m_vec;
        std::shared_lock<std::shared_mutex> m_lock;

    public:
        ConstAccessor(const MTVector &vec): m_vec{vec}, m_lock{vec.m_mutex} {}

        size_t size() const {
            return m_vec.m_arr.size();
        }

        [[nodiscard]] const std::vector<int> &get_vec() const {
            return m_vec.m_arr;
        }
    };

    Accessor access() {
        return {*this};
    }

    ConstAccessor const_access() const {
        return {*this};
    }
};

template <typename T>
class MTStack {
    std::condition_variable m_cv;
    std::mutex m_mtx;
    std::vector<T> m_arr;

public:
    T pop() {
        std::unique_lock lck{m_mtx};
        m_cv.wait(lck, [this]{return !m_arr.empty();});
        T ret=std::move(m_arr.back());
        m_arr.pop_back();
        return ret;
    }

    auto pop_hold() {
        std::unique_lock lck{m_mtx};
        m_cv.wait(lck, [this]{return !m_arr.empty();});
        T ret=std::move(m_arr.back());
        m_arr.pop_back();
        return std::pair{std::move(ret),std::move(lck)};
    }

    void push(T val) {
        std::unique_lock lck{m_mtx};
        m_arr.push_back(std::move(val));
        m_cv.notify_one();
    }

    void push_many(std::initializer_list<T> list) {
        std::unique_lock lck{m_mtx};
        std::copy(std::move_iterator(list.begin()),
            std::move_iterator(list.end()),
            std::back_inserter(m_arr));
        m_cv.notify_all();
    }
};

void download(std::string_view file) {
    for (int i=0;i<10;i++) {
        fmt::print("Downloading {} ({}%)...\n", file,i*10);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    fmt::print("Download complete: {}\n",file);
}

void interact() {
    fmt::print("{}: ","请输入你的名字");
    std::string name;
    std::cin>>name;
    fmt::print("Hi, {}\n",name);
}

int main() {
    size_t n=1<<18;
    std::vector<float> arr(n);
    std::iota(arr.begin(), arr.end(), 0);

    tbb::parallel_for(tbb::blocked_range<size_t>(0,n),
        [&](tbb::blocked_range<size_t> r) {
            for (size_t i=r.begin();i!=r.end();i++) {
                arr[i]=std::sin(arr[i]);
            }
        });
    auto t1=std::chrono::steady_clock::now();
    fmt::print("{}\n",arr);
    auto t2=std::chrono::steady_clock::now();
    fast_io::io::print("[");
    for (size_t i=0;i<n;i++) {
        fast_io::io::print(arr[i]);
        if (i!=n-1) {
            fast_io::io::print(", ");
        }
    }
    fast_io::io::print("]\n");
    auto t3=std::chrono::steady_clock::now();
    std::cout<<"[";
    for (size_t i=0;i<n;i++) {
        std::cout<<std::format("{}",arr[i]);
        if (i!=n-1) {
            std::cout<<", ";
        }
    }
    std::cout<<"]\n";
    auto t4=std::chrono::steady_clock::now();
    fmt::print("fmt: {}\nfast_io: {}\nstd::format: {}\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1),
        std::chrono::duration_cast<std::chrono::milliseconds>(t3-t2),
        std::chrono::duration_cast<std::chrono::milliseconds>(t4-t3));
}
