#include "header.h"

int main() {
    constexpr int nx = 1 << 12;
    constexpr int ny = 1 << 12;
    ndarray<2, int> a(nx, ny);
    ndarray<2, int> b(ny, nx);
    ndarray<2, int> c(ny, nx);
    int m = 0;
    for (int i = 0; i < a.shape(0); i++) {
        for (int j = 0; j < a.shape(1); j++) {
            a(i, j) = m++;
        }
    }
    TICK(morton);
    constexpr int block_size = 64;
#pragma omp parallel for
    for (int morton_code = 0; morton_code < (ny / block_size) * (nx / block_size); morton_code++) {
        auto [y_base, x_base] = morton2d::decode(morton_code);
        x_base *= block_size;
        y_base *= block_size;
        for (int y = y_base; y < y_base + block_size; y++) {
            for (int x = x_base; x < x_base + block_size; x++) {
                b(x, y) = a(y, x);
            }
        }
    }
    TOCK(morton);

    TICK(tbb_simple_partitioner);
    tbb::parallel_for(
        tbb::blocked_range2d<size_t>(0, nx, block_size, 0, ny, block_size),
        [&](const tbb::blocked_range2d<size_t>& r) {
            for (size_t y = r.cols().begin(); y < r.cols().end(); y++) {
                for (size_t x = r.rows().begin(); x < r.rows().end(); x++) {
                    c(x, y) = a(y, x);
                }
            }
        },
        tbb::simple_partitioner{});
    TOCK(tbb_simple_partitioner);
}