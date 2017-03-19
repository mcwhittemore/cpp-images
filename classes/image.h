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
    int size;
    int id;
    int ToPos(int x, int y, int c);
    
  public:
    Image(bool d = false);
    ~Image();
    void Setup(int w, int h);
    void Paint(unsigned char* color);
    int Get(int x, int y, int c);
    void Set(int x, int y, int c, int v);
    void Set(int x, int y, unsigned char* color);
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
  size = width * height * numChannels;
  pix = static_cast<unsigned char*>(malloc(size));
}

void Image::Paint(unsigned char* color) {
  for (int i=0; i<size; i+=numChannels) {
    pix[i] = color[0];
    pix[i+1] = color[1];
    pix[i+2] = color[2];
    if (numChannels == 4) pix[i+3] = color[3];
  }
}

int Image::Get(int x, int y, int c) {
  int pos = ToPos(x, y, c);
  return pix[pos];
}

void Image::Set(int x, int y, int c, int v) {
  int pos = ToPos(x, y, c);
  pix[pos] = v;
}

void Image::Set(int x, int y, unsigned char* color) {
 int pos = ToPos(x, y, 0); 
 for (int c=0; c<numChannels; c++) {
   pix[pos+c] = color[c];
 }
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
