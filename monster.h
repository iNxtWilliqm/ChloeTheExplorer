#ifndef EXPLORER_MONSTER
#define EXPLORER_MONSTER

#include "splashkit.h"
#include "my_types.h"
#include <vector>

using namespace std;

monster new_monster(game &game);

void draw_monster(const game &game);

void update_monster(game &game, player &player);

#endif