enum colors{
  NONE,
  WHITE,
  BLACK
};

enum pieces_types{
  KING,
  QUEEN,
  ROOK,
  BISHOP,
  KNIGHT,
  PAWN
};

struct piece {
  enum colors color;
  enum pieces_types type;
};

char* get_piece_icon(struct piece* piece){
  if(piece->color == WHITE){
    switch(piece->type){
      case KING:
        return "♚";
      case QUEEN:
        return "♛";
      case ROOK:
        return "♜";
      case BISHOP:
        return "♝";
      case KNIGHT:
        return "♞";
      case PAWN:
        return "♟";
    }
  }else if(piece->color == BLACK){
    switch(piece->type){
      case KING:
        return "♔";
      case QUEEN:
        return "♕";
      case ROOK:
        return "♖";
      case BISHOP:
        return "♗";
      case KNIGHT:
        return "♘";
      case PAWN:
        return "♙";
    }
  }
  return " ";
}