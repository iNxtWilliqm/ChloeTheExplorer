#include "splashkit.h"
#include "monster.h"
#include "loot.h"
#include <cmath>

using namespace std;

bitmap monster_bitmap(monster_type type) {
	switch (type) {
		case PIG_INVERT:
			return bitmap_named("pig_invert");
		default:
			return bitmap_named("pig");
	}
}

monster new_monster(game &game) {
	
	monster monster;
	
	bitmap default_bitmap = monster_bitmap(PIG);

	monster.monster_sprite = create_sprite(default_bitmap);

	int monster_direction = rnd(0, 2);
	switch (monster_direction) {
		case 1:
			monster_direction = screen_width() + camera_x();
			break;
		default:
			monster_direction = camera_x();
	}

	monster.type = PIG;
	monster.x = monster_direction;
	monster.y = screen_height() / 1.5 - sprite_height(monster.monster_sprite);
	monster.health = 3;

	sprite_set_x(monster.monster_sprite, monster.x);
	sprite_set_y(monster.monster_sprite, monster.y);

	sprite_add_layer(monster.monster_sprite, monster_bitmap(PIG_INVERT), "pig_invert");

	return monster;
}

void draw_monster(const game &game) {
	for (const monster &monster : game.monsters) {
		draw_sprite(monster.monster_sprite);
	}
}

void update_monster(game &game, player &player) {

	const float MONSTER_SPEED = 2.0;

	for (int i = 0; i < game.monsters.size(); i++) {
		monster &monster = game.monsters[i];

		update_sprite(monster.monster_sprite);

		// Check if the monster collides with the player
		if (sprite_collision(monster.monster_sprite, player.player_sprite)) {
			if (player.health >= 0) {
				player.health -= 1;
			}
			// TODO: PLAY SOUND
		} else {
			if (sprite_x(monster.monster_sprite) < sprite_x(player.player_sprite)) {
				sprite_set_dx(monster.monster_sprite, MONSTER_SPEED);
				sprite_hide_layer(monster.monster_sprite, PIG);
				sprite_show_layer(monster.monster_sprite, PIG_INVERT);
			} else if (sprite_x(monster.monster_sprite) > sprite_x(player.player_sprite)) {
				sprite_set_dx(monster.monster_sprite, -MONSTER_SPEED);
				sprite_hide_layer(monster.monster_sprite, PIG_INVERT);
				sprite_show_layer(monster.monster_sprite, PIG);
			}
		}

		for (int j = 0; j < player.bullets.size(); j++) {
			bullet &bullet = player.bullets[j];
			if (sprite_collision(bullet.bullet_sprite, monster.monster_sprite)) {
				monster.health -= 1;
				player.bullets[j] = player.bullets.back();
				player.bullets.pop_back();
				j--; // Decrement j to handle the replaced bullet in the next iteration
			}

			if (!game.monsters.empty()) {
				if (monster.health <= 0) {
					player.kill += 1;
					float death_pos = sprite_x(monster.monster_sprite);

					game.monsters[i] = game.monsters.back();
					game.monsters.pop_back();

					loot loot = new_loot(death_pos);
					game.loots.push_back(loot);

					play_sound_effect(sound_effect_named("pig_dead"));

					break;
				}
			}
		}
	}

	// Spawn new monsters randomly
	switch (player.level) {
		case 0:
			if (rnd(0, 100) < 1) { // 1% chance of spawning a new monster in each update
				if (game.monsters.size() < 2) { // Limit the number of monsters to 2
					monster monster = new_monster(game);
					game.monsters.push_back(monster);
				}
			}
			break;
		case 1:
			if (rnd(0, 100) < 2) { // 2% chance of spawning a new monster in each update
				if (game.monsters.size() < 3) { // Limit the number of monsters to 3
					monster monster = new_monster(game);
					game.monsters.push_back(monster);
				}
			}
			break;
		case 2:
			if (rnd(0, 100) < 3) { // 3% chance of spawning a new monster in each update
				if (game.monsters.size() < 4) { // Limit the number of monsters to 4
					monster monster = new_monster(game);
					game.monsters.push_back(monster);
				}
			}
			break;
		case 3:
			if (rnd(0, 100) < 4) { // 4% chance of spawning a new monster in each update
				if (game.monsters.size() < 5) { // Limit the number of monsters to 5
					monster monster = new_monster(game);
					game.monsters.push_back(monster);
				}
			}
			break;
		case 4:
			if (rnd(0, 100) < 5) { // 5% chance of spawning a new monster in each update
				if (game.monsters.size() < 6) { // Limit the number of monsters to 6
					monster monster = new_monster(game);
					game.monsters.push_back(monster);
				}
			}
			break;
		case 5:
			if (rnd(0, 100) < 5) { // 5% chance of spawning a new monster in each update
				if (game.monsters.size() < 7) { // Limit the number of monsters to 7
					monster monster = new_monster(game);
					game.monsters.push_back(monster);
				}
			}
			break;
		default:
			if (rnd(0, 100) < 5) { // 5% chance of spawning a new monster in each update
				if (game.monsters.size() < 10) { // Limit the number of monsters to 10
					monster monster = new_monster(game);
					game.monsters.push_back(monster);
				}
			}
	}

}