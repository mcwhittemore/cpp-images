#include "./image.h"

namespace pixicog {

class Paint {
  private:
    Image *img;
  public:
    Paint(Image *i) { img = i; };
    void Fill(unsigned char* color);
};

void Paint::Fill(unsigned char* color) {
  int size = img->Size();
  int numChannels = img->NumChannels();
  for (int i=0; i<size; i+=numChannels) {
    for (int c=0; c<numChannels; c++) {
      img->Set(i+c, color[c]);
    }
  }
};

}
