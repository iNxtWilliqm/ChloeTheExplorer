#ifndef EXPLORER_GAME
#define EXPLORER_GAME

#include "splashkit.h"
#include "my_types.h"
#include <vector>

using namespace std;

void load_game(game &game, player &player, monster &monster, bullet &bullet);

void draw_ground(const game &game);

void draw_background();

#endif