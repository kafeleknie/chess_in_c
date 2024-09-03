#ifndef TYPES_H
#define TYPES_H

enum colors { NONE, WHITE, BLACK };

enum pieces_types { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };

struct piece {
  enum colors color;
  enum pieces_types type;
};

struct position {
  int y;
  int x;
};

struct move {
  struct position from;
  struct position to;
};

#endif