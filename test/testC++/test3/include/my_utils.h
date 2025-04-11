#pragma once

/**
 * cpp_type_name
 * ThreadPool
 * MTVector MTStack
 * Pod
 * quick_sort quick_reduce
 * AlignedAllocator
 * ndarray
 * morton2d morton3d
 */

#include <algorithm>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <numeric>
#include <shared_mutex>
#include <stack>
#include <thread>
#include <vector>

#include <fmt/format.h>

#include <tbb/parallel_invoke.h>

#if defined(__GNUC__) || defined(__clang__)
#include <cxxabi.h>
#endif

template <typename T>
std::string cpp_type_name() {
    const char* name = typeid(T).name();
#if defined(__GNUC__) || defined(__clang__)
    int status;
    char* p = abi::__cxa_demangle(name, 0, 0, &status);
    std::string s = p;
    std::free(p);
#else
    std::string s = name;
#endif
    if (std::is_const_v<std::remove_reference_t<T>>) {
        s += " const";
    }
    if (std::is_volatile_v<std::remove_reference_t<T>>) {
        s += " volatile";
    }
    if (std::is_lvalue_reference_v<T>) {
        s += " &";
    }
    if (std::is_rvalue_reference_v<T>) {
        s += " &&";
    }
    return s;
}
#define SHOW(x) std::cout << cpp_type_name<x>() << "\n";

class ThreadPool {
    std::vector<std::thread> m_pool;

   public:
    void push_back(std::thread t) { m_pool.push_back(std::move(t)); }

    ~ThreadPool() {
        for (auto& t : m_pool) {
            if (t.joinable())
                t.join();
        }
    }
};

inline ThreadPool tpool;

class MTVector {
    std::vector<int> m_arr;
    mutable std::shared_mutex m_mutex;

   public:
    class Accessor {
        MTVector& m_vec;
        std::unique_lock<std::shared_mutex> m_lock;

       public:
        Accessor(MTVector& vec) : m_vec{vec}, m_lock{vec.m_mutex} {}

        void push_back(int val) { m_vec.m_arr.push_back(val); }
    };

    class ConstAccessor {
        const MTVector& m_vec;
        std::shared_lock<std::shared_mutex> m_lock;

       public:
        ConstAccessor(const MTVector& vec) : m_vec{vec}, m_lock{vec.m_mutex} {}

        size_t size() const { return m_vec.m_arr.size(); }

        [[nodiscard]] const std::vector<int>& get_vec() const { return m_vec.m_arr; }
    };

    Accessor access() { return {*this}; }

    ConstAccessor const_access() const { return {*this}; }
};

template <typename T>
class MTStack {
    std::condition_variable m_cv;
    std::mutex m_mtx;
    std::vector<T> m_arr;

   public:
    T pop() {
        std::unique_lock lck{m_mtx};
        m_cv.wait(lck, [this] { return !m_arr.empty(); });
        T ret = std::move(m_arr.back());
        m_arr.pop_back();
        return ret;
    }

    auto pop_hold() {
        std::unique_lock lck{m_mtx};
        m_cv.wait(lck, [this] { return !m_arr.empty(); });
        T ret = std::move(m_arr.back());
        m_arr.pop_back();
        return std::pair{std::move(ret), std::move(lck)};
    }

    void push(T val) {
        std::unique_lock lck{m_mtx};
        m_arr.push_back(std::move(val));
        m_cv.notify_one();
    }

    void push_many(std::initializer_list<T> list) {
        std::unique_lock lck{m_mtx};
        std::copy(std::move_iterator(list.begin()), std::move_iterator(list.end()),
                  std::back_inserter(m_arr));
        m_cv.notify_all();
    }
};

template <typename T>
struct Pod {
   private:
    T m_t;

   public:
    Pod() {}

    Pod(Pod&& p) noexcept : m_t(std::move(p.m_t)) {}

    Pod(const Pod& p) : m_t(p.m_t) {}

    Pod& operator=(Pod&& p) noexcept {
        m_t = std::move(p.m_t);
        return *this;
    }

    Pod& operator=(const Pod& p) {
        m_t = p.m_t;
        return *this;
    }

