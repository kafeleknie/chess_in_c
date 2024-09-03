#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <string.h> 
#include "types.h"

#define RESET_COLOR "\033[0m"
#define LIGHT_BG "\033[48;5;250m" 
#define DARK_BG "\033[48;5;15m"
#define DARK_TEXT "\033[38;5;8m"


struct piece board[8][8];
void initialize_board(struct piece board[8][8]);
void draw_board();

char* get_piece_icon(struct piece*);
struct piece* get_piece(struct position*);
enum colors get_piece_color(struct position*);
void move_piece(struct move*,struct position*,struct position*);

enum move_status validate_move(struct move*);
bool obstacle_check(struct move*);
enum move_status validate_king_move(struct move*,enum colors);
enum move_status validate_queen_move(struct move*,enum colors);
enum move_status validate_rook_move(struct move*,enum colors);
enum move_status validate_bishop_move(struct move*,enum colors);
enum move_status validate_knight_move(struct move*,enum colors);
enum move_status validate_pawn_move(struct move*,enum colors);

char* get_user_input();
void convert_input_to_move(char*, struct move*);
void convert_input_to_position(char*,struct position*);

bool game();

int main(void) {
  game();
}

bool game(){
  initialize_board(board);
  int turn = 1;
  enum colors curent_player = WHITE;
  struct position white_king_position = {7,4};
  struct position black_king_position = {0,4};
  while(true){
    draw_board();
    struct move move = {{0,0},{0,1}};
    char* user_input = get_user_input();
    convert_input_to_move(user_input,&move);
    // printf("fromX%i\n",move.from.x);
    // printf("fromY%i\n",move.from.y);
    // printf("toX%i\n",move.to.x);
    // printf("toY%i\n\n",move.to.y);
    
    if(validate_move(&move) == VALID){
      move_piece(&move,&white_king_position,&black_king_position);
      curent_player = (curent_player == WHITE) ? BLACK : WHITE;
    }
  }
  return true;
}

void initialize_board(struct piece board[8][8]) {
    board[0][0] = (struct piece){BLACK, ROOK};
    board[0][1] = (struct piece){BLACK, KNIGHT};
    board[0][2] = (struct piece){BLACK, BISHOP};
    board[0][3] = (struct piece){BLACK, QUEEN};
    board[0][4] = (struct piece){BLACK, KING};
    board[0][5] = (struct piece){BLACK, BISHOP};
    board[0][6] = (struct piece){BLACK, KNIGHT};
    board[0][7] = (struct piece){BLACK, ROOK};

    for (int x = 0; x < 8; x++) {
        board[1][x] = (struct piece){BLACK, PAWN};
    }

    for (int x = 2; x < 6; x++) {
        for (int y = 0; y < 8; y++) {
            board[x][y] = (struct piece){NONE};
        }
    }

    for (int i = 0; i < 8; i++) {
        board[6][i] = (struct piece){WHITE, PAWN};
    }

    board[7][0] = (struct piece){WHITE, ROOK};
    board[7][1] = (struct piece){WHITE, KNIGHT};
    board[7][2] = (struct piece){WHITE, BISHOP};
    board[7][3] = (struct piece){WHITE, QUEEN};
    board[7][4] = (struct piece){WHITE, KING};
    board[7][5] = (struct piece){WHITE, BISHOP};
    board[7][6] = (struct piece){WHITE, KNIGHT};
    board[7][7] = (struct piece){WHITE, ROOK};
}

//move validation
void move_piece(struct move* move , struct position* white_king_position,struct position* black_king_position){
  struct piece blank_space = {NONE};
  board[move->to.y][move->to.x] = board[move->from.y][move->from.x];
  board[move->from.y][move->from.x] = blank_space;
}

enum move_status validate_move( struct move* move){
  if(move->to.x < 0 || move->to.x > 7 || move->to.y < 0 || move->to.y > 7) return OUT_OF_BONDS;
  if(move->from.x == move->to.x && move->from.y == move->to.y) return OCCUPIED;
  
