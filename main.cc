#include <stdlib.h>
#include <unistd.h>

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "record.h"

using std::cerr;
using std::cout;
using std::endl;

ABSL_FLAG(std::string, output_file, "", "required: path to target binary file");
ABSL_FLAG(int, binary_size, -1,
          "optional: max binary size; pads out if necessary");
ABSL_FLAG(std::string, fill_byte, "",
          "optional: fill byte for undefined regions: default 0xff");

int main(int argc, char* argv[]) {
  std::vector<char*> input_files = absl::ParseCommandLine(argc, argv);
  for (size_t i = 1; i < input_files.size(); ++i) {
    std::string file_name(input_files[i]);
    std::ifstream file;
    file.open(file_name.c_str(), std::ios::binary | std::ios::in);
    if (!file.is_open()) {
      cerr << "hexbin: failed to open file: '" << file_name << "'" << endl;
      exit(1);
    }
    while (!file.eof()) {
      absl::StatusOr<Record> record = Record::Read(file);
      if (!record.ok()) {
        cerr << "hexbin: error reading record: " << record.status() << endl;
        exit(1);
      }
      if (record.value().IsEof()) {
        break;
      }
      cout << "Read record, checksum: "
           << static_cast<int>(record.value().provided_checksum())
           << " validated: "
           << (record.value().IsValidChecksum() ? "true" : "false") << endl;
    }
    file.close();
  }
  return 0;
}
