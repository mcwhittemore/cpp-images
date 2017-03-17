#include <iostream> 
#include "./classes/image.h"

// the list of commands
#include "./classes/command.h"
#include "./classes/commands/squares.h"

using namespace std; 
using namespace pixicog;

int main(int argc, char * argv[]) {
  // 1: path
  // 2: command
  // 3: output
  // mas: to be passed to command.
  
  int size = argc - 2;
  char  *args[size];
  for (int i=2; i<argc; i++) {
    printf("arg %d is %s\n", i-2, argv[i]);
    args[i-2] = argv[i];
  }

  char* command = argv[1];

  Command *cmd;

  if (strcmp(command, "squares") == 0) {
    RunSquares rs = RunSquares(size, args);
    cmd = &rs;
  }
  else {
    printf("'%s' is an invalid command", command);
    return 1;
  }

  Image::init(*argv);
  cmd->Run();
  cmd->Save("output/result.png");

  return 0;
}