  struct piece* piece = get_piece(&move->from);
  
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

enum move_status validate_king_move(struct move* move ,enum colors color){
  int shiftX = abs(move->to.x - move->from.x);
  int shiftY = abs(move->to.y - move->from.y);
  if(shiftX <= 1 && shiftY <= 1) return VALID;
  return INVALID;
}

enum move_status validate_queen_move(struct move* move ,enum colors color){
  if(validate_rook_move(move,color) == VALID || validate_bishop_move(move,color) == VALID) return VALID;
  return INVALID;
}

enum move_status validate_rook_move(struct move* move , enum colors color){
  if(obstacle_check(move)) return OBSTACLE;
  int shiftX = abs(move->to.x - move->from.x);
  int shiftY = abs(move->to.y - move->from.y);
  if(shiftX == 0 || shiftY == 0) return VALID;
  return INVALID;
}

enum move_status validate_bishop_move(struct move* move , enum colors color){
  if(obstacle_check(move)) return OBSTACLE;
  int shiftX = abs(move->to.x - move->from.x);
  int shiftY = abs(move->to.y - move->from.y);
  if( shiftX == shiftY) return VALID;
  return INVALID;
}

enum move_status validate_knight_move(struct move* move , enum colors color){
  int shiftX = abs(move->to.x - move->from.x);
  int shiftY = abs(move->to.y - move->from.y);

  if(abs(shiftX - shiftY) == 1) return VALID;
  return INVALID;
}

enum move_status validate_pawn_move(struct move* move , enum colors color){
  if(obstacle_check(move)) return OBSTACLE;
  if(move->to.y > move->from.y && color == WHITE) return INVALID;
  if(move->to.y < move->from.y && color == BLACK) return INVALID;

  int shiftX = abs(move->to.x - move->from.x);
  int shiftY = abs(move->to.y - move->from.y);

  if(shiftX == 0){
    if(shiftY == 1) return VALID;
    if(shiftY == 2 && ( move->from.y == 1 || move->from.y == 6)) return VALID;
  }
  return INVALID;
}

//user input staff
char* get_user_input(){
  char input[5];
  scanf("%s",input);
  char *input_copy = malloc(sizeof(char) * 5); 
  strcpy(input_copy, input);
  return input_copy;
}

void convert_input_to_move(char* input , struct move* move){
  move->from = (struct position){abs(8 - (int)(input[1] - '0')),input[0] - 97};
  move->to = (struct position){abs(8 - (int)(input[3] - '0')),input[2] - 97};
}

void convert_input_to_position(char* input , struct position* position){
  position->y = 8 - (input[1] - '0');
  position->x = input[0] - 97;
}

char* get_piece_icon(struct piece* piece){
  if(piece->color == WHITE){
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
  }else if(piece->color == BLACK){
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
  }
  return " ";
}

void draw_board(){
  char* numbers_emojis[8]= {"１","２","３","４","５","６","７","８"};
  system("clear");
  printf("%s\n","  ＡＢＣＤＥＦＧＨ");
  for(int Y = 0; Y < 8; Y++){
    for(int X = 0; X < 8; X++){
      if(X==0) printf("%s",numbers_emojis[8 - (Y + 1)]);
      
      if((Y + X) % 2 == 0) {
        printf("%s", LIGHT_BG);
      } else {
        printf("%s", DARK_BG);
      }
      
      printf("%s ", get_piece_icon(&board[Y][X]));
      printf("%s",RESET_COLOR);
      
      if(X==7) printf("%s",numbers_emojis[8 - (Y + 1)]);
    }
    printf("\n");
  }
  printf("%s\n","  ＡＢＣＤＥＦＧＨ");
}



struct piece* get_piece(struct position* position){
  return &board[position->y][position->x];
}

enum colors get_piece_color(struct position* position){
  return board[position->y][position->x].color;
}