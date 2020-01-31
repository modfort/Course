#ifndef MYSOK_H
#define MYSOK_H
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <string>
#include <vector>
#include <utility>
#define NBL 100
#define NBC 100

int board[NBL][NBC];
int board_nbl;
int man_l;
int man_c;
std::vector<std::pair<int,int>> Pos;
#define MOVE_U 0
#define MOVE_D 1
#define MOVE_L 2
#define MOVE_R 3

#define FREE 0
#define TARGET 1
#define WALL 2
#define CRATE_ON_FREE 3
#define CRATE_ON_TARGET 4
#define MAN_ON_FREE 5
#define MAN_ON_TARGET 6
#define END_OF_LINE 7

char board_str[] = {' ','.','#','$','*','@','a'};

void init_board() {
  for(int i = 0; i < NBL; i++)
    for(int j = 0; j < NBC; j++)
      board[i][j] = FREE;
}
void print_board() {
	printf("	%d %d \n",man_l,man_c );
  for(int i = 0; i < board_nbl; i++) {
    for(int j = 0; j < NBC; j++) {
      if(board[i][j]==END_OF_LINE) break;
      printf("%c", board_str[board[i][j]]);
    }
    printf("\n");
  }
}
void load(char* _file) {
  FILE *fp = fopen(_file, "r");
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  if (fp == NULL) {
    perror("fopen"); exit(EXIT_FAILURE);
  }
  board_nbl = 0;
  while ((nread = getline(&line, &len, fp)) != -1) {
    if(((int)nread) > 0) {
      bool read_ok = false;
      for(int i = 0; i < nread; i++) {
      	if(line[i] == board_str[FREE]) board[board_nbl][i] = FREE;
      	if(line[i] == board_str[TARGET]) board[board_nbl][i] = TARGET;
      	if(line[i] == board_str[WALL]) {
	  read_ok = true; board[board_nbl][i] = WALL;
	}
      	if(line[i] == board_str[CRATE_ON_FREE]) board[board_nbl][i] = CRATE_ON_FREE;
      	if(line[i] == board_str[CRATE_ON_TARGET]) board[board_nbl][i] = CRATE_ON_TARGET;
      	if(line[i] == board_str[MAN_ON_FREE]) {
	  man_l = board_nbl; man_c = i;
	  Pos.push_back(std::make_pair(man_l,man_c)); 
	  board[board_nbl][i] = MAN_ON_FREE;
	}
      	if(line[i] == board_str[MAN_ON_TARGET]) {
	  man_l = board_nbl; man_c = i; 
	  board[board_nbl][i] = MAN_ON_TARGET;
	  Pos.push_back(std::make_pair(man_l,man_c)); 

	}
      }
      if(read_ok) {
	board[board_nbl][nread]=END_OF_LINE;
	board_nbl++;
      }
    }
  }
  free(line);
  fclose(fp);
}
bool can_move_U() {
  if(man_l <= 1) return false;
  if(board[man_l-1][man_c]==FREE) return true;
  if(man_l >= 3) {
    if(board[man_l-1][man_c]==CRATE_ON_FREE &&
       (board[man_l-2][man_c]==FREE || board[man_l-2][man_c]==TARGET)) return true;
    if(board[man_l-1][man_c]==CRATE_ON_TARGET &&
       (board[man_l-2][man_c]==FREE || board[man_l-2][man_c]==TARGET)) return true;
  }
  return false;
}
void move_U() {
  if(board[man_l-1][man_c]==FREE) {
    if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
    if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
    board[man_l-1][man_c] = MAN_ON_FREE;
    man_l-=1;
    Pos.push_back(std::make_pair(man_l,man_c));
    return;
  }
  if(board[man_l-1][man_c]==TARGET) {
    if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
    if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
    board[man_l-1][man_c] = MAN_ON_TARGET;
    man_l-=1;
    Pos.push_back(std::make_pair(man_l,man_c));
    return;
  }
  if(board[man_l-2][man_c]==FREE) {
    if(board[man_l-1][man_c]==CRATE_ON_FREE) {
      if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
      if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
      board[man_l-1][man_c]=MAN_ON_FREE;
      board[man_l-2][man_c]=CRATE_ON_FREE;
      man_l-=1;
      Pos.push_back(std::make_pair(man_l,man_c));
      return;
    }
    if(board[man_l-1][man_c]==CRATE_ON_TARGET) {
      if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
      if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
      board[man_l-1][man_c]=MAN_ON_TARGET;
      board[man_l-2][man_c]=CRATE_ON_FREE;
      man_l-=1;
      Pos.push_back(std::make_pair(man_l,man_c));
      return;
    }
  }
  if(board[man_l-2][man_c]==TARGET) {
    if(board[man_l-1][man_c]==CRATE_ON_FREE) {
      if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
      if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
      board[man_l-1][man_c]=MAN_ON_FREE;
      board[man_l-2][man_c]=CRATE_ON_TARGET;
      man_l-=1;
      Pos.push_back(std::make_pair(man_l,man_c));
      return;
    }
    if(board[man_l-1][man_c]==CRATE_ON_TARGET) {
      if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
      if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
      board[man_l-1][man_c]=MAN_ON_TARGET;
      board[man_l-2][man_c]=CRATE_ON_TARGET;
      man_l-=1;
      Pos.push_back(std::make_pair(man_l,man_c));
      return;
    }
  }
}
bool can_move_D() {
  if(man_l > board_nbl) return false;
  if(board[man_l+1][man_c]==FREE) return true;
  if(man_l >= 3) {
    if(board[man_l+1][man_c]==CRATE_ON_FREE &&
       (board[man_l+2][man_c]==FREE || board[man_l+2][man_c]==TARGET)) return true;
    if(board[man_l+1][man_c]==CRATE_ON_TARGET &&
       (board[man_l+2][man_c]==FREE || board[man_l+2][man_c]==TARGET)) return true;
  }
  return false;
}

void move_D() {
  if(board[man_l+1][man_c]==FREE) {
    if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
    if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
    board[man_l+1][man_c] = MAN_ON_FREE;
    man_l+=1;
    Pos.push_back(std::make_pair(man_l,man_c));
    return;
  }
  if(board[man_l+1][man_c]==TARGET) {
    if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
    if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
    board[man_l+1][man_c] = MAN_ON_TARGET;
    man_l+=1;
    Pos.push_back(std::make_pair(man_l,man_c));
    return;
  }
  if(board[man_l+2][man_c]==FREE) {
    if(board[man_l+1][man_c]==CRATE_ON_FREE) {
      if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
      if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
      board[man_l+1][man_c]=MAN_ON_FREE;
      board[man_l+2][man_c]=CRATE_ON_FREE;
      man_l+=1;
      Pos.push_back(std::make_pair(man_l,man_c));
      return;
    }
    if(board[man_l+1][man_c]==CRATE_ON_TARGET) {
      if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
      if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
      board[man_l+1][man_c]=MAN_ON_TARGET;
      board[man_l+2][man_c]=CRATE_ON_FREE;
      man_l+=1;
      Pos.push_back(std::make_pair(man_l,man_c));
      return;
    }
  }
  if(board[man_l+2][man_c]==TARGET) {
    if(board[man_l+1][man_c]==CRATE_ON_FREE) {
      if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
      if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
      board[man_l+1][man_c]=MAN_ON_FREE;
      board[man_l+2][man_c]=CRATE_ON_TARGET;
      man_l+=1;
      Pos.push_back(std::make_pair(man_l,man_c));
      return;
    }
    if(board[man_l+1][man_c]==CRATE_ON_TARGET) {
      if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
      if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
      board[man_l+1][man_c]=MAN_ON_TARGET;
      board[man_l+2][man_c]=CRATE_ON_TARGET;
      man_l+=1;
      Pos.push_back(std::make_pair(man_l,man_c));
      return;
    }
  }
}
bool can_move_L() {
  if( man_c <= 1) return false;
  if(board[man_l][man_c-1]==FREE) return true;
  if(man_c >= 3) {
    if(board[man_l][man_c-1]==CRATE_ON_FREE &&
       (board[man_l][man_c-2]==FREE || board[man_l-2][man_c]==TARGET)) return true;
    if(board[man_l][man_c-1]==CRATE_ON_TARGET &&
       (board[man_l][man_c-2]==FREE || board[man_l-2][man_c]==TARGET)) return true;
  }
  return false;
}