    Pod(T&& t) : m_t(std::move(t)) {}

    Pod(const T& t) : m_t(t) {}

    Pod& operator=(T&& t) {
        m_t = std::move(t);
        return *this;
    }

    Pod& operator=(const T& t) {
        m_t = t;
        return *this;
    }

    const T* operator&() const { return &m_t; }

    T* operator&() { return &m_t; }

    const T& get() const { return m_t; }

    T& get() { return m_t; }

    template <typename... Ts>
    Pod& emplace(Ts&&... ts) {
        ::new (&m_t) T(std::forward<Ts>(ts)...);
        return *this;
    }

    void destroy() { m_t.~T(); }
};

template <typename T>
void quick_sort(T* data, size_t size) {
    if (size < 1) {
        return;
    }
    if (size < (1 << 16)) {
        std::sort(data, data + size, std::less<>{});
        return;
    }
    size_t mid = std::hash<size_t>{}(size);
    mid ^= std::hash<void*>{}(static_cast<void*>(data));
    mid %= size;
    std::swap(data[0], data[mid]);
    T pivot = data[0];
    size_t left = 0, right = size - 1;
    while (left < right) {
        while (left < right && !(data[right] < pivot)) {
            right--;
        }
        if (left < right) {
            data[left++] = data[right];
        }
        while (left < right && data[left] < pivot) {
            left++;
        }
        if (left < right) {
            data[right--] = data[left];
        }
    }
    data[left] = pivot;
    tbb::parallel_invoke([&]() { quick_sort(data, left); },
                         [&]() { quick_sort(data + left + 1, size - left - 1); });
}

template <typename T>
T quick_reduce(T* data, size_t size) {
    if (size < (1 << 16)) {
        return std::reduce(data, data + size);
    }
    T sum1, sum2;
    size_t mid = size / 2;
    tbb::parallel_invoke([&]() { sum1 = quick_reduce(data, mid); },
                         [&]() { sum2 = quick_reduce(data + mid, size - mid); });
    return sum1 + sum2;
}

enum class Alignment : size_t {
    Normal = sizeof(void*),
    SSE = 16,
    AVX = 32,
};

namespace detail {
inline void* allocate_aligned_memory(size_t align, size_t size) {
#if defined(__GNUC__) || defined(__clang__)
    return std::aligned_alloc(align, size);
#else
    return _aligned_malloc(size, align);
#endif
}
inline void deallocate_aligned_memory(void* ptr) noexcept {
#if defined(__GNUC__) || defined(__clang__)
    std::free(ptr);
#else
    _aligned_free(ptr);
#endif
}
}  // namespace detail

template <typename T, Alignment Align = Alignment::AVX>
class AlignedAllocator;

template <Alignment Align>
class AlignedAllocator<void, Align> {
   public:
    typedef void* pointer;
    typedef const void* const_pointer;
    typedef void value_type;

    template <class U>
    struct rebind {
        typedef AlignedAllocator<U, Align> other;
    };
};

template <typename T, Alignment Align>
class AlignedAllocator {
   public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    typedef std::true_type propagate_on_container_move_assignment;

    template <class U>
    struct rebind {
        typedef AlignedAllocator<U, Align> other;
    };

   public:
    AlignedAllocator() noexcept {}

    template <class U>
    AlignedAllocator(const AlignedAllocator<U, Align>&) noexcept {}

    size_type max_size() const noexcept { return (size_type(~0) - size_type(Align)) / sizeof(T); }

    pointer address(reference x) const noexcept { return std::addressof(x); }

    const_pointer address(const_reference x) const noexcept { return std::addressof(x); }

    pointer allocate(size_type n, typename AlignedAllocator<void, Align>::const_pointer = 0) {
        const size_type alignment = static_cast<size_type>(Align);
        void* ptr = detail::allocate_aligned_memory(alignment, n * sizeof(T));
        if (ptr == nullptr) {
            throw std::bad_alloc();
        }

        return reinterpret_cast<pointer>(ptr);
    }

    void deallocate(pointer p, size_type) noexcept { return detail::deallocate_aligned_memory(p); }

    template <class U, class... Args>
    void construct(U* p, Args&&... args) {
        ::new (reinterpret_cast<void*>(p)) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p) { p->~T(); }
};

template <typename T, Alignment Align>
class AlignedAllocator<const T, Align> {
   public:
    typedef T value_type;
    typedef const T* pointer;
    typedef const T* const_pointer;
    typedef const T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    typedef std::true_type propagate_on_container_move_assignment;

    template <class U>
    struct rebind {
        typedef AlignedAllocator<U, Align> other;
    };

   public:
    AlignedAllocator() noexcept {}

    template <class U>
    AlignedAllocator(const AlignedAllocator<U, Align>&) noexcept {}

    size_type max_size() const noexcept { return (size_type(~0) - size_type(Align)) / sizeof(T); }

    const_pointer address(const_reference x) const noexcept { return std::addressof(x); }

    pointer allocate(size_type n, typename AlignedAllocator<void, Align>::const_pointer = 0) {
        const size_type alignment = static_cast<size_type>(Align);
        void* ptr = detail::allocate_aligned_memory(alignment, n * sizeof(T));
        if (ptr == nullptr) {
            throw std::bad_alloc();
        }

        return reinterpret_cast<pointer>(ptr);
    }

    void deallocate(pointer p, size_type) noexcept { return detail::deallocate_aligned_memory(p); }

    template <class U, class... Args>
    void construct(U* p, Args&&... args) {
        ::new (reinterpret_cast<void*>(p)) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p) { p->~T(); }
};

template <typename T, Alignment TAlign, typename U, Alignment UAlign>
inline bool operator==(const AlignedAllocator<T, TAlign>&,
                       const AlignedAllocator<U, UAlign>&) noexcept {
    return TAlign == UAlign;
}

template <typename T, Alignment TAlign, typename U, Alignment UAlign>
inline bool operator!=(const AlignedAllocator<T, TAlign>&,
                       const AlignedAllocator<U, UAlign>&) noexcept {
    return TAlign != UAlign;
}

template <std::size_t N,
          typename T,
          std::size_t LoBound = 0,
          std::size_t HiBound = LoBound,
          typename AllocatorT = AlignedAllocator<T>>
class ndarray {
    static_assert(N > 0, "N cannot be 0");
    static_assert(std::is_same_v<std::remove_reference_t<std::remove_cv_t<T>>, T>,
                  "T cannot be cvref");

    using Dim = std::array<std::intptr_t, N>;
    using Shape = std::array<std::size_t, N>;

    std::vector<T, AllocatorT> m_arr;
    Shape m_shape{};

    constexpr static std::size_t _calc_size(Shape const& shape) noexcept {
        std::size_t size = shape[0] + (LoBound + HiBound);
        for (std::size_t i = 1; i < N; i++) {
            size *= shape[i] + (LoBound + HiBound);
        }
        return size;
    }

   public:
    ndarray() = default;
    ndarray(ndarray const&) = default;
    ndarray(ndarray&&) = default;
    ndarray& operator=(ndarray const&) = default;
    ndarray& operator=(ndarray&&) = default;
    ~ndarray() = default;

    explicit ndarray(Shape const& shape) : m_arr(_calc_size(shape)), m_shape(shape) {}

    explicit ndarray(Shape const& shape, T const& value)
        : m_arr(_calc_size(shape), value), m_shape(shape) {}

    template <class... Ts,
              std::enable_if_t<sizeof...(Ts) == N && (std::is_integral_v<Ts> && ...), int> = 0>
    explicit ndarray(Ts const&... ts) : ndarray(Shape{static_cast<size_t>(ts)...}) {}

    void reshape(Shape const& shape) {
        std::size_t size = _calc_size(shape);
        m_shape = shape;
        m_arr.clear();
        m_arr.resize(size);
    }

    void reshape(Shape const& shape, T const& value) {
        std::size_t size = _calc_size(shape);
        m_shape = shape;
        m_arr.clear();
        m_arr.resize(size, value);
    }

    void shrink_to_fit() { m_arr.shrink_to_fit(); }

    template <class... Ts,
              std::enable_if_t<sizeof...(Ts) == N && (std::is_integral_v<Ts> && ...), int> = 0>
    void reshape(Ts const&... ts) {
        this->reshape(Shape{static_cast<size_t>(ts)...});
    }

    constexpr Shape shape() const noexcept { return m_shape; }

    constexpr std::size_t shape(std::size_t i) const noexcept { return m_shape[i]; }

    constexpr std::size_t linearize(Dim const& dim) const noexcept {
        std::size_t offset{dim[0] + LoBound};
        std::size_t term = 1;
        for (std::size_t i = 1; i < N; i++) {
            term *= m_shape[i - 1] + (LoBound + HiBound);
            offset += term * std::size_t{dim[i] + LoBound};
        }
        return offset;
    }

    std::size_t safe_linearize(Dim const& dim) const {
        for (std::size_t i = 0; i < N; i++) {
            if (dim[i] < -std::intptr_t{LoBound} || dim[i] >= m_shape[i] + HiBound)
                throw std::out_of_range("ndarray::at");
        }
        return linearize(dim);
    }

    constexpr T* data() noexcept { return m_arr.data(); }

    constexpr T const* data() const noexcept { return m_arr.data(); }

    constexpr T& operator()(Dim const& dim) noexcept { return data()[linearize(dim)]; }

    constexpr T const& operator()(Dim const& dim) const noexcept { return data()[linearize(dim)]; }

    template <class... Ts,
              std::enable_if_t<sizeof...(Ts) == N && (std::is_integral_v<Ts> && ...), int> = 0>
    constexpr T& operator()(Ts const&... ts) noexcept {
        return operator()(Dim{static_cast<intptr_t>(ts)...});
    }

    template <class... Ts,
              std::enable_if_t<sizeof...(Ts) == N && (std::is_integral_v<Ts> && ...), int> = 0>
    constexpr T const& operator()(Ts const&... ts) const noexcept {
        return operator()(Dim{static_cast<intptr_t>(ts)...});
    }

    constexpr T& operator[](Dim const& dim) noexcept { return operator()(linearize(dim)); }

    constexpr T const& operator[](Dim const& dim) const noexcept {
        return operator()(linearize(dim));
    }

    T& at(Dim const& dim) { return data()[safe_linearize(dim)]; }

    T const& at(Dim const& dim) const { return data()[safe_linearize(dim)]; }

    template <class... Ts,
              std::enable_if_t<sizeof...(Ts) == N && (std::is_integral_v<Ts> && ...), int> = 0>
    T& at(Ts const&... ts) {
        return at(Dim{static_cast<intptr_t>(ts)...});
    }

    template <class... Ts,
              std::enable_if_t<sizeof...(Ts) == N && (std::is_integral_v<Ts> && ...), int> = 0>
    T const& at(Ts const&... ts) const {
        return at(Dim{static_cast<intptr_t>(ts)...});
    }

    std::string format() const {
        std::string result;
        const auto& shape = this->shape();
        const std::size_t total_size = _calc_size(shape);

        // 头部信息
        result += fmt::format("ndarray<{}, {}> shape=[", N, cpp_type_name<T>());
        for (std::size_t i = 0; i < N; ++i) {
            result += fmt::format("{}{}", shape[i], i < N - 1 ? ", " : "");
        }
        result += "]:\n";

        if constexpr (N == 1) {
            // 1D 数组
            result += "[";
            for (std::size_t i = 0; i < shape[0]; ++i) {
                result += fmt::format("{}{}", (*this)(i), i < shape[0] - 1 ? ", " : "");
            }
            result += "]";
        } else if constexpr (N == 2) {
            // 2D 数组
            result += "[";
            for (std::size_t i = 0; i < shape[0]; ++i) {
                result += "[";
                for (std::size_t j = 0; j < shape[1]; ++j) {
                    result += fmt::format("{}{}", (*this)(i, j), j < shape[1] - 1 ? ", " : "");
                }
                result += "]";
                result += (i < shape[0] - 1 ? ", " : "");
            }
            result += "]";
        } else if constexpr (N == 3) {
            // 3D 数组
            result += "[";
            for (std::size_t i = 0; i < shape[0]; ++i) {
                result += "[";
                for (std::size_t j = 0; j < shape[1]; ++j) {
                    result += "[";
                    for (std::size_t k = 0; k < shape[2]; ++k) {
                        result +=
                            fmt::format("{}{}", (*this)(i, j, k), k < shape[2] - 1 ? ", " : "");
                    }
                    result += "]";
                    result += (j < shape[1] - 1 ? ", " : "");
                }
                result += "]";
                result += (i < shape[0] - 1 ? ", " : "");
            }
            result += "]";
        } else {
            // 更高维度 - 简化显示
            result += "[";
            for (std::size_t i = 0; i < total_size; ++i) {
                result += fmt::format("{}{}", data()[i], i < total_size - 1 ? ", " : "");
            }
            result += "]";
        }

        return result;
    }
};

template <std::size_t N, typename T, std::size_t LoBound, std::size_t HiBound, typename AllocatorT>
struct fmt::formatter<ndarray<N, T, LoBound, HiBound, AllocatorT>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const ndarray<N, T, LoBound, HiBound, AllocatorT>& arr, FormatContext& ctx) {
        auto out = ctx.out();
        out = fmt::format_to(out, "{}", arr.format());
        return out;
    }
};

namespace morton2d {
constexpr static uint64_t encode1(uint64_t x) {
    x = (x | (x << 16)) & 0x0000FFFF0000FFFF;
    x = (x | (x << 8)) & 0x00FF00FF00FF00FF;
    x = (x | (x << 4)) & 0x0F0F0F0F0F0F0F0F;
    x = (x | (x << 2)) & 0x3333333333333333;
    x = (x | (x << 1)) & 0x5555555555555555;
    return x;
}

constexpr static uint64_t encode(uint64_t x, uint64_t y) {
    return encode1(x) | encode1(y << 1);
}

constexpr static uint64_t decode1(uint64_t x) {
    x = x & 0x5555555555555555;
    x = (x | (x >> 1)) & 0x3333333333333333;
    x = (x | (x >> 2)) & 0x0F0F0F0F0F0F0F0F;
    x = (x | (x >> 4)) & 0x00FF00FF00FF00FF;
    x = (x | (x >> 8)) & 0x0000FFFF0000FFFF;
    x = (x | (x >> 16)) & 0xFFFFFFFFFFFFFFFF;
    return x;
}

constexpr static std::tuple<uint64_t, uint64_t> decode(uint64_t d) {
    return {decode1(d), decode1(d >> 1)};
}

}  // namespace morton2d

namespace morton3d {

constexpr static uint64_t encode1(uint64_t x) {
    x = (x | (x << 32)) &
        0x7fff00000000ffff;  // 0b0111111111111111000000000000000000000000000000001111111111111111
    x = (x | (x << 16)) &
        0x00ff0000ff0000ff;  // 0b0000000011111111000000000000000011111111000000000000000011111111
    x = (x | (x << 8)) &
        0x700f00f00f00f00f;  // 0b0111000000001111000000001111000000001111000000001111000000001111
    x = (x | (x << 4)) &
        0x30c30c30c30c30c3;  // 0b0011000011000011000011000011000011000011000011000011000011000011
    x = (x | (x << 2)) &
        0x1249249249249249;  // 0b0001001001001001001001001001001001001001001001001001001001001001
    return x;
}

constexpr static uint64_t encode(uint64_t x, uint64_t y, uint64_t z) {
    return encode1(x) | encode1(y << 1) | encode1(z << 2);
}

constexpr static uint64_t decode1(uint64_t x) {
    x = x & 0x1249249249249249;
    x = (x | (x >> 2)) & 0x30c30c30c30c30c3;
    x = (x | (x >> 4)) & 0x700f00f00f00f00f;
    x = (x | (x >> 8)) & 0x00ff0000ff0000ff;
    x = (x | (x >> 16)) & 0x7fff00000000ffff;
    x = (x | (x >> 32)) & 0xffffffffffffffff;
    return x;
}

constexpr static std::tuple<uint64_t, uint64_t, uint64_t> decode(uint64_t d) {
    return {decode1(d), decode1(d >> 1), decode1(d >> 2)};
}

}  // namespace morton3d