#ifndef TESTSOK_H
#define TESTSOK_H
#include "mysok.h"

/* position : ...#
 *            ...@
 * can_move_U() return false */
bool test_p001() {
  board[0][0]=WALL; board[0][1]=END_OF_LINE;
  board[1][0]=MAN_ON_FREE;board[1][1]=END_OF_LINE;
  board_nbl=2;
  man_l=1; man_c=0;
  return (can_move_U()==false);
}

/* position : ...#
 *            ...a
 * can_move_U() return false */
bool test_p002() {
  return true;
}

/* position : ...#
 *            ...
 *            ...@
 * can_move_U() return true 
 * move_U() modifie la position : ...#
 *                                ...@
 *                                ...
*/
bool test_p003() {
  board[0][0]=WALL; board[0][1]=END_OF_LINE;
  board[1][0]=FREE; board[1][1]=END_OF_LINE;
  board[2][0]=MAN_ON_FREE;board[2][1]=END_OF_LINE;
  board_nbl=3;
  man_l=2; man_c=0;
  if(can_move_U()==false) return false;
  move_U();
  if(board[1][0]!=MAN_ON_FREE) return false;
  if(board[2][0]!=FREE) return false;
  if(man_l!=1) return false;
  return true;
}

#endif
