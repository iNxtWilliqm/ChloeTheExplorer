#include "splashkit.h"
#include "bullet.h"
#include "math.h"

using namespace std;

bullet new_bullet(player &player) {
	bullet bullet;

	bullet.bullet_sprite = create_sprite(bitmap_named("bullet"));

	sprite_set_x(bullet.bullet_sprite, sprite_x(player.player_sprite));
	sprite_set_y(bullet.bullet_sprite, sprite_y(player.player_sprite) + 25);

	player.bullets.push_back(bullet);

	return bullet;
}

void draw_bullet(const player &player) {
	for (const bullet &bullet : player.bullets) {
		if (bullet.is_shot == false) {
			draw_sprite(bullet.bullet_sprite);
		}
	}
}

void update_bullet(player &player) {
	for (int i = 0; i < player.bullets.size(); i++) {
		bullet &bullet = player.bullets[i];

		update_sprite(bullet.bullet_sprite);

		if (center_point(bullet.bullet_sprite).x < camera_position().x || center_point(bullet.bullet_sprite).y < camera_position().y) {
			player.bullets[i] = player.bullets.back();
			player.bullets.pop_back();
		}
	}
}