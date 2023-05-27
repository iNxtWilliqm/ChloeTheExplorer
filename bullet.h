#ifndef EXPLORER_BULLET
#define EXPLORER_BULLET

#include "splashkit.h"
#include "my_types.h"
#include <vector>

using namespace std;

bullet new_bullet(player &player);

void draw_bullet(const player &player);

void update_bullet(player &player);

#endif