#pragma once

using namespace std;

namespace pixicog {

bool ColorDistanceSort (unsigned char* c1, unsigned char* c2) {
  for (int c = 0; c<3; c++) {
    if (c1[c] - c2[c] < 0) return true;
    if (c1[c] - c2[c] > 0) return false;
  }

  return false;

}

}

