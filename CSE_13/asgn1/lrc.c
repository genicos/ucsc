#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum faciem { LEFT, RIGHT, CENTER, PASS } faces;
faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };

//Names of the characters(people) that will play the game
const char *names[] = { "Dude", "Walter", "Maude", "Big Lebowski", "Brandt",
  "Bunny", "Karl", "Kieffer", "Franz", "Smokey" };

//Main has all pregame adjustments and game loop
int main(void) {
  int32_t seed;
  uint32_t pot, number_of_players, players_in_game;

  printf("Random seed: ");
  scanf("%d", &seed);
  srand(seed);

  number_of_players = 11;
  while (number_of_players < 2 || number_of_players > 10) {
    printf("How many players?: ");
    scanf("%d", &number_of_players);
  }
  
  //All players start with 3$
  uint32_t player_balance[number_of_players];
  for (uint8_t i = 0; i < number_of_players; i++) {
    player_balance[i] = 3;
  }

  players_in_game = number_of_players;
  pot = 0;

  //Game loop runs until a single player is remaining
  while (players_in_game > 1) {
    for (uint8_t i = 0; i < number_of_players && players_in_game > 1; i++) {
      uint32_t this_players_balance = player_balance[i];

      //a player onnly rolls if they have money
      if (this_players_balance != 0) {
        printf("\n%s rolls... ", names[i]);
      }

      //3 or less rolls each turn
      for (uint8_t j = 0; j < this_players_balance && j < 3; j++) {

        switch (die[rand() % 6]) {
        //Curent player loses a dollar and passes it to the left
        case LEFT:
          player_balance[i]--;
          player_balance[(i - 1 + number_of_players) % number_of_players]++;
          //If player to the left was revived from bankrupcy, increment players
          if (player_balance[(i - 1 + number_of_players) % number_of_players]
              == 1) {
            players_in_game++;
          }
          printf("gives $1 to %s ",
              names[(i - 1 + number_of_players) % number_of_players]);
          break;

        //Current player loses a dollar and passes it to the right
        case RIGHT:
          player_balance[i]--;
          player_balance[(i + 1) % number_of_players]++;
          //If player to the right was revived from bankrupcy, increment players
          if (player_balance[(i + 1) % number_of_players] == 1) {
            players_in_game++;
          }
          printf("gives $1 to %s ", names[(i + 1) % number_of_players]);
          break;

        //Current player loses a dollar and passes it to the pot
        case CENTER:
          player_balance[i]--;
          pot++;
          printf("puts $1 in the pot ");
          break;

        case PASS:
          printf("gets a pass ");
          break;
        }
        //If current player is bankrupt, decrement players
        if (player_balance[i] < 1) {
          players_in_game--;
        }
      }
    }
  }

  //Announce winner by finding player who still has money
  for (uint8_t i = 0; i < number_of_players; i++) {
    if (player_balance[i] > 0) {
      printf("\n%s wins the $%d pot with $%d left in the bank!\n", names[i],
          pot, player_balance[i]);
    }
  }
}
