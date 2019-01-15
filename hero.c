/***********************************************************************
 * @file    character.c
 * @author  Alex Cameron Miller, William Read Scott
 * @date    14 September 2015
 * @brief   Initializes and hosts character structures
 **********************************************************************/

#include "hero.h"
#include "attack.h"
#include "text.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Define Hero Stats Below
const Stats WIZARD_STATS = {100,  // HP
                            150,  // Attack
                            130,  // Defense
                            160}; // Speed

const Stats KNIGHT_STATS = {150,  // HP
                            130,  // Attack
                            180,  // Defense
                            140}; // Speed

const Stats MONK_STATS = {110,  // HP
                          170,  // Attack
                          150,  // Defense
                          150}; // Speed

const Stats NONE_STATS = {0,  // HP
                          0,  // Attack
                          0,  // Defense
                          0}; // Speed

// "Clear" Stat Bonuses; these are modified in-game with Buffs and Debuffs
const StatBonuses CLEAR_STAT_BONUSES = {0,  // Attack Bonus
                                        0,  // Defense Bonus
                                        0}; // Speed Bonus

// Creates an instance of a hero
Hero generateHero(HeroType hero_type, char* name, Stats max_stats,
                  AttackSet attacks) {
    Hero hero;

    // Initialize Hero
    hero.hero_type = hero_type;
    hero.max_stats = max_stats;
    hero.current_stats = max_stats;
    hero.stat_bonuses = CLEAR_STAT_BONUSES;
    hero.attacks = attacks;
    hero.status = NORMAL;
    hero.substitute = 0;
    hero.protect_b = 0;
    return hero;
}

// Create Heroes
Hero createHero(HeroType hero_type) {
    if (hero_type == HERO_WIZARD) {
        return createWizard();
    }
    else if (hero_type == HERO_KNIGHT) {
        return createKnight();
    }
    else if (hero_type == HERO_MONK) {
        return createMonk();
    }
    else {
        // We have no idea what they are, thus they'll be NOTHING
        return createNone();
    }
}

Hero createWizard() {
    AttackSet attacks = {ATTACK_FIREBALL, ATTACK_SUBSTITUTE, ATTACK_CURE,
                         ATTACK_SPELL_BARRAGE};
    return generateHero(HERO_WIZARD, HERO_WIZARD_NAME, WIZARD_STATS, attacks);
}

Hero createMonk() {
    AttackSet attacks = {ATTACK_STRIKE, ATTACK_PROTECT, ATTACK_MEDITATE,
                         ATTACK_BERSERK};
    return generateHero(HERO_MONK, HERO_MONK_NAME, MONK_STATS, attacks);
}

Hero createKnight() {
    AttackSet attacks = {ATTACK_STOMP, ATTACK_IRONCLAD, ATTACK_PRIDWEN,
                         ATTACK_EXCALIBUR};
    return generateHero(HERO_KNIGHT, HERO_KNIGHT_NAME, KNIGHT_STATS, attacks);
}
/* Function: createNone
 *
 * Creates blank Hero for error catching.
 *
 */
Hero createNone() {
    AttackSet attacks = {ATTACK_NONE, ATTACK_NONE, ATTACK_NONE, ATTACK_NONE};
    return generateHero(HERO_NONE, HERO_NONE_NAME, NONE_STATS, attacks);

}