#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <string>
#include <unordered_map>
#include "mysok.h"

int main(int _ac, char** _av) {
  if(_ac != 2) { printf("usage: %s SOK_FILE\n", _av[0]); return 0; }

  srand(2);
  load(_av[1]);
  move_U();
 print_board();
 unplay();
 print_board();	

  return 0;
}
