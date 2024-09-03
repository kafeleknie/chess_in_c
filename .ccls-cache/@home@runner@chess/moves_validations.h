#ifndef MOVES_VALIDATIONS_H
#define MOVES_VALIDATIONS_H

struct move;
struct piece* get_piece(struct position*);
enum colors get_piece_color(struct position*);

bool validate_move(struct move*);
bool obstacle_check(struct move*);
bool validate_king_move(struct move*,enum colors);
bool validate_queen_move(struct move*,enum colors);
bool validate_rook_move(struct move*,enum colors);
bool validate_bishop_move(struct move*,enum colors);
bool validate_knight_move(struct move*,enum colors);
bool validate_pawn_move(struct move*,enum colors);

bool validate_move( struct move* move){
  if(move->to.x < 0 || move->to.x > 7 || move->to.y < 0 || move->to.y > 7) return false;
  struct piece* piece = get_piece(&move->from);
  if(obstacle_check(move)) return false;
  switch(piece->type){
    case KING:
      return validate_king_move(move,piece->color);
    case QUEEN:
      return validate_queen_move(move,piece->color);
    case ROOK:
      return validate_rook_move(move,piece->color);
    case BISHOP:
      return validate_bishop_move(move,piece->color);
    case KNIGHT:
      return validate_knight_move(move,piece->color);
    case PAWN:
      return validate_pawn_move(move,piece->color);
  }
  return false;
}

bool obstacle_check(struct move* move){
  struct position current_position = move->from;
  int shiftX = abs(move->to.x - move->from.x);
  int shiftY = abs(move->to.y - move->from.y);
  int directionX = shiftX == 0 ? 0 : (move->to.x - move->from.x) / shiftX;
  int directionY = shiftY == 0 ? 0 : (move->to.y - move->from.y) / shiftY;
  for(int i = 1; i < (shiftX == 0 ? shiftY : shiftX); i++){
    current_position.x += directionX;
    current_position.y += directionY;
    if(get_piece_color(&current_position) != NONE) return true;
  }
  return false;
}

bool validate_king_move(struct move* move ,enum colors color){
  int shiftX = abs(move->to.x - move->from.x);
  int shiftY = abs(move->to.y - move->from.y);
  if(shiftX <= 1 || shiftY <= 1) return true;
  return false;
}

bool validate_queen_move(struct move* move ,enum colors color){
  if(validate_rook_move(move,color) || validate_bishop_move(move,color)) return true;
  return false;
}

bool validate_rook_move(struct move* move , enum colors color){
  int shiftX = abs(move->to.x - move->from.x);
  int shiftY = abs(move->to.y - move->from.y);
  if(shiftX == 0 || shiftY == 0) return true;
  return false;
}

bool validate_bishop_move(struct move* move , enum colors color){
  int shiftX = abs(move->to.x - move->from.x);
  int shiftY = abs(move->to.y - move->from.y);
  if( shiftX == shiftY) return true;
  return false;
}

bool validate_knight_move(struct move* move , enum colors color){
  int shiftX = abs(move->to.x - move->from.x);
  int shiftY = abs(move->to.y - move->from.y);

  if(abs(shiftX - shiftY) == 1) return true;
  return false;
}

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

#endif