#include "splashkit.h"
#include "player.h"
#include "monster.h"
#include "loot.h"
#include "bullet.h"
#include "game.h"

using namespace std;

void load_game(game &game, player &player, monster &monster, bullet &bullet) {
	draw_background();
	draw_ground(game);
	draw_player(player);
	draw_monster(game);
	draw_loot(game);
	if (bullet.is_shot == true) {
		draw_bullet(player);
	}
	draw_hud(player);
}

void draw_ground(const game &game) {
	fill_rectangle(COLOR_GREEN, 0, screen_height() / 1.5, screen_width(), screen_height(), option_to_screen());
}

void fill_random_circle() {
	int x = rand() % screen_width();    // Generate random x-coordinate
	int y = rand() % screen_height();   // Generate random y-coordinate

	fill_circle(COLOR_YELLOW, x, y, 1, option_to_screen());
}

void draw_background() {
	fill_rectangle(COLOR_DARK_SLATE_BLUE, 0, 0, screen_width(), screen_height() / 1.5, option_to_screen());
	// Adding noises textures to background
	for (int i = 0; i < 5; i++) {
		fill_random_circle();   
	}
}