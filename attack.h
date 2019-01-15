#ifndef ASSIGNMENT_ATTACK_H
#define ASSIGNMENT_ATTACK_H

#include "text.h"
#include <stdint.h>
#include "rpgbattle_utils.h"

// Forward Declarations
#ifndef _HEROSTRUCT
#define _HEROSTRUCT
typedef struct hero_s Hero;
#endif

#ifndef _GAMESTRUCT
#define _GAMESTRUCT
typedef struct game Game;
#endif

// Attack Base Powers
// Wizard attack set
#define ATTACK_FIREBALL_BASEPOWER 20
#define ATTACK_FIREBALL_CRITICAL 45

#define ATTACK_SUBSTITUTE_BASEPOWER 100
#define ATTACK_SUBSTITUTE_CRITICAL 100

#define ATTACK_CURE_BASEPOWER 20
#define ATTACK_CURE_CRITICAL 30

#define ATTACK_SPELL_BARRAGE_BASEPOWER 10
#define ATTACK_SPELL_BARRAGE_CRITICAL 15

// Knight attack set
#define ATTACK_STOMP_BASEPOWER 25
#define ATTACK_STOMP_CRITICAL 5

#define ATTACK_IRONCLAD_BASEPOWER 100
#define ATTACK_IRONCLAD_CRITICAL 100

#define ATTACK_PRIDWEN_BASEPOWER 30
#define ATTACK_PRIDWEN_CRITICAL 95

#define ATTACK_EXCALIBUR_BASEPOWER 25
#define ATTACK_EXCALIBUR_CRITICAL 5

// Monk attack set
#define ATTACK_STRIKE_BASEPOWER 30
#define ATTACK_STRIKE_CRITICAL 10

#define ATTACK_PROTECT_BASEPOWER 100
#define ATTACK_PROTECT_CRITICAL 100

#define ATTACK_MEDITATE_BASEPOWER 15
#define ATTACK_MEDITATE_CRITICAL 45

#define ATTACK_BERSERK_BASEPOWER 15
#define ATTACK_BERSERK_CRITICAL 35

// MISC Attack Defines
#define ATTACK_DATA_SIZE 4
#define ATTACK_DATA_LOOP_SIZE 3

typedef enum {A_NONE,
              A_FIREBALL,
              A_SUBSTITUTE,
              A_CURE,
              A_SPELL_BARRAGE,
              A_STRIKE,
              A_PROTECT,
              A_MEDITATE,
              A_BERSERK,
              A_STOMP,
              A_IRONCLAD,
              A_PRIDWEN,
              A_EXCALIBUR} Attack;

typedef enum {SELF, ENEMY, ALL} Target;

typedef struct attack_s AttackDetails;
struct attack_s {
    Attack attack;
    Target target;
    uint8_t basePower;
    uint8_t critChance;
};

// This could be an array but passing arrays is a nightmare so using a struct
typedef struct attacks_s AttackSet;
struct attacks_s {
    AttackDetails attack_1;
    AttackDetails attack_2;
    AttackDetails attack_3;
    AttackDetails attack_4;
};

// Execute the attack based on the sent Attack enum
void constructAttack(Game *game);
void executeAttack(Hero* attackingHero, Hero* defendingHero);
uint8_t calcCrit(Attack attack);
uint8_t calcHits(Attack attack);
uint8_t determineAttackPriority(Attack attack);

// Wizard Attack Functions
void attackFireball(Hero* attackingHero, Hero* defendingHero);
void attackSubstitute(Hero* attackingHero, Hero* defendingHero);
void attackCure(Hero* attackingHero);
void attackSpellBarrage(Hero* attackingHero, Hero* defendingHero);

// Monk Attack Functions
void attackStrike(Hero* attackingHero, Hero* defendingHero);
void attackProtect(Hero* attackingHero, Hero* defendingHero);
void attackMeditate(Hero* attackingHero);
void attackBerserk(Hero* attackingHero, Hero* defendingHero);

// Knight Attack Functions
void attackStomp(Hero* attackingHero, Hero* defendingHero);
void attackIronclad(Hero* attackingHero, Hero* defendingHero);
void attackPridwen(Hero* attackingHero);
void attackExcalibur(Hero* attackingHero, Hero* defendingHero);

// Wizard AttackDetails
extern const AttackDetails ATTACK_FIREBALL;
extern const AttackDetails ATTACK_SUBSTITUTE;
extern const AttackDetails ATTACK_CURE;
extern const AttackDetails ATTACK_SPELL_BARRAGE;

// Monk AttackDetails
extern const AttackDetails ATTACK_STRIKE;
extern const AttackDetails ATTACK_PROTECT;
extern const AttackDetails ATTACK_MEDITATE;
extern const AttackDetails ATTACK_BERSERK;

// Knight AttackDetails
extern const AttackDetails ATTACK_STOMP;
extern const AttackDetails ATTACK_IRONCLAD;
extern const AttackDetails ATTACK_PRIDWEN;
extern const AttackDetails ATTACK_EXCALIBUR;

// None AttackDetails
extern const AttackDetails ATTACK_NONE;

#endif // ASSIGNMENT_ATTACK_H