#include "splashkit.h"
#include "loot.h"
#include <cmath>

using namespace std;

bitmap loot_bitmap(loot_type type) {
	switch (type) {
		case COIN:
			return bitmap_named("loot_coin");
		case HEART:
			return bitmap_named("loot_heart");
		case XP:
			return bitmap_named("loot_xp");
		default:
			return bitmap_named("loot_bullet");
	}
}

loot new_loot(float x) {
	loot loot;

	loot.type = static_cast<loot_type>(rnd(0, 4));

	loot.loot_sprite = create_sprite(loot_bitmap(loot.type));

	sprite_set_x(loot.loot_sprite, x);
	sprite_set_y(loot.loot_sprite, screen_height() / 1.5 - sprite_height(loot.loot_sprite));

	return loot;
}

void draw_loot(const game &game) {
	for (const loot &loot : game.loots) {
		draw_sprite(loot.loot_sprite);
	}
}

void update_loot(player &player, game &game) {
	for (int i = 0; i < game.loots.size(); i++) {
		loot &loot = game.loots[i];
		update_sprite(loot.loot_sprite);
		if (sprite_collision(player.player_sprite, loot.loot_sprite)) {
			if (loot.type == BULLET) {
				player.ammo += 30;
				play_sound_effect(sound_effect_named("loot_bullet"));
			} else if (loot.type == COIN) {
				player.coin += 1;
				play_sound_effect(sound_effect_named("loot_coin"));
			} else if (loot.type == HEART) {
				player.health += 10;
				play_sound_effect(sound_effect_named("loot_heart"));
			} else if (loot.type == XP) {
				player.xp += 10;
				play_sound_effect(sound_effect_named("loot_xp"));
			}
			game.loots[i] = game.loots.back();
			game.loots.pop_back();
		}
	}
}