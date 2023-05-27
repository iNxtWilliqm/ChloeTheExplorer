#ifndef MY_TYPES
#define MY_TYPES

#include "splashkit.h"
#include <vector>

using namespace std;

struct bullet {
    double x, y;
    bool is_shot;
    sprite bullet_sprite;
};

struct player {
	double x, y;
	double y_velocity;
	bool on_ground;
	int health;
    int kill;
    int coin;
    int ammo;
    int level;
    int xp;
    vector<bullet> bullets;
	sprite player_sprite;
};

enum loot_type {
    BULLET,
    COIN,
    HEART,
    XP
};

struct loot {
    sprite loot_sprite;
    loot_type type;
};

enum monster_type {
	PIG,
	PIG_INVERT
};

struct monster {
	double x, y;
	double y_velocity;
	bool on_ground;
    int health;
	sprite monster_sprite;
	monster_type type;
};

struct game {
    int number;
    bool is_run;
    vector<monster> monsters;
    vector<loot> loots;
};

#endif