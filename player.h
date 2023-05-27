#ifndef EXPLORER_PLAYER
#define EXPLORER_PLAYER

#include "splashkit.h"
#include "my_types.h"
#include <vector>

using namespace std;

#define SCREEN_BORDER 100

player new_player();

void draw_player(const player &player);

void update_player(player &player, const game &game);

void handle_input(player &player, bullet &bullet);

void draw_hud(player player);

#endif