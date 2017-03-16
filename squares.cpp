#include <Magick++.h> 
#include <iostream> 

#include "./classes/image.h"

using namespace std; 
using namespace pixicognitive;

int main(int argc, char **argv) 
{ 
  if (argc != 3) {
    cout << "You must provide width and height as numbers\n";
    return 1;
  }

  int squareSize = 20;
  int width = stoi(argv[1]) * squareSize;
  int height = stoi(argv[2]) * squareSize;

  unsigned char colors[]={0,0,0, 255,0,0, 255,255,0, 255,0,255, 255,255,255, 0,255,0, 0,255,255, 0,0,255};

  int numColors = 8;

  Image::init(*argv);
  Image img = Image (width, height);

  int mw = width/squareSize;

  for (int x=0; x<width; x++) {
    for (int y=0; y<height; y++) {

      int xp = x/squareSize; // current x square pos
      int yp = y/squareSize; // current y square pos
      int cp = (xp*mw)+yp;   // current position if all squares where in a line
      int color = cp % numColors; // current color of square

      for (int c=0; c<3; c++) {
        img.set(x, y, c, colors[(color*3)+c]);
      }
    }
  }

  img.save("output/result.png");

}
