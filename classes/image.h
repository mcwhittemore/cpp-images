#pragma once

#include <Magick++.h> 

using namespace std; 

namespace pixicog {

class Image {
  private:
    bool setup;
    bool debug;
    unsigned char* pix;
    int width;
    int height;
    int numChannels;
    int id;
    int ToPos(int x, int y, int c);
    
  public:
    Image(bool d = false);
    ~Image();
    void Setup(int w, int h);
    int Get(int x, int y, int c);
    void Set(int x, int y, int c, int v);
    void Save(string file);
    static void Init(char *argv) {
      Magick::InitializeMagick(argv);
    };
};

/** Constructur **/

Image::Image(bool d) {
  debug = d;
  setup = false;
  id = rand() % 1000;
  if (debug) {
    printf("create image - %d\n", id);
  }
}

/** Deconstructor **/

Image::~Image() {
  if (setup == false) return; 
  free(pix);
  if (debug) {
    printf("delete image - %d\n", id);
  }
}

/** PRIVATE - turn x, y, c into an pos in the underlaying array **/

int Image::ToPos(int x, int y, int c) {
  return (y*width*numChannels)+(x*numChannels) + c;
}

/** Config the under laying underlaying **/

void Image::Setup(int w, int h) {
  if (setup) throw "You cannot setup multiple times";
  setup = true;
  width = w;
  height = h;
  numChannels = 3;
  pix = static_cast<unsigned char*>(malloc(width*height*numChannels));
}

int Image::Get(int x, int y, int c) {
  int pos = ToPos(x, y, c);
  return pix[pos];
}

void Image::Set(int x, int y, int c, int v) {
  int pos = ToPos(x, y, c);
  pix[pos] = v;
}

void Image::Save(string file) {
  // Create Image object and read in from pixel data above
  Magick::Image image; 
  if (debug) {
    printf("save image - %d\n", id);
  }
  image.read(width, height,"RGB",Magick::CharPixel,pix);

  // Write the image to a file - change extension if you want a GIF or JPEG
  image.write(file); 
}

}
