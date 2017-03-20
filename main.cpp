#include <iostream> 

#include "./classes/exceptions.h"
#include "./classes/image.h"

// the list of commands
#include "./classes/commands/squares.h"
#include "./classes/commands/cracks.h"

using namespace std; 
using namespace pixicog;

int main(int argc, char * argv[]) {
  // 1: path
  // 2: command
  // 3: output
  // mas: to be passed to command.

  try {
    if (argc < 3) throw MainMissingArgs;

    char* command = argv[1];
    char* filePath = argv[2];

    int size = argc - 3;
    char  *args[size];
    for (int i=3; i<argc; i++) {
      args[i-3] = argv[i];
    }

    Image::Init(*argv);

    Image img = Image();

    if (strcmp(command, "squares") == 0) {
      RunSquares rs(size, args);
      rs.Run(&img);
    }
    else if (strcmp(command, "cracks") == 0) {
      RunCracks rc(size, args);
      rc.Run(&img);
    }
    else {
      printf("'%s' is an invalid command", command);
      return 1;
    }

    img.Save(filePath);
  }
  catch (exception &e) {
    cout << e.what() << "\n";
    return 1;
  }

  return 0;
}
