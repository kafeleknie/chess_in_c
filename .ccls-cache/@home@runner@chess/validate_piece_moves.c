#include <stdbool.h>
#include "types.c"
#include <stdlib.h> 

bool validate_pawn_move(struct move* move , enum colors color){
  if(move->to.y > move->from.y && color == WHITE) return false;
  if(move->to.y < move->from.y && color == BLACK) return false;

  int shiftX = abs(move->to.x - move->from.x);
  int shiftY = abs(move->to.y - move->from.y);

  if(shiftX == 0){
    if(shiftY == 1) return true;
    if(shiftY == 2 && ( move->from.y == 1 || move->from.y == 6)) return true;
  }
  return false;
}

bool validate_knight_move(struct move* move , enum colors color){
  int shiftX = abs(move->to.x - move->from.x);
  int shiftY = abs(move->to.y - move->from.y);

  if(abs(shiftX - shiftY) == 1) return true;
  return false;
}

bool validate_bishop_move(struct move* move , enum colors color){
  int shiftX = abs(move->to.x - move->from.x);
  int shiftY = abs(move->to.y - move->from.y);
  if( shiftX == shiftY) return true;
  return false;
}

bool validate_rook_move(struct move* move , enum colors color){
  int shiftX = abs(move->to.x - move->from.x);
  int shiftY = abs(move->to.y - move->from.y);
  if(shiftX == 0 || shiftY == 0) return true;
  return false;
}

bool validate_queen_move(struct move* move ,enum colors color){
  if(validate_rook_move(move,color) || validate_bishop_move(move,color)) return true;
  return false;
}

bool validate_king_move(struct move* move ,enum colors color){
  int shiftX = abs(move->to.x - move->from.x);
  int shiftY = abs(move->to.y - move->from.y);
  if(shiftX <= 1 || shiftY <= 1) return true;
  return false;
}