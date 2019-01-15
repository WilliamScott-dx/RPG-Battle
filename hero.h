/***********************************************************************
 * @file    character.h
 * @author  Alex Cameron Miller, William Read Scott
 * @date    14 September 2015
 **********************************************************************/

#ifndef ASSIGNMENT_HERO_H
#define ASSIGNMENT_HERO_H

#include "system.h"
#include "attack.h"

#define NUM_HEROES 4

// enum for status types
typedef enum {NORMAL, BURNED} Status;
typedef enum {HERO_NONE, HERO_WIZARD, HERO_MONK, HERO_KNIGHT} HeroType;  // Update NUM_HEROES when added to

// Struct for storing player stats.
typedef struct stats_s Stats;
struct stats_s {
    uint8_t hp;
    uint8_t attack;
    uint8_t defense;
    uint8_t speed;
};

// Struct for storing player stats.
typedef struct statBonuses_s StatBonuses;
struct statBonuses_s {
    uint8_t attackBonus;
    uint8_t defenseBonus;
    uint8_t speedBonus;
};

// Struct for storing the players character
#define _HEROSTRUCT
typedef struct hero_s Hero;
struct hero_s {
    HeroType hero_type;
    Stats max_stats;
    Stats current_stats;
    StatBonuses stat_bonuses;
    AttackSet attacks;
    Status status;
    uint8_t substitute;
    uint8_t protect_b;
    uint8_t attackData[ATTACK_DATA_SIZE];
};

// Create Heroes
Hero createHero(HeroType hero_type);
Hero generateHero(HeroType hero_type, char *name, Stats max_stats,
                  AttackSet attacks);
Hero createWizard(void);
Hero createKnight(void);
Hero createMonk(void);
Hero createNone(void);

// Hero Stats
extern const Stats WIZARD_STATS;
extern const Stats KNIGHT_STATS;
extern const Stats MONK_STATS;
extern const Stats NONE_STATS;

// Stat Bonuses
extern const StatBonuses CLEAR_STAT_BONUSES;

#endif // ASSIGNMENT_HERO_H