#pragma once

#include "../exceptions.h"
#include "../paint.h"
#include "../gradiente.h"

using namespace std; 

namespace pixicog {

class RunCracks {
  private:
    int width;
    int height;
  public:
    RunCracks(int argc, char *args[]) {
      if (argc < 2) {
        cout << "why\n";
        throw CommandMissingArgs;
      }

      width = stoi(args[0]);
      height = stoi(args[1]);

      if (argc == 3) srand(stoi(args[2]));
      else srand(255);

    }
    void Run(Image *img) {
      img->Setup(width, height);
      unsigned char white[]={240,240,240};
      unsigned char black[]={30,30,30};
      unsigned char mat[]={225,225,225};
      Gradiente gray = Gradiente(black, white, 3);

      Paint p = Paint(img);
      p.Fill(mat);

      int x = ((rand() % width) / 3) * 2;
      int maxD = width / 5;
      int minD = width / 10;
      int d = (rand() % (maxD - minD) + minD);
      int fullD = d;

      int ph = (height / 5);
      int sh = rand() % ph;
      int ch = height - sh;
      int yd = (ch / maxD);

      for (int y=0; y<height; y++) {
        if (y % yd == 0) {
          minD -= 1;
          maxD -= 1;
        }
        int ld = (rand() % 3) - 1;
        int rd = (rand() %3) - 1;
        x += ld;
        if (x < minD) x = minD;
        if (x >= (width-minD)) x = width-minD;

        d += rd;
        if (d > maxD) d = maxD;
        if (d < minD) d = minD;

        int x2 = x + d;
        if (x2 > width) x2 = width;

        unsigned char color[img->NumChannels()];
        if (d > fullD) fullD = d;
        for (int i=x; i<=x2; i++) {
          int d = i - x;
          gray.Get(fullD, d, color);
          img->Set(i, y, color);
        }
      }
    }
};

}
