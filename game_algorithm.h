#include <stdbool.h>

// step(c, r, width, heigth) returns false if the square with the coordinates
//   ([c]olumn,[r]ow) does not contain a mine or if it has been stepped
//   on before. Otherwise, it returns true.

bool step(const int c, const int r, const int width, const int height);

// step_adv(c, r, width, heigth) returns false if the square with the
//   coordinates ([c]olumn,[r]ow) does not contain a mine or if it has been
//   stepped on before. Otherwise, it returns true.

bool step_adv(const int c, const int r, const int width, const int height);

// mark(col, row, width, heigth) toggles the mark of the square at (col,row).
//   (It markes the square if it is currently not markes, or unmarks it if it
//   is currently marked). The function returns true if all squares with mines
//   are marked and all marked squares contain mines, and false otherwise.

bool mark(const int c, const int r, const int width, const int height);

// print(width, height) prints the current player board. Unexplored squares are
//   represented by '_ ', marked squares by 'P ', and mines by 'X '.

void print(const int width, const int height);