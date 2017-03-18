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
    }
};

}
