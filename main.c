#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "game_client.h"
#include "cs136-trace.h"

void process_error(char *msg) {
  printf("%s", msg);
  game_end();
  exit(EXIT_FAILURE);
}

bool process_loop(bool (*func)(int, int, int, int), int width, int height) {
  int col = INT_MIN, row = INT_MIN;
  if (scanf("%d%d", &col, &row) != 2) {
    process_error("Invalid board coordinates.\n");
  }
  bool game_over = func(col, row, width, height);
  print(width, height);
  return game_over;
}

//==============================================================================
// GAME CONTROLS
//------------------------------------------------------------------------------
//   I width height       Starts the game using a random board of size
//                        (width,height) (both of type int).
//   D width height seed  Starts the game using a pre-defined board of size
//                        (width,height) (both oftype int). Using the same seed
//                        (of type int) will result in the same board.
//   S col row            Steps on the square with the coordinates (col,row)
//                        (both of type int).
//   A col row            Steps on the square with the coordinates (col,row)
//                        (both of type int). This is the advanced version of
//                        the standard step above.
//   M col row            Toggles the mark for the square with the coordinates
//                        (col,row) (both of type int).
//   Q                    Quits the game.
//==============================================================================

int main(void) {

    // UNKNOWN represents a square that the player has neither marked nor stepped on
    const int UNKNOWN;

    // MARKED represents a square that the player has marked
    const int MARKED;

    // MINE represents a square that contains a mine
    const int MINE;

  const int CMD_INIT = lookup_symbol("I");
  const int CMD_INITS = lookup_symbol("D");
  const int CMD_STEP = lookup_symbol("S");
  const int CMD_STEPADV = lookup_symbol("A");
  const int CMD_MARK = lookup_symbol("M");
  const int CMD_QUIT = lookup_symbol("Q");

  int width = 0, height = 0;
  bool game_over = false;

  int cmd = read_symbol();
  while (cmd != INVALID_SYMBOL && game_over == false) {
    if (cmd == CMD_INIT || cmd == CMD_INITS) {
      if (scanf("%d%d", &width, &height) != 2)  {
        process_error("Invalid board dimensions.\n");
      }
      if (cmd == CMD_INIT) {
        game_start(width, height);
      } else /* if (cmd == CMD_INITS) */ {
        int seed = 0;
        if (scanf("%d", &seed) != 1) {
          process_error("Invalid seed.\n");
        }
        game_start_seed(width, height, seed);
      }
      print(width, height);
    } else if (cmd == CMD_STEP) {
      game_over = process_loop(step, width, height);
      if (game_over) {
        printf("You stepped on a mine. Game over!\n");
      }
    } else if (cmd == CMD_STEPADV) {
      game_over = process_loop(step_adv, width, height);
      if (game_over) {
        printf("You stepped on a mine. Game over!\n");
      }
    } else if (cmd == CMD_MARK) {
      game_over = process_loop(mark, width, height);
      if (game_over) {
        printf("You marked all mines. Congratulations, well done!\n");
      }
    } else if (cmd == CMD_QUIT) {
      printf("Thanks for playing. See you soon!\n");
      game_over = true;
    } else {
      process_error("Invalid command.\n");
    }

    cmd = read_symbol();
  }

  game_end();

  return EXIT_SUCCESS;
}