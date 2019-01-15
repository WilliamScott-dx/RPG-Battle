#include "attack.h"
#include "text.h"
#include "hero.h"
#include "rpgbattle.h"

// Wizard Attacks
const AttackDetails ATTACK_FIREBALL = {A_FIREBALL, ENEMY,
                                       ATTACK_FIREBALL_BASEPOWER,
                                       ATTACK_FIREBALL_CRITICAL};
const AttackDetails ATTACK_SUBSTITUTE = {A_SUBSTITUTE, SELF,
                                         ATTACK_SUBSTITUTE_BASEPOWER,
                                         ATTACK_SUBSTITUTE_CRITICAL};
const AttackDetails ATTACK_CURE = {A_CURE, SELF,
                                   ATTACK_CURE_BASEPOWER,
                                   ATTACK_CURE_CRITICAL};
const AttackDetails ATTACK_SPELL_BARRAGE = {A_SPELL_BARRAGE, ENEMY,
                                            ATTACK_SPELL_BARRAGE_BASEPOWER,
                                            ATTACK_SPELL_BARRAGE_CRITICAL};

// Knight Attacks
const AttackDetails ATTACK_STOMP = {A_STOMP, ENEMY,
                                    ATTACK_STOMP_BASEPOWER,
                                    ATTACK_STOMP_CRITICAL};
const AttackDetails ATTACK_IRONCLAD = {A_IRONCLAD, SELF,
                                       ATTACK_IRONCLAD_BASEPOWER,
                                       ATTACK_IRONCLAD_CRITICAL};
const AttackDetails ATTACK_PRIDWEN = {A_PRIDWEN, SELF,
                                      ATTACK_PRIDWEN_BASEPOWER,
                                      ATTACK_PRIDWEN_CRITICAL};
const AttackDetails ATTACK_EXCALIBUR = {A_EXCALIBUR, ENEMY,
                                        ATTACK_EXCALIBUR_BASEPOWER,
                                        ATTACK_EXCALIBUR_CRITICAL};

// Monk Attacks
const AttackDetails ATTACK_STRIKE = {A_STRIKE, ENEMY,
                                     ATTACK_STRIKE_BASEPOWER,
                                     ATTACK_STRIKE_CRITICAL};
const AttackDetails ATTACK_PROTECT = {A_PROTECT, SELF,
                                      ATTACK_PROTECT_BASEPOWER,
                                      ATTACK_PROTECT_CRITICAL};
const AttackDetails ATTACK_MEDITATE = {A_MEDITATE, SELF,
                                       ATTACK_MEDITATE_BASEPOWER,
                                       ATTACK_MEDITATE_CRITICAL};
const AttackDetails ATTACK_BERSERK = {A_BERSERK, ENEMY,
                                      ATTACK_BERSERK_BASEPOWER,
                                      ATTACK_BERSERK_CRITICAL};

// None Attacks
const AttackDetails ATTACK_NONE = {A_NONE, SELF, 0};

/* Function: uint8_t calcCrit(Attack attack)
 *
 * Calculates if the attack will be a critical hit or not.
 */
uint8_t calcCrit(Attack attack) {
    if (attack == A_FIREBALL) {
        if (rand_uint8(1, 100) > ATTACK_FIREBALL.critChance) {
            return 1;
        }
        return 0;
    }
    else if (attack == A_SPELL_BARRAGE) {
        if (rand_uint8(1, 100) > ATTACK_SPELL_BARRAGE.critChance) {
            return 1;
        }
        return 0;
    }
    else if (attack == A_STRIKE) {
        if (rand_uint8(1, 100) > ATTACK_STRIKE.critChance) {
            return 1;
        }
        return 0;
    }
    else if (attack == A_BERSERK) {
        if (rand_uint8(1, 100) > ATTACK_BERSERK.critChance) {
            return 1;
        }
        return 0;
    }
    else if (attack == A_STOMP) {
        if (rand_uint8(1, 100) > ATTACK_STOMP.critChance) {
            return 1;
        }
        return 0;
    }
        else if (attack == A_EXCALIBUR) {
        if (rand_uint8(1, 100) > ATTACK_EXCALIBUR.critChance) {
            return 1;
        }
        return 0;
    }
    else { // Attack cannot critical hit
        return 0;
    }
}

/* Function: uint8_t calcHits(Attack attack)
 *
 * Calculates the amount of hits an attack will have on an opponent if the
 * attack being used is one that hits multiple times, otherwise returns
 * 1 for a single hit attack.
 */
uint8_t calcHits(Attack attack) {
    if (attack == A_SPELL_BARRAGE) {
        return rand_uint8(0, 7);
    } else if (attack == A_EXCALIBUR) {
        return rand_uint8(0, 4);
    } else if (attack == A_BERSERK) {
        return rand_uint8(0, 10);
    } else {
        return 1;
    }
};

