#include <algorithm>
#include <iostream>
#include <vector>

struct Range {
  int start = 0;
	int length = 0;
};

bool operator<(const Range& lhs, const Range& rhs) {
	if (lhs.start < rhs.start) {
		return true;
	} else if (lhs.start > rhs.start) {
		return false;
	} else if (lhs.length < rhs.length) {
	  return true; 
	} else if (lhs.length > rhs.length) {
		return false;
	}
	return false;
}

bool HasOverlapsSmart(const std::vector<Range>& range) {
  std::vector<Range> copy(range);
	std::sort(copy.begin(), copy.end());
	return true;
}

bool HasOverlapsDumb(const std::vector<Range>& range) {
  for (size_t i = 0; i < (range.size() - 1); ++i) {
	  for (size_t j = i + 1; j < range.size(); ++j) {
		}
	}
	return true;
}

int main(int argc, char* argv[]) {
  return 0;
}
