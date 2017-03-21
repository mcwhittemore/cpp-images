#pragma once

#include <Magick++.h> 
#include "./exceptions.h"

using namespace std; 

namespace pixicog {

class Image {
  private:
    bool setup;
    bool debug;
    unsigned char* pix;
    int id;
    int ToPos(int x, int y, int c);
    int size;
    int width;
    int height;
    int numChannels;

  public:
    Image(bool d = false);
    ~Image();
    void Setup(int w, int h, int c=3);
    void Open(string file);
    void Paint(unsigned char* color);
    int Size() { return size; };
    int Width() { return width; };
    int Height() { return height; };
    int NumChannels() { return numChannels; };
    int Get(int x, int y, int c);
    void Set(int x, int y, int c, int v);
    void Set(int p, int v);
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

void Image::Setup(int w, int h, int c) {
  if (setup) throw ImageMultipleSetup;
  setup = true;
  width = w;
  height = h;
  numChannels = c;
  size = width * height * numChannels;
  pix = static_cast<unsigned char*>(malloc(size));
}

void Image::Open(string path) {
  if (setup) throw ImageMultipleSetup;
  Magick::Image image; 
  image.read(path);

  width = (int) image.columns();
  height = (int) image.rows();
  numChannels = (int) image.channels();
  Setup(width, height, numChannels);

  MagickCore::Quantum *pixels = image.getPixels(0, 0, width, height);

  for (int x=0; x<width; x++) {
    for (int y=0; y<height; y++) {
      unsigned offset = numChannels * (width * y + x);
      for (int c=0; c<numChannels; c++) {
        pix[offset+c] = pixels[offset+c];
      }
    }
  }
  
  printf("width: %d, height: %d\n", width, height);

}

int Image::Get(int x, int y, int c) {
  if (!setup) throw ImageNotSetup;
  int pos = ToPos(x, y, c);
  return pix[pos];
}

// Set a specific channel for one pixel
void Image::Set(int x, int y, int c, int v) {
  if (!setup) throw ImageNotSetup;
  int pos = ToPos(x, y, c);
  pix[pos] = v;
}

// Set all channels for one pixel
void Image::Set(int x, int y, unsigned char* color) {
  if (!setup) throw ImageNotSetup;
 int pos = ToPos(x, y, 0); 
 for (int c=0; c<numChannels; c++) {
   pix[pos+c] = color[c];
 }
}

//Set a specific value in the underlaying array
void Image::Set(int p, int v) {
  pix[p] = v;
}

void Image::Save(string file) {
  if (!setup) throw ImageNotSetup;
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
