#ifndef EXPLORER_LOOT
#define EXPLORER_LOOT

#include "splashkit.h"
#include "my_types.h"
#include <vector>

using namespace std;

loot new_loot(float x);

void draw_loot(const game &game);

void update_loot(player &player, game &game);

#endif