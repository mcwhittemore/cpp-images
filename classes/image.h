#pragma once

#include <Magick++.h> 

using namespace std; 

namespace pixicog {

class Image {
  private:
    unsigned char* pix;
    int width;
    int height;
    int numChannels;
    int toPos(int x, int y, int c);
    int id;
    bool debug;
    
  public:
    Image(bool d = false);
    ~Image();
    void setup(int w, int h);
    int get(int x, int y, int c);
    void set(int x, int y, int c, int v);
    void save(string file);
    static void init(char *argv);
};

Image::Image(bool d) {
  debug = d;
  id = rand() % 1000;
  if (debug) {
    printf("create image - %d\n", id);
  }
}

Image::~Image() {
  free(pix);
  if (debug) {
    printf("delete image - %d\n", id);
  }
}

void Image::setup(int w, int h) {
  width = w;
  height = h;
  numChannels = 3;
  pix = static_cast<unsigned char*>(malloc(width*height*numChannels));
}

void Image::init(char *argv) {
 Magick::InitializeMagick(argv);
}

int Image::toPos(int x, int y, int c) {
  return (y*width*numChannels)+(x*numChannels) + c;
}

int Image::get(int x, int y, int c) {
  int pos = toPos(x, y, c);
  return pix[pos];
}

void Image::set(int x, int y, int c, int v) {
  int pos = toPos(x, y, c);
  pix[pos] = v;
}

void Image::save(string file) {
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
