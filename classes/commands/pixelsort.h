#pragma once

#include <algorithm>
#include <vector>

#include "../exceptions.h"
#include "../image.h"
#include "../color_sort.h"

using namespace std; 

namespace pixicog {

class RunPixelsort {
  private:
    string file;
  public:
    RunPixelsort(int argc, char *args[]) {
      if (argc < 1) {
        throw CommandMissingArgs;
      }

      file = (string) args[0];
    }
    void Run(Image *img) {
      img->Open(file);

      int width = img->Width();
      int height = img->Height();
      int numChannels = img->NumChannels();

      vector<unsigned char* > col(height);
      for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
          unsigned char color[numChannels];
          for (int c=0; c<numChannels; c++) {
            unsigned char v = img->Get(x, y, c); 
            color[c] = v;
          }
          col[y] = color;
        }

        //sort(col.begin(), col.end(), ColorDistanceSort);

        for (int y=0; y<height; y++) {
          unsigned char* newColor = col[y];
          img->Set(x, y, newColor);
        }

        col.erase(col.begin(), col.end());
      }
    }
};

}