// TODO: Add actual description
uint8_t determineAttackPriority(Attack attack) {
    if (attack == A_SUBSTITUTE) {
        return 1;
    } else if (attack == A_PROTECT) {
        return 2;
    } else if (attack == A_IRONCLAD) {
        return 3;
    } else {
        return 0;
    }
}


/* Function: constructAttack(Game *game)
 *
 * Calculates if players attack will be critical, and hits the attack will have
 * on opposing player.
 *
 * Completes missing data for the playerAttackData array.
 */
void constructAttack(Game *game) {
    Attack currentAttack = (Attack)game->playerHero.attackData[0];
    // Calculate the amount of hits
    game->playerHero.attackData[1] = calcHits(currentAttack);
    // Calculate if attack is a critical hit
    game->playerHero.attackData[2] = calcCrit(currentAttack);
}


/* Function: uint8_t calcPower(uint8_t attackPower,
 *                             Hero* attackingHero,
 *                             Hero* defendingHero)
 *
 * Calculates the power the attack will have.
 */
uint8_t calcPower(uint8_t attackPower, Hero* attackingHero,
                  Hero* defendingHero) {
    uint8_t resultingPower = 0;

    // TODO: Write this logic you bozo.
    if (defendingHero == NULL) {
        resultingPower = attackPower *
                (attackingHero->current_stats.attack / (uint8_t)100);
    } else {
        resultingPower = attackPower *
                         (attackingHero->current_stats.attack / (uint8_t)100);

        resultingPower = resultingPower /
                (attackingHero->current_stats.defense / (uint8_t)100);
    }

    return resultingPower;
}

/* Function: void executeAttack(Attack attack, Hero *target)
 *
 * Support function to take the passed attack and perform the associated
 * attack actions.
 */
void executeAttack(Hero* attackingHero, Hero* defendingHero) {
    Attack currentAttack = (Attack) attackingHero->attackData[0];
    
    if (currentAttack == A_FIREBALL) {
        attackFireball(attackingHero, defendingHero);
    }
    else if (currentAttack == A_SUBSTITUTE) {
        attackCure(attackingHero);
    }
    else if (currentAttack == A_CURE) {
        attackSubstitute(attackingHero, defendingHero);
    }
    else if (currentAttack == A_SPELL_BARRAGE) {
        attackSpellBarrage(attackingHero, defendingHero);
    }
    else if (currentAttack == A_STRIKE) {
        attackStomp(attackingHero, defendingHero);
    }
    else if (currentAttack == A_PROTECT) {
        attackIronclad(attackingHero, defendingHero);
    }
    else if (currentAttack == A_MEDITATE) {
        attackPridwen(attackingHero);
    }
    else if (currentAttack == A_BERSERK) {
        attackExcalibur(attackingHero, defendingHero);
    }
    else if (currentAttack == A_STOMP) {
        attackStrike(attackingHero, defendingHero);
    }
    else if (currentAttack == A_IRONCLAD) {
        attackProtect(attackingHero, defendingHero);
    }
    else if (currentAttack == A_PRIDWEN) {
        attackMeditate(attackingHero);
    }
    else if (currentAttack == A_EXCALIBUR) {
        attackBerserk(attackingHero, defendingHero);
    }
}

// Wizard Attack Functions

/* TODO: Finalise functions:
 * Fireball
 * Substitute
 * Cure
 * Spell Barrage
 *
 * Strike
 * Protect
 * Meditate
 * Berserk
 *
 * Stomp
 * Ironclad
 * Pridwen
 * Excalibur
 *
 */

/* Function: void attackFireball(Game *game)
 *
 * Attack: Fireball
 * Performs single fireball spell on opponent.
 */
void attackFireball(Hero* attackingHero, Hero* defendingHero) {
    uint8_t currentHp = defendingHero->current_stats.hp;
    uint8_t attackPower = ATTACK_FIREBALL.basePower;

    //attackPower = calcPower(attackPower, attackingHero, defendingHero);
    attackPower = 90;

    if (currentHp <= attackPower) {
        defendingHero->current_stats.hp = 0;
    } else {
        defendingHero->current_stats.hp -= attackPower;
    }
}

/* Function: void attackSubstitute(Game *game)
 *
 * Attack: Substitute
 * Defensive move to dodge an opponents attack.
 */
void attackSubstitute(Hero* attackingHero, Hero* defendingHero) {

}

/* Function: void attackCure(Game *game)
 *
 * Attack: Cure
 * Performs a cure on the players hero.
 */
void attackCure(Hero* attackingHero){
    uint8_t currentHp = attackingHero->current_stats.hp;
    uint8_t maxHp = attackingHero->max_stats.hp;
    uint8_t attackPower = ATTACK_CURE.basePower;

    attackPower = calcPower(attackPower, attackingHero, NULL);

    if ((attackPower + currentHp) > maxHp) {
        attackingHero->current_stats.hp = maxHp;
    } else {
        attackingHero->current_stats.hp += attackPower;
    }
}

