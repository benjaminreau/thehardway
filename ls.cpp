#include <fmt/core.h>
#include <filesystem>
#include <unistd.h>

namespace fs = std::filesystem;

void print_content(std::string dir, int hidden_files, int hidden_files_global, int only_directories) {
    fs::path target{dir};

    if (hidden_files_global == 1) {
        fmt::print(".  ..  ");
    }
    for(auto& dir_entry : fs::directory_iterator{target}) {
        const std::string& path = dir_entry.path().filename().string();

        if (only_directories == 1 && !dir_entry.is_directory()) continue;
        if (path.starts_with(".") && hidden_files == 0 && hidden_files_global == 0) continue;
        fmt::print("{}  ", path);
    }
    fmt::print("\n");
}

int main(int argc, char* argv[]) {
    int hidden_files = 0;
    int hidden_files_global = 0;
    int only_directories = 0;
    int c = 0;
    int i = 1;

    while ((c = getopt(argc, argv, "aAd")) != -1) {
        switch (c) {
            case 'a':
                hidden_files_global = 1;
                i++;
                break;
            case 'A':
                hidden_files = 1;
                i++;
                break;
            case 'd':
                only_directories = 1;
                i++;
                break;
            default:
                break;
        }
    }
    if (argc == i) {
        print_content(".", hidden_files, hidden_files_global, only_directories);
    }
    for (; i < argc; i++) {
        print_content(argv[i], hidden_files, hidden_files_global, only_directories);
    }
}