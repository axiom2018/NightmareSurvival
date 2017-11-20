// Definitions.h
#pragma once

// Put all definitions in one universal place for access.

// Id's.
#define PISTOL_ID 0
#define SHOTGUN_ID 1
#define ROCKET_LAUNCHER_ID 2
#define FIRSTAID_ID 3
#define ARMOR_ID 4
#define AMMUNITION_ID 5

// Upgrades.
#define FIRST_AID_UPGRADE 25
#define ARMOR_UPGRADE 20
#define AMMO_UPGRADE 20

// Bullets.
#define PISTOL_BULLET 0
#define SHOTGUN_BULLET 1
#define ROCKET 2
#define PISTOL_BULLET_DAMAGE 2
#define SHOTGUN_BULLET_DAMAGE 10
#define ROCKET_DAMAGE 30

// Enemies.
#define SKELETON_DAMAGE 5
#define VAMPIRE_DAMAGE 10
#define DEMON_DAMAGE 15
#define BOSS_DAMAGE 20

#define SKELETON_SPEED 3
#define VAMPIRE_SPEED 1
#define DEMON_SPEED 2
#define BOSS_SPEED 1

#define SKELETON_HEALTH 2
#define VAMPIRE_HEALTH 6
#define DEMON_HEALTH 15
#define BOSS_HEALTH 35

#define SKELETON_REWARD_LOW 30
#define SKELETON_REWARD_HIGH 90
#define VAMPIRE_REWARD_LOW 60
#define VAMPIRE_REWARD_HIGH 110
#define DEMON_REWARD_LOW 80
#define DEMON_REWARD_HIGH 150
#define BOSS_REWARD_LOW 100
#define BOSS_REWARD_HIGH 200

#define MAX_ENEMIES_PER_WAVE 5

// Etc.
#define COLUMNS 35
#define ROWS 20
#define MAX_ENEMIES 3
#define PLAYER_HEALTH 80
#define MAX_POSITION_TESTS 3
#define MAX_PREREQ_TESTS 2
#define HIGH_AND_LOW_MAX 3
#define MAX_EMPTY_REQUESTS 25
#define UNIVERSAL_UPGRADE_PRICE 100