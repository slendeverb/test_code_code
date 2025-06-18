#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

int get_terminal_width() {
    #ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    #else
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_col;
    #endif
}

void adaptive_progress_bar(int current, int total) {
    int width = get_terminal_width()-30; // 预留信息空间
    float progress = static_cast<float>(current) / total;
    int pos = static_cast<int>(width * progress);

    std::string bar;
    bar.reserve(width + 10);
    bar += "[";
    for (int i = 0; i < width; ++i) {
        if (i < pos) bar += "=";
        else if (i == pos) bar += ">";
        else bar += " ";
    }
    bar += "] ";

    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%3d%% %d/%d", 
             static_cast<int>(progress * 100), current, total);
    bar += buffer;

    std::cout << "\r" << bar << std::flush;
}

int main() {
    const int total = 100;
    for (int i = 0; i <= total; ++i) {
        adaptive_progress_bar(i, total);
        double progress_persent=(double)i/total;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "\n任务完成! " << std::endl;
    return 0;
}