#include "splashkit.h"
#include "player.h"
#include "monster.h"
#include "loot.h"
#include "game.h"
#include "bullet.h"

using namespace std;

void load_resources() {
	load_resource_bundle("game_bundle", "chloe_the_explorer.txt");
}

int main() {
    open_window("Chloe The Explorer", 1000, 500);
    load_resources();

    game game;
    player player;
    bullet bullet;
    monster monster;

    player = new_player();

    bool game_over = false; // Add a flag to track game over state

    while (!quit_requested()) {
        process_events();
        
        if (!game_over) {
            // Handle input to adjust player movement
            handle_input(player, bullet);

            clear_screen();

            // Player mechanics and camera movement
            update_player(player, game);

            // Monster mechanics
            update_monster(game, player);

            // Bullet mechanics
            update_bullet(player);

            // Loot mechanics
            update_loot(player, game);

            load_game(game, player, monster, bullet);

            // Check if game over condition is met
            if (player.health <= 0) {
                game_over = true;
            }
        } else {
            // Restart the game
            if (key_typed(R_KEY)) { 
                game_over = false;
                player = new_player();
                game.monsters.clear();
				player.bullets.clear();
                game.loots.clear();
            }
        }

        refresh_screen(60);
    }

    return 0;
}