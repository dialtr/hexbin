
#include <iostream>
#include <string>
#include <vector>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "hexbin.h"

using std::cout;
using std::endl;

ABSL_FLAG(std::string, output_file, "", "required: path to target binary file");
ABSL_FLAG(int, binary_size, -1,
          "optional: max binary size; pads out if necessary");
ABSL_FLAG(std::string, fill_byte, "",
          "optional: fill byte for undefined regions: default 0xff");

int main(int argc, char* argv[]) {
  std::vector<char*> input_files = absl::ParseCommandLine(argc, argv);
  for (auto f : input_files) {
    cout << f << endl;
  }
  return 0;
}