void move_L() {
  if(board[man_l][man_c-1]==FREE) {
    if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
    if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
    board[man_l][man_c-1] = MAN_ON_FREE;
    man_c-=1;
    Pos.push_back(std::make_pair(man_l,man_c));
    return;
  }
  if(board[man_l][man_c-1]==TARGET) {
    if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
    if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
    board[man_l][man_c-1] = MAN_ON_TARGET;
    man_c-=1;
    Pos.push_back(std::make_pair(man_l,man_c));
    return;
  }
  if(board[man_l][man_c+2]==FREE) {
    if(board[man_l][man_c-1]==CRATE_ON_FREE) {
      if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
      if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
      board[man_l][man_c-1]=MAN_ON_FREE;
      board[man_l][man_c+2]=CRATE_ON_FREE;
      man_c-=1;
      Pos.push_back(std::make_pair(man_l,man_c));
      return;
    }
    if(board[man_l][man_c-1]==CRATE_ON_TARGET) {
      if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
      if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
      board[man_l][man_c-1]=MAN_ON_TARGET;
      board[man_l][man_c+2]=CRATE_ON_FREE;
      man_c-=1;
      Pos.push_back(std::make_pair(man_l,man_c));
      return;
    }
  }
  if(board[man_l][man_c+2]==TARGET) {
    if(board[man_l][man_c-1]==CRATE_ON_FREE) {
      if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
      if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
      board[man_l][man_c-1]=MAN_ON_FREE;
      board[man_l][man_c+2]=CRATE_ON_TARGET;
      man_c-=1;
      Pos.push_back(std::make_pair(man_l,man_c));
      return;
    }
    if(board[man_l][man_c-1]==CRATE_ON_TARGET) {
      if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
      if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
      board[man_l][man_c-1]=MAN_ON_TARGET;
      board[man_l][man_c+2]=CRATE_ON_TARGET;
      man_c-=1;
      Pos.push_back(std::make_pair(man_l,man_c));
      return;
    }
  }
}
bool can_move_R() {
  if(man_c <= 1) return false;
  if(board[man_l][man_c+1]==FREE) return true;
  if(man_c >= 3) {
    if(board[man_l][man_c+1]==CRATE_ON_FREE &&
       (board[man_l][man_c+2]==FREE || board[man_l+2][man_c]==TARGET)) return true;
    if(board[man_l][man_c+1]==CRATE_ON_TARGET &&
       (board[man_l][man_c+2]==FREE || board[man_l+2][man_c]==TARGET)) return true;
  }
  return false;
}

void move_R() {
  if(board[man_l][man_c+1]==FREE) {
    if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
    if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
    board[man_l][man_c+1] = MAN_ON_FREE;
    man_c+=1;
    Pos.push_back(std::make_pair(man_l,man_c));
    return;
  }
  if(board[man_l][man_c+1]==TARGET) {
    if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
    if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
    board[man_l][man_c+1] = MAN_ON_TARGET;
    man_c+=1;
    Pos.push_back(std::make_pair(man_l,man_c));
    return;
  }
  if(board[man_l][man_c+2]==FREE) {
    if(board[man_l][man_c+1]==CRATE_ON_FREE) {
      if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
      if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
      board[man_l][man_c+1]=MAN_ON_FREE;
      board[man_l][man_c+2]=CRATE_ON_FREE;
      man_c+=1;
      Pos.push_back(std::make_pair(man_l,man_c));
      return;
    }
    if(board[man_l][man_c+1]==CRATE_ON_TARGET) {
      if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
      if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
      board[man_l][man_c+1]=MAN_ON_TARGET;
      board[man_l][man_c+2]=CRATE_ON_FREE;
      man_c+=1;
      Pos.push_back(std::make_pair(man_l,man_c));
      return;
    }
  }
  if(board[man_l][man_c+2]==TARGET) {
    if(board[man_l][man_c+1]==CRATE_ON_FREE) {
      if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
      if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
      board[man_l][man_c+1]=MAN_ON_FREE;
      board[man_l][man_c+2]=CRATE_ON_TARGET;
      man_c+=1;
      Pos.push_back(std::make_pair(man_l,man_c));
      return;
    }
    if(board[man_l][man_c+1]==CRATE_ON_TARGET) {
      if(board[man_l][man_c]==MAN_ON_FREE) board[man_l][man_c]=FREE;
      if(board[man_l][man_c]==MAN_ON_TARGET) board[man_l][man_c]=TARGET;
      board[man_l][man_c+1]=MAN_ON_TARGET;
      board[man_l][man_c+2]=CRATE_ON_TARGET;
      man_c+=1;
      Pos.push_back(std::make_pair(man_l,man_c));
      return;
    }
  }
}

void play(int dir)
{
	switch(dir){
	case 0: move_U(); break;
	case 1:move_D();break;
	case 2:move_L(); break;
	case 3 : move_R();break;
	default: printf("%s\n","erreur d'entre de donneés" ); break;

	}
}

void unplay()
{	
	if(Pos.size()>1){
		printf("\n");
		for(auto e:Pos)
			printf("%d %d \n",e.first,e.second );
		printf("\n");

		printf("je suis rentre\n");
		Pos.pop_back();
		printf("%d %d \n",Pos.back().first,Pos.back().second );
		man_c=Pos.back().second;
		man_l=Pos.back().first;


	}
	else
		printf("erreur nous sommes a la position iniale\n");	
}		

#endif
