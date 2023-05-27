#include "splashkit.h"
#include "player.h"
#include "bullet.h"
#include <cmath>

using namespace std;

player new_player() {
	player player;

	player.player_sprite = create_sprite(bitmap_named("chloe"));

	player.x = 0;
	player.y = screen_height() / 1.5 - sprite_height(player.player_sprite);
	player.on_ground = true;
	player.health = 100;
	player.coin = 0;
	player.ammo = 30;

	sprite_set_x(player.player_sprite, player.x);
	sprite_set_y(player.player_sprite, player.y);

	return player;
}

void draw_player(const player &player) {
	draw_sprite(player.player_sprite);
}

void display_lose() {
	// kill player
	draw_rectangle(COLOR_WHITE, screen_center().x, screen_center().y, screen_center().x+100, screen_center().y+100, option_to_screen());
	draw_text("YOU LOST", COLOR_WHITE, "go3.ttf", 20, screen_center().x, screen_center().y, option_to_screen());
}

bool is_on_ground(const player &player, const game &game) {
    float playerBottomY = sprite_y(player.player_sprite) + sprite_height(player.player_sprite);
    float groundTopY = screen_height() / 1.5;

    return playerBottomY >= groundTopY;
}

void update_player(player &player, const game &game) {
	const float GRAVITY = 0.5;

	update_sprite(player.player_sprite);

	// Test edge of screen boundaries to adjust the camera
	double left_edge = camera_x() + SCREEN_BORDER;
	double right_edge = left_edge + screen_width() - 2 * SCREEN_BORDER;
	double top_edge = camera_y() + SCREEN_BORDER;
	double bottom_edge = top_edge + screen_height();

	// Get the center of the player
	point_2d sprite_center = center_point(player.player_sprite);

	// Test top/bottom of screen
	if (sprite_center.y < top_edge) {
		move_camera_by(0, sprite_center.y - top_edge);
	} else if (sprite_center.y > bottom_edge) {
		move_camera_by(0, sprite_center.y - bottom_edge);
	}

	// Test left/right of screen
	if (sprite_center.x < left_edge) {
		move_camera_by(sprite_center.x - left_edge, 0);
	} else if (sprite_center.x > right_edge) {
		move_camera_by(sprite_center.x - right_edge, 0);
	}

	// Apply gravity
	sprite_set_dy(player.player_sprite, sprite_dy(player.player_sprite) + GRAVITY);

	if (is_on_ground(player, game)) {
		player.on_ground = true;
        sprite_set_dy(player.player_sprite, 0);
    }

	// if (player.health <= 0) {
	// 	draw_rectangle(COLOR_WHITE, 500, 60, 700, 80, option_to_screen());
	// 	draw_text("HEALTH: " + to_string(player.health), COLOR_WHITE, "go3.ttf", 20, 100, 40, option_to_screen());
	// 	display_lose();
	// }

}

void handle_input(player &player, bullet &bullet) {

	const float PLAYER_SPEED = 5.0;
	const float JUMP_FORCE = 10.0;
	const float BULLET_SPEED = 10.0;

	if (key_down(D_KEY)) {
		sprite_set_dx(player.player_sprite, PLAYER_SPEED);
	} else if (key_down(A_KEY)) {
		sprite_set_dx(player.player_sprite, -PLAYER_SPEED);
	} else {
		sprite_set_dx(player.player_sprite, 0);
	}

	if (key_down(SPACE_KEY) && player.on_ground == true) {
		player.on_ground = false;
		sprite_set_dy(player.player_sprite, -JUMP_FORCE);
	}

	if (mouse_clicked(LEFT_BUTTON)) {
		if (player.ammo > 0) {
			bullet = new_bullet(player);

			bullet.is_shot = true;
			player.ammo -= 1;
			
			// Calculate angle between bullet and mouse position
			float rotation = sprite_rotation(bullet.bullet_sprite);
			point_2d mouse_pos = { mouse_position().x + camera_position().x, mouse_position().y + camera_position().y };
			vector_2d angle = vector_from_center_sprite_to_point(bullet.bullet_sprite, mouse_pos);

			// Set bullet's rotation and velocity
			sprite_set_rotation(bullet.bullet_sprite, rotation);
			sprite_set_velocity(bullet.bullet_sprite, angle);
			sprite_set_speed(bullet.bullet_sprite, BULLET_SPEED);
		}
	}

}

void draw_hud(player player) {
	draw_text("HEALTH: " + to_string(player.health), COLOR_WHITE, "go3.ttf", 20, 50, 20, option_to_screen());
	draw_text("KILLS: " + to_string(player.kill), COLOR_WHITE, "go3.ttf", 20, 200, 20, option_to_screen());
	draw_text("COINS: " + to_string(player.coin), COLOR_WHITE, "go3.ttf", 20, 350, 20, option_to_screen());
	draw_text("AMMO: " + to_string(player.ammo), COLOR_WHITE, "go3.ttf", 20, 500, 20, option_to_screen());
	if (player.ammo <= 0) {
		draw_text("Out of Ammo!", COLOR_RED, "go3.ttf", 20, 500, 50, option_to_screen());
	}
}