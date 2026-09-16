#include <fmt/core.h>
#include <fstream>
#include <unistd.h>

using std::string, std::ifstream, std::ios;
using fmt::println;

void print_file(string filename, int print_nb, int print_squeeze) {
  ifstream in_file{filename, std::ios::binary};
  string line;
  int i = 1;

  getline(in_file, line);
  while (in_file) {
    if (print_nb == 1) {
      fmt::print("  {}\t", i);
      i++;
    }
    if (line == "" && print_squeeze == 1) {
      getline(in_file, line);
      continue;
    }
    println("{}", line);
    getline(in_file, line);
  }
  return;
}

int main(int argc, char* argv[]) {
  int i = 1;
  int c = 0;
  int print_nb = 0;
  int print_squeeze = 0;

  while ((c = getopt(argc, argv, "ns")) != -1) {
    switch (c) {
      case 'n':
        print_nb = 1;
        i += 1;
        break;
      case 's':
        i += 1;;
        print_squeeze = 1;
        break;
      default:
        break;
    }
  }
  while (i < argc) {
    print_file(argv[i], print_nb, print_squeeze);
    i++;
  }
}
