#ifndef _UTILS_H
#define _UTILS_H
#include "player.h"
#include "board.h"
#include "game.h"
#include "menu.h"
#include "point.h"
#include "shape.h"

constexpr char HASHTAG = 35;

bool isValidCellV2(Shape& curr_shape, Board& board, Input direction);
bool isStuckV2(Shape& curr_shape, Board& board);

bool isValidCell(Shape& curr_shape, Board& board, Input direction);
bool isStuck(Shape& curr_shape, Board& board);
bool isColliding(Shape& curr_shape, Board& board);
void gotoxy(int x, int y);
void hideCursor();
void clear_screen();
void sleep(double seconds);
char getKeyboardHit();
Input playerInput(char input, Player*& p1, Player*& p2);
void KbHit(Player*& p1, Player*& p2, Board& board_p1, Board& board_p2, Shape& shape_p1, Shape& shape_p2, Menu& menu, Game& game);

#endif //_UTILS_H