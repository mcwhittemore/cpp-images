#pragma once

using namespace std;

namespace pixicog {

bool ColorDistanceSort (vector<unsigned char> c1, vector<unsigned char> c2) {
  for (int c = 0; c<3; c++) {
    if (c1[c] - c2[c] < 0) return false;
    if (c1[c] - c2[c] > 0) return true;
  }

  return false;

}

}

