#include <fmt/core.h>
#include <fstream>
#include <unistd.h>
#include <vector>

using std::string, std::ifstream, std::ios;
using fmt::println;

void print_file(string filename, int count) {
  ifstream in_file{filename, std::ios::binary};
  string line;
  std::vector<string> lines;

  while (getline(in_file, line)) {
    lines.push_back(line);
  }
  int i = lines.size() - count;
  while (i < (int)lines.size()) {
    println("{}", lines[i]);
    i++;
  }

}

int main(int argc, char* argv[]) {
  int c = 0;
  int count = 10;

  while ((c = getopt(argc, argv, "n:")) != -1) {
    switch (c) {
      case 'n':
        count = std::stoi(optarg);
        break;
      default:
        break;
    }
  }
  if (optind < argc) {
    for (int i = optind; i < argc; i++) {
        print_file(argv[i], count);
    }
  }
}
