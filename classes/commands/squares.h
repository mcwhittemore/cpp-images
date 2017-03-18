#pragma once

using namespace std; 

namespace pixicog {

class RunSquares {
  private:
    int squareSize;
    int width;
    int height;
  public:
    RunSquares(int argc, char *args[]) {
      if (argc != 2) {
        throw "You must provide width and height as numbers";
      }
  
      squareSize = 20;
      width = stoi(args[0]) * squareSize;
      height = stoi(args[1]) * squareSize;

    }
    void Run(Image *img) {
      img->Setup(width, height);

      unsigned char colors[]={0,0,0, 255,0,0, 255,255,0, 255,0,255, 255,255,255, 0,255,0, 0,255,255, 0,0,255};

      int numColors = 8;

      int mw = width/squareSize;

      for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {

          int xp = x/squareSize; // current x square pos
          int yp = y/squareSize; // current y square pos
          int cp = (xp*mw)+yp;   // current position if all squares where in a line
          int color = cp % numColors; // current color of square

          for (int c=0; c<3; c++) {
            img->Set(x, y, c, colors[(color*3)+c]);
          }
        }
      }

    }
};

}
