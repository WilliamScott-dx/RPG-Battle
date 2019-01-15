/***********************************************************************
 * @file    rpgbattle.h
 * @author  Alex Cameron Miller, William Read Scott
 * @date    14 September 2015
 **********************************************************************/
#ifndef ASSIGNMENT_RPGBATTLE_H
#define ASSIGNMENT_RPGBATTLE_H

#include "system.h"
#include "hero.h"
#include "attack.h"

#define LOOP_RATE 2500
#define MESSAGE_RATE 100

// enum for states
typedef enum {GS_WELCOME, GS_HERO_SELECT, GS_CONNECT, GS_MY_STATUS,
              GS_ENEMY_STATUS, GS_ATTACK_SELECT, GS_RESOLVE_TURN, GS_RESULT,
              GS_EXCHANGE_ATTACKS, GS_SETTLE_SPEED_TIE
} State;

/** Game structure */
#define _GAMESTRUCT
typedef struct game Game;
struct game {
    State state;
    uint8_t runOnce;
    Hero playerHero;
    Hero opponentHero;
    uint8_t winner;
    uint8_t speedTieResult;
    uint8_t opponentRandInt;
    uint8_t playerRandInt;
};

// Init Game
void gameInit(Game *game);

// GAME STATES
void gsWelcome(Game *game);

void gsHeroSelect(Game *game);

void gsConnect(Game *game);

void gsMyStatus(Game *game);

void gsEnemyStatus(Game *game);

void gsAttackSelect(Game *game);

void gsExchangeAttacks(Game *game);

void gs_resolve_turn(Game* game);

void gsSettleSpeedTie(Game* game);

void determineResultOrStatus(Game* game); // Support Function for resolve_turn to determine next game state

void gsResult(Game *game);

#endif // ASSIGNMENT_RPGBATTLE_H