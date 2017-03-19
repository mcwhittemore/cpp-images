#pragma once

using namespace std; 

namespace pixicog {

class RunCracks {
  private:
    int width;
    int height;
  public:
    RunCracks(int argc, char *args[]) {
      if (argc != 2) {
        printf("why %d", argc);
        throw "You must provide width and height as numbers";
      }
  
      width = stoi(args[0]);
      height = stoi(args[1]);

    }
    void Run(Image *img) {
      img->Setup(width, height);
      unsigned char white[]={255,255,255};
      img->Paint(white);

      unsigned char black[]={0,0,0};
      int lx = ((rand() % width) / 3) * 2;
      int maxDis = width / 20;
      int dx = (rand() % maxDis);

      for (int y=0; y<height; y++) {
        img->Set(lx, y, black);
        img->Set(lx+dx, y, black);
        int shift = (rand() % 3) - 1;
        lx += shift;
        int slide = (rand() % 3) - 1;
        dx += slide;
        if (dx > maxDis) dx = maxDis;
      }
    }
};

}