/* Function: void attackSpellBarrage(Hero* attackingHero, Hero* defendingHero)
 *
 * Attack: Spell Barrage
 * Performs multiple hits on the opponent.
 */
void attackSpellBarrage(Hero* attackingHero, Hero* defendingHero) {
    uint8_t currentHp = defendingHero->current_stats.hp;
    uint8_t attackPower = ATTACK_SPELL_BARRAGE.basePower;
    uint8_t hits = attackingHero->attackData[1];

    attackPower = calcPower(attackPower, attackingHero, defendingHero);

    for (int i = 0; i < hits; i++) {
        if (currentHp <= attackPower) {
            defendingHero->current_stats.hp = 0;
        } else {
            defendingHero->current_stats.hp -= attackPower;
        }
    }
}
// Monk Attack Functions
/* Function: void attackStrike(Game *game)
 *
 * Attack: Strike
 * Performs a single strike on the opponent.
 */
void attackStrike(Hero* attackingHero, Hero* defendingHero){
    uint8_t currentHp = defendingHero->current_stats.hp;
    uint8_t attackPower = ATTACK_STRIKE.basePower;

    attackPower = calcPower(attackPower, attackingHero, defendingHero);

    if (currentHp <= attackPower) {
        defendingHero->current_stats.hp = 0;
    } else {
        defendingHero->current_stats.hp -= attackPower;
    }
};


void attackProtect(Hero* attackingHero, Hero* defendingHero){

};

/* Function: void attackMeditate(Game *game)
 *
 * Attack: Meditate
 * Restores health to the user.
 */
void attackMeditate(Hero* attackingHero){
    uint8_t currentHp = attackingHero->current_stats.hp;
    uint8_t maxHp = attackingHero->max_stats.hp;
    uint8_t attackPower = ATTACK_MEDITATE.basePower;

    attackPower = calcPower(attackPower, attackingHero, NULL);

    if ((attackPower + currentHp) > maxHp) {
        attackingHero->current_stats.hp = maxHp;
    } else {
        attackingHero->current_stats.hp += attackPower;
    }
};

/* Function: void attackBerserk(Hero* attackingHero, Hero* defendingHero)
 *
 * Attack: Berserk
 * Performs multiple hits on the opponent.
 */
void attackBerserk(Hero* attackingHero, Hero* defendingHero){
    uint8_t currentHp = defendingHero->current_stats.hp;
    uint8_t attackPower = ATTACK_BERSERK.basePower;
    uint8_t hits = attackingHero->attackData[1];

    attackPower = calcPower(attackPower, attackingHero, defendingHero);

    for (int i = 0; i < hits; i++) {
        if (currentHp <= attackPower) {
            defendingHero->current_stats.hp = 0;
        } else {
            defendingHero->current_stats.hp -= attackPower;
        }
    }
};

// Knight Attack Functions
/* Function: void attackStomp(Hero* attackingHero, Hero* defendingHero)
 *
 * Attack: Stomp
 * Performs a single stomp attack on the opponent.
 */
void attackStomp(Hero* attackingHero, Hero* defendingHero){
    uint8_t currentHp = defendingHero->current_stats.hp;
    uint8_t attackPower = ATTACK_STOMP.basePower;

    attackPower = calcPower(attackPower, attackingHero, defendingHero);

    if (currentHp <= attackPower) {
        defendingHero->current_stats.hp = 0;
    } else {
        defendingHero->current_stats.hp -= attackPower;
    }
};
void attackIronclad(Hero* attackingHero, Hero* defendingHero){};

/* Function: attackPridwen(Hero* attackingHero)
 *
 * Attack: Pridwen
 * Restores health to the user.
 */
void attackPridwen(Hero* attackingHero){
    uint8_t currentHp = attackingHero->current_stats.hp;
    uint8_t maxHp = attackingHero->max_stats.hp;
    uint8_t attackPower = ATTACK_PRIDWEN.basePower;

    attackPower = calcPower(attackPower, attackingHero, NULL);

    if ((attackPower + currentHp) > maxHp) {
        attackingHero->current_stats.hp = maxHp;
    } else {
        attackingHero->current_stats.hp += attackPower;
    }
};

/* Function: void attackExcalibur(Hero* attackingHero, Hero* defendingHero)
 *
 * Attack: Excalibur
 * Performs multiple hits on the opponent.
 */
void attackExcalibur(Hero* attackingHero, Hero* defendingHero){
    uint8_t currentHp = defendingHero->current_stats.hp;
    uint8_t attackPower = ATTACK_EXCALIBUR.basePower;
    uint8_t hits = attackingHero->attackData[1];

    attackPower = calcPower(attackPower, attackingHero, defendingHero);

    for (int i = 0; i < hits; i++) {
        if (currentHp <= attackPower) {
            defendingHero->current_stats.hp = 0;
        } else {
            defendingHero->current_stats.hp -= attackPower;
        }
    }
};
