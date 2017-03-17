#pragma once

#include "./image.h"

using namespace std; 

namespace pixicog {

class Command {
  protected:
    Image img;

  public:
    Command(int c, char *s[]) {
      img = Image(0, 0);
    }

    virtual void Run(){};
    void Save(string path);
};

void Command::Save(string path) {
  img.save(path);
}

}

