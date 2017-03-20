#include "./exceptions.h"

using namespace std;

namespace pixicog {

class Gradiente {
  private:
    unsigned char* from;
    unsigned char* to;
    int size;
  public:
    Gradiente(unsigned char* c1, unsigned char* c2, int s);
    void Get(int le, int pos, unsigned char *color);

};

Gradiente::Gradiente(unsigned char* c1, unsigned char* c2, int s) {
  size = s;
  from = c1;
  to = c2;
};

void Gradiente::Get(int len, int pos, unsigned char *color) {
  for (int i=0; i<size; i++) {
    if (pos > len) {
      color[i] = to[i];
      continue;
    }
    else if (pos < 0) {
      color[i] = from[i];
      continue;
    }
    double per = (double)(to[i] - from[i]) / len;
    int growth = (int) per * pos;
    color[i] = from[i] + growth;
  }
}

}
