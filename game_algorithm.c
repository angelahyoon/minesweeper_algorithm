#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// is_valid(c, r, w, h) checks if the square with the 
//     coordinates ([c]olumn, [r]ow) is a valid point in
//     the grid.
bool is_valid(int c, int r, int w, int h) { 
  return (r >= 0) && (r < h) && \
         (c >= 0) && (c < w);
}


// mine_count(c, r, w, h) counts the number of mines
//     adjacent to the square with the coordinates 
//     ([c]olumn,[r]ow).
int mine_count(const int c, const int r, const int w, const int h) {
  int count = 0;
  
  // Check North Mine
  if (is_valid(c, r - 1, w, h)) {
    if (mine_at(c, r - 1)) {
      count++;
    }
  }
  // Check South Mine
  if (is_valid(c, r + 1, w, h)) {
    if (mine_at(c, r + 1)) {
      count++;
    }
  }
  // Check East Mine
  if (is_valid(c + 1, r, w, h)) {
    if (mine_at(c + 1, r)) {
      count++;
    }
  }
  // Check West Mine
  if (is_valid(c - 1, r, w, h)) {
    if (mine_at(c - 1, r)) {
      count++;
    }
  }
  // Check North-East Mine
  if (is_valid(c + 1, r - 1, w, h)) {
    if (mine_at(c + 1, r - 1)) {
      count++;
    }
  }
  // Check North-West Mine
  if (is_valid(c - 1, r - 1, w, h)) {
    if (mine_at(c - 1, r - 1)) {
      count++;
    }
  }
  // Check South-East Mine
  if (is_valid(c + 1, r + 1, w, h)) {
    if (mine_at(c + 1, r + 1)) {
      count++;
    }
  }
  // Check South-West Mine
  if (is_valid(c - 1, r + 1, w, h)) {
    if (mine_at(c - 1, r + 1)) {
      count++;
    }
  }
  return count;
}

// see game_client.h
bool step(const int c, const int r, const int width, const int height) {
  int i = (r * width) + c;
  bool mine = mine_at(c, r);
  
  if (mine) {
    player_board[i] = MINE;
    return true;
  } else {
    if (player_board[i] == UNKNOWN) {
      player_board[i] = mine_count(c, r, width, height);
    }
    return false;
  }
}

// see game_client.h
bool mark(const int c, const int r, int width, int height) {
  int index = (r * width) + c;
  
  if (player_board[index] == UNKNOWN) {
    player_board[index] = MARKED;
  } else if (player_board[index] == MARKED) {
    player_board[index] = UNKNOWN;
  }
  return board_complete();
}

// see game_client.h
void print(int width, int height) {
  
  for (int r = 0; r <= height ; r++) {
    for (int c = 0; c < width; c++) {
      int i = (r * width) + c;
      
      if (c == width - 1) {
        if (r < height) {
          if (player_board[i] == MINE) {
            printf("X\n");
          } else if (player_board[i] == MARKED) {
            printf("P\n");
          } else if (player_board[i] == UNKNOWN) {
            printf("_\n");
          } else {
            printf("%d\n", player_board[i]);
          }
        } else {
          printf("=\n");
        }
        
      } else {
        if (r < height) {
          if (player_board[i] == MINE) {
            printf("X ");
          } else if (player_board[i] == MARKED) {
            printf("P ");
          } else if (player_board[i] == UNKNOWN) {
            printf("_ ");
          } else {
            printf("%d ", player_board[i]);
          }
        } else {
          printf("==");
        }
      }
    }
  }
}

// see game_client.h
bool step_adv(const int c, const int r, const int width, const int height) {
  int i = (r * width) + c;
  bool mine = mine_at(c, r);
  bool check = is_valid(c, r, width, height);
  
  if (mine) {
    player_board[i] = MINE;
    return true;
    
  } else {
    if (player_board[i] == UNKNOWN) {
      player_board[i] = mine_count(c, r, width, height);
      
      if (player_board[i] == 0) {
        
        check = is_valid(c, r - 1, width, height);
        if (check) {
          step_adv(c, r - 1, width, height);
        }
        check = is_valid(c, r + 1, width, height);
        if (check) {
          step_adv(c, r + 1, width, height);
        }
        check = is_valid(c + 1, r, width, height);
        if (check) {
          step_adv(c + 1, r, width, height);
        }
        check = is_valid(c - 1, r, width, height);
        if (check) {
          step_adv(c - 1, r, width, height);
        }
        check = is_valid(c + 1, r - 1, width, height);
        if (check) {
          step_adv(c + 1, r - 1, width, height);
        }
        check = is_valid(c - 1, r - 1, width, height);
        if (check) {
          step_adv(c - 1, r - 1, width, height);
        }
        check = is_valid(c + 1, r + 1, width, height);
        if (check) {
          step_adv(c + 1, r + 1, width, height);
        }
        check = is_valid(c - 1, r + 1, width, height);
        if (check) {
          step_adv(c - 1, r + 1, width, height);
        }
      }
    }
    return false;
  }
}
