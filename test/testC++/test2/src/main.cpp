#include <header.h>

class Singleton1 {
   public:
    static Singleton1* get_instance() {
        if (_instance == nullptr) {
            _instance = new Singleton1();
        }
        return _instance;
    }

   private:
    Singleton1() {}
    ~Singleton1() { std::cout << "~Singleton1()\n"; }
    Singleton1(const Singleton1&) = delete;
    Singleton1& operator=(const Singleton1&) = delete;
    Singleton1(Singleton1&&) = delete;
    Singleton1& operator=(Singleton1&&) = delete;

    static Singleton1* _instance;
};
Singleton1* Singleton1::_instance = nullptr;

class Singleton2 {
   public:
    static Singleton2* get_instance() {
        if (_instance == nullptr) {
            _instance = new Singleton2();
            atexit(Destructor);
        }
        return _instance;
    }

   private:
    static void Destructor() {
        if (nullptr != _instance) {
            delete _instance;
            _instance = nullptr;
        }
    }
    Singleton2() {}
    ~Singleton2() { std::cout << "~Singleton2()\n"; }
    Singleton2(const Singleton2&) = delete;
    Singleton2& operator=(const Singleton2&) = delete;
    Singleton2(Singleton2&&) = delete;
    Singleton2& operator=(Singleton2&&) = delete;

    static Singleton2* _instance;
};
Singleton2* Singleton2::_instance = nullptr;

class Singleton3 {
   public:
    static Singleton3* get_instance() {
        if (_instance == nullptr) {
            std::lock_guard<std::mutex> lock(_mutex);
            if (_instance == nullptr) {
                _instance = new Singleton3();
                atexit(Destructor);
            }
        }
        return _instance;
    }

   private:
    static void Destructor() {
        if (nullptr != _instance) {
            delete _instance;
            _instance = nullptr;
        }
    }
    Singleton3() {}
    ~Singleton3() { std::cout << "~Singleton3()\n"; }
    Singleton3(const Singleton3&) = delete;
    Singleton3& operator=(const Singleton3&) = delete;
    Singleton3(Singleton3&&) = delete;
    Singleton3& operator=(Singleton3&&) = delete;

    static Singleton3* _instance;
    static std::mutex _mutex;
};
Singleton3* Singleton3::_instance = nullptr;
std::mutex Singleton3::_mutex;

class Singleton4 {
   public:
    static Singleton4* get_instance() {
        Singleton4* temp = _instance.load(std::memory_order_relaxed);
        std::atomic_thread_fence(std::memory_order_acquire);
        if (temp == nullptr) {
            std::lock_guard<std::mutex> lock(_mutex);
            temp = _instance.load(std::memory_order_relaxed);
            if (temp == nullptr) {
                temp = new Singleton4();
                std::atomic_thread_fence(std::memory_order_release);
                _instance.store(temp, std::memory_order_relaxed);
                atexit(Destructor);
            }
        }
        return temp;
    }

   private:
    static void Destructor() {
        Singleton4* temp = _instance.load(std::memory_order_relaxed);
        if (nullptr != temp) {
            delete temp;
        }
    }
    Singleton4() {}
    ~Singleton4() { std::cout << "~Singleton4()\n"; }
    Singleton4(const Singleton4&) = delete;
    Singleton4& operator=(const Singleton4&) = delete;
    Singleton4(Singleton4&&) = delete;
    Singleton4& operator=(Singleton4&&) = delete;

    static std::atomic<Singleton4*> _instance;
    static std::mutex _mutex;
};
std::atomic<Singleton4*> Singleton4::_instance = nullptr;
std::mutex Singleton4::_mutex;

class Singleton5 {
   public:
    static Singleton5* get_instance() {
        static Singleton5 instance;
        return &instance;
    }

   private:
    Singleton5() {}
    ~Singleton5() { std::cout << "~Singleton5()\n"; }
    Singleton5(const Singleton5&) = delete;
    Singleton5& operator=(const Singleton5&) = delete;
    Singleton5(Singleton5&&) = delete;
    Singleton5& operator=(Singleton5&&) = delete;
};

template <typename T>
class Singleton {
   public:
    static T* get_instance() {
        static T instance;
        return &instance;
    }

   protected:
    virtual ~Singleton() { std::cout << "~Singleton()\n"; }
    Singleton() {}

   private:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
};

class DesignPattern : public Singleton<DesignPattern> {
    friend class Singleton<DesignPattern>;

   private:
    DesignPattern() {}
    ~DesignPattern() { std::cout << "DesignPattern()\n"; }
};

int main(int argc, char** argv) {
    auto s2 = Singleton2::get_instance();
    auto s3 = Singleton3::get_instance();
    auto s4 = Singleton4::get_instance();
    auto s5 = Singleton5::get_instance();
    auto s6 = DesignPattern::get_instance();
}