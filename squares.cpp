#include <Magick++.h> 
#include <iostream> 

using namespace std; 
using namespace Magick; 

int main(int argc,char **argv) 
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

  unsigned char* pix = static_cast<unsigned char*>(malloc(width*height*3));

  int mw = width/squareSize;

  for (int x=0; x<width; x++) {
    for (int y=0; y<height; y++) {
      int pos = (x*height*3)+(y*3);

      int xp = x/squareSize; // current x square pos
      int yp = y/squareSize; // current y square pos
      int cp = (xp*mw)+yp;   // current position if all squares where in a line
      int color = cp % numColors; // current color of square

      for (int c=0; c<3; c++) {
        pix[pos+c] = colors[(color*3)+c];
      }
    }
  }

  // Initialise ImageMagick library
  InitializeMagick(*argv);

  // Create Image object and read in from pixel data above
  Image image; 
  image.read(width, height,"RGB",CharPixel,pix);

  // Write the image to a file - change extension if you want a GIF or JPEG
  image.write("output/result.png"); 
}
