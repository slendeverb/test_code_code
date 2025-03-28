#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <valarray>
#include <variant>
#include <thread>
#include <algorithm>
#include <numeric>
#include <future>
#include <shared_mutex>
#include <condition_variable>

#include <fast_io.h>
#include <fast_io_legacy.h>
#include <fast_io_device.h>
#include <fast_io_i18n.h>
#include <fast_io_driver/timer.h>
#include <fast_io_driver/qt.h>

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/chrono.h>
#include <fmt/compile.h>
#include <fmt/ostream.h>
#include <fmt/printf.h>
#include <fmt/xchar.h>

#include <range/v3/all.hpp>

#include <glm/glm.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <opencv2/opencv.hpp>

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <QDebug>
#include <QString>
#include <QByteArray>

QTextStream qin(stdin);
QTextStream qout(stdout);

#undef emit
#include <tbb/task_group.h>
#include <tbb/parallel_invoke.h>
#include <tbb/parallel_for.h>

#include "backward.hpp"
namespace backward{
    backward::SignalHandling sh;
}

#if defined(__GNUC__) || defined(__clang__)
#include <cxxabi.h>
#endif

template <typename T>
std::string cpp_type_name() {
    const char* name=typeid(T).name();
#if defined(__GNUC__) || defined(__clang__)
    int status;
    char* p=abi::__cxa_demangle(name,0,0,&status);
    std::string s=p;
    std::free(p);
#else
    std::string s=name;
#endif
    if (std::is_const_v<std::remove_reference_t<T>>) {
        s+=" const";
    }
    if (std::is_volatile_v<std::remove_reference_t<T>>) {
        s+=" volatile";
    }
    if (std::is_lvalue_reference_v<T>) {
        s+=" &";
    }
    if (std::is_rvalue_reference_v<T>) {
        s+=" &&";
    }
    return s;
}

#define SHOW(x) std::cout<<cpp_type_name<x>()<<"\n"