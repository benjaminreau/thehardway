#include <fmt/core.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <unistd.h>

namespace fs = std::filesystem;

void copy_directory(fs::path source, fs::path target) {
    if (fs::is_directory(source)) {
        fs::create_directory(target);
        for(auto& dir_entry : fs::directory_iterator{source}) {
            fs::path new_target = target / dir_entry.path().filename();
            copy_directory(dir_entry.path(), new_target);
        }
    } else {
        fs::copy_file(source, target);
    }
}

int main(int argc, char* argv[]) {
    int c = 0;
    int i = 1;
    int recursive = 0;

    while ((c = getopt(argc, argv, "r")) != -1) {
        switch (c) {
            case 'r':
            recursive = 1;
            i++;
            break;
            default:
            break;
        }
    }
    if(recursive == 0 && argc != 3) {
        fmt::println("USAGE: cp <from_file> <to_file>");
        return 1;
    }
    if (recursive == 1 && fs::is_directory(argv[i])) {
        copy_directory(argv[i], argv[i + 1]);
    } else {
        try {
            fs::copy_file(argv[i], argv[i + 1]);
        } catch(fs::filesystem_error &e) {
            fmt::println("failed to copy: {}", e.what());
        }
    }
}
