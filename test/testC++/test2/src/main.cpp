#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void solve()
{
    std::string output_path { "../../../out.txt" };
    std::ofstream out { output_path };
    std::filesystem::path folder_path { "C:/Users/slendeverb/Documents/code_code" };
    if (!std::filesystem::exists(folder_path)) {
        out << "folder path doesn't exist" << std::endl;
    }
    std::filesystem::directory_entry entry { folder_path };
    if (entry.status().type() == std::filesystem::file_type::directory) {
        out << "This root is a directory\n";
    }
    std::filesystem::recursive_directory_iterator list { folder_path };
    for (auto& it : list) {
        if (!it.is_directory()) {
            out << it.path() << "\n";
        }
    }
    out.close();
}

int main()
{
    solve();
    return 0;
}