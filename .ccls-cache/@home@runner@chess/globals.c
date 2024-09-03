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