#pragma once

#include "my_utils.h"

#include <algorithm>
#include <condition_variable>
#include <deque>
#include <future>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <shared_mutex>
#include <stack>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <variant>
#include <vector>
#include <print>
#include <regex>

std::random_device rd{};
std::mt19937_64 gen{rd()};

#include <fast_io.h>
#include <fast_io_device.h>
#include <fast_io_driver/qt.h>
#include <fast_io_driver/timer.h>
#include <fast_io_hosted.h>
#include <fast_io_i18n.h>
#include <fast_io_legacy.h>

#include <fmt/chrono.h>
#include <fmt/compile.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fmt/printf.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <fmt/xchar.h>

#include <json/json.h>

#include <range/v3/all.hpp>

#include <glm/glm.hpp>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <opencv2/opencv.hpp>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#undef foreach
#undef emit
#undef slots
#include <QByteArray>
#include <QDebug>
#include <QString>

QTextStream qin(stdin);
QTextStream qout(stdout);

#define TBB_PREVIEW_CONCURRENT_LRU_CACHE 1
#define TBB_PREVIEW_BLOCKED_RANGE_ND 1
#include <tbb/blocked_range2d.h>
#include <tbb/blocked_range3d.h>
#include <tbb/blocked_rangeNd.h>
#include <tbb/cache_aligned_allocator.h>
#include <tbb/concurrent_hash_map.h>
#include <tbb/concurrent_lru_cache.h>
#include <tbb/concurrent_map.h>
#include <tbb/concurrent_priority_queue.h>
#include <tbb/concurrent_queue.h>
#include <tbb/concurrent_set.h>
#include <tbb/concurrent_unordered_map.h>
#include <tbb/concurrent_unordered_set.h>
#include <tbb/concurrent_vector.h>
#include <tbb/parallel_for.h>
#include <tbb/parallel_invoke.h>
#include <tbb/parallel_pipeline.h>
#include <tbb/parallel_reduce.h>
#include <tbb/parallel_scan.h>
#include <tbb/parallel_sort.h>
#include <tbb/partitioner.h>
#include <tbb/task_arena.h>
#include <tbb/task_group.h>
#include <tbb/tick_count.h>
#define TICK(x) auto bench_##x = tbb::tick_count::now();
#define TOCK(x) \
    std::cout << #x ": " << (tbb::tick_count::now() - bench_##x).seconds() << "s" << std::endl;

#include <benchmark/benchmark.h>
#include <benchmark/export.h>

#include <openvdb/openvdb.h>

#include <NumCpp.hpp>

#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#include <libavfilter/avfilter.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libdwarf/dwarf.h>
#include <libpng16/png.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>

#include "backward.hpp"
namespace backward {
backward::SignalHandling sh;
}