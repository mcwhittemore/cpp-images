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
    int state;
  public:
    RunPixelsort(int argc, char *args[]) {
      if (argc < 1) {
        throw CommandMissingArgs;
      }

      file = (string) args[0];
      state = 0;
    }
    void Run(Image *img) {
      img->Open(file);

      int width = img->Width();
      int height = img->Height();
      int numChannels = img->NumChannels();

      vector<vector<unsigned char> > col(height);
      for (int x=0; x<width; x++) {
        int first = -1;
        for (int y=0; y<height; y++) {
          vector<unsigned char> color(numChannels);
          for (int c=0; c<numChannels; c++) {
            unsigned char v = img->Get(x, y, c); 
            color[c] = v;
          }
          col[y] = color;

          int isMatch = CheckForMatch(color, first, y);

          if (first == -1 && isMatch == 1) {
            first = y;
          }
          else if (first != -1 && isMatch == 0) {
            //printf("dist: %d\n", y-first);
            sort(col.begin()+first, col.begin()+y, ColorDistanceSort);
            first = -1;
          }
          else if (isMatch == -1) {
            first = -1;
          }
        }

        if (first != -1) {
          sort(col.begin()+first, col.end(), ColorDistanceSort);
        }

        for (int y=0; y<height; y++) {
          vector<unsigned char> newColor = col[y];
          for (int c=0; c<numChannels; c++) {
            img->Set(x, y, c, newColor[c]);
          }
        }
      }
    };
    int CheckForMatch(vector<unsigned char> color, int from, int at) {
      int g = (color[1] + 1);
      if (from == -1) {
        state = g;
        return 1;
      }

      if (at - from < state) return 1;

      bool greenIsMax = color[0] < color[1] && color[1] > color[2];
      int gor = (int) color[1] / (color[0] + 1);
      int gob = (int) color[1] / (color[2] + 1);

      if (gor < 2 || gob < 2) return 0;

      if (g < state && greenIsMax) {
        state = g;
        return 1;
      }

      return 0;
    }
};

}

