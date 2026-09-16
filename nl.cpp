#include <fmt/core.h>
#include <fstream>

using std::string, std::ifstream, std::ios;
using fmt::println;

int count_lines(string filename) {
  ifstream in_file{filename, std::ios::binary};
  string line;
  int result = 0;

  while (in_file) {
    getline(in_file, line);
    result++;
  }
  return result;
}

int main(int argc, char* argv[]) {
  int i = 1;
  int result;

  if (argc < 2)
    return 84;
  while (i < argc) {
    result = count_lines(argv[i]);
    println("{}: {} lines", argv[i], result - 1);
    i++;
  }
}
