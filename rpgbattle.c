/***********************************************************************
 * @file    rpgbattle.c
 * @author  Alex Cameron Miller, William Read Scott
 * @date    14 September 2015
 **********************************************************************/

#include "system.h"
#include "rpgbattle.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "text.h"
#include "navswitch.h"
#include "button.h"
#include "gfx_utils.h"
#include "rpgbattle_utils.h"
#include <string.h>
#include <avr/delay.h>
#include "led.h"
#include "pacer.h"

/* Function: void gameInit(Game *game)
 *
 * Initialises the current game.
 */
void gameInit(Game *game) {
    game->state = GS_WELCOME;
    game->runOnce = 0;
    game->winner = 0;
    game->playerHero = createNone();
    game->opponentHero = createNone();
}

/* Function: void gs_update(Game *game, State state)
 *
 * Updates the selected game state and resets the text state.
 */
void gs_update(Game *game, State state) {
    game->runOnce = 0;
    tinygl_clear();
    led_set (LED1, 0);
    delay_ms (150); // TODO: Determine if this is needed
    game->state = state;
}

/* Function: void gsWelcome(Game *game)
 *
 * Updates the selected game state to the "Welcome" state.
 */
void gsWelcome(Game *game) {
    if (!game->runOnce) {
        tinygl_text(WELCOME_TEXT);
        game->runOnce = 1;
    }

    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        gs_update(game, GS_HERO_SELECT);
    }
}

/* Function: void gsHeroSelect(Game *game)
 *
 * Prompts user to select their hero of choice. Cycles through the available
 * heros. Once selected, calls gs_update to progress the game state.
 *
 * Controls: NAVSWITCH_NORTH = Backward through hero selection.
 *           NAVSWITCH_SOUTH = Forward through hero selection.
 */
void gsHeroSelect(Game *game) {
    // Initialised hero type must match first hero in enums.
    static uint8_t selectedHero = HERO_WIZARD;

    // The below must be identical to HeroType define in hero.h
    char *available_heroes[NUM_HEROES] = {HERO_NONE_NAME,
                                          HERO_WIZARD_NAME,
                                          HERO_MONK_NAME,
                                          HERO_KNIGHT_NAME};

    if (!game->runOnce) {
        tinygl_text(available_heroes[1]); // "None" hero should never be shown
        selectedHero = HERO_WIZARD;
        game->runOnce = 1;
    }

    // Backward through hero selection.
    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        if (selectedHero < NUM_HEROES - 1) {
            selectedHero += 1;
        } else if (selectedHero == NUM_HEROES - 1) {
            selectedHero = HERO_WIZARD;
        }
        tinygl_text(available_heroes[selectedHero]);
    }

    // Forward through hero selection.
    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        if (selectedHero > HERO_WIZARD) {
            selectedHero -= 1;
        } else if (selectedHero == HERO_WIZARD) {
            selectedHero = HERO_KNIGHT;
        }
        tinygl_text(available_heroes[selectedHero]);
    }

    // Hero has been selected, call gs_update to progress to next game state.
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        game->playerHero = createHero((HeroType)selectedHero);
        gs_update(game, GS_CONNECT);
    }
}

/* Function: void gsConnect(Game *game)
 *
 * Sends your selected hero to the opponent, stores the opponents hero.
 * Once the hero's have been successfully exchanged, calls gs_update to
 * progress the game state.
 */
void gsConnect(Game *game) {
    static uint8_t bHeroSent = 0;     // Bool: Has selected hero been sent.
    static uint8_t bHeroReceived = 0; // Bool: Has enemy hero been received.

    if (!game->runOnce) {
        led_set (LED1, 1);
        bHeroSent = 0;
        bHeroReceived = 0;
        game->runOnce = 1;
    }

    if (ir_uart_read_ready_p()) {
        game->opponentHero = createHero((HeroType)ir_uart_getc());
    }

    // Confirms that the hero has been received.
    if (game->opponentHero.hero_type != HERO_NONE) {
        bHeroReceived = 1;
    }

    // Sends selected hero to opponent.
    if (!bHeroSent){
        ir_uart_putc(game->playerHero.hero_type);
        bHeroSent = 1;
    }

    /* Hero's have been successfully exchanged, call gs_update to progress
     * to next game state.
     */
    if (bHeroReceived && bHeroSent) {
        gs_update(game, GS_ATTACK_SELECT);
    }
}

/* Function: gsAttackSelect(Game *game)
 *
 * Prompts user to select their attack.
 *
 * TODO: make this shit actually work
 */
void gsAttackSelect(Game *game) {
    static uint8_t bAttackSet = 0; // Bool: Has the attack been selected.

    if (!game->runOnce) {
        tinygl_text(ATTACK_SELECT_TEXT);
        bAttackSet = 0;
        game->runOnce = 1;
    }

    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        setAttackName(game->playerHero.attacks.attack_1.attack);
        game->playerHero.attackData[0] = game->playerHero.attacks.attack_1.attack;
        bAttackSet = 1;
    }

    if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        setAttackName(game->playerHero.attacks.attack_2.attack);
        game->playerHero.attackData[0] = game->playerHero.attacks.attack_2.attack;
        bAttackSet = 1;
    }

    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        setAttackName(game->playerHero.attacks.attack_3.attack);
        game->playerHero.attackData[0] = game->playerHero.attacks.attack_3.attack;
        bAttackSet = 1;
    }

    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        setAttackName(game->playerHero.attacks.attack_4.attack);
        game->playerHero.attackData[0] = game->playerHero.attacks.attack_4.attack;
        bAttackSet = 1;
    }

    // Allows player to check their own current stats and the enemy stats.
    if (button_push_event_p(BUTTON1)) {
        gs_update(game, GS_MY_STATUS);
    }

    // Attack confirmed, proceed with selected attacks to next game state.
    if (navswitch_push_event_p(NAVSWITCH_PUSH) && bAttackSet == 1) {
        constructAttack(game);
        gs_update(game, GS_EXCHANGE_ATTACKS);
        led_set (LED1, 1);
    }
}


void gsExchangeAttacks(Game *game) {
    int i = 0;
    static uint8_t attack_received = 0;
    static uint8_t attack_sent = 0;

    if (!game->runOnce) {
        attack_received = 0;
        attack_sent = 0;
        game->runOnce = 1;
    }

    if (ir_uart_read_ready_p()) {
        attack_received = 1;
        for (i = 0; i < ATTACK_DATA_LOOP_SIZE; i++) {
            game->opponentHero.attackData[i] = (uint8_t)ir_uart_getc();
        }
        game->opponentHero.attackData[3] = '\0';
    }

    if (!attack_sent) {
        attack_sent = 1;
        for (i = 0; i < ATTACK_DATA_LOOP_SIZE; i++) {
            ir_uart_putc(game->playerHero.attackData[i]);
        }
    }

    if (attack_received && attack_sent) {
        if (game->playerHero.current_stats.speed == game->opponentHero.current_stats.speed) {
            gs_update(game, GS_SETTLE_SPEED_TIE);
        } else {
            gs_update(game, GS_RESOLVE_TURN);
        }

    }
}

/* Function: void gsMyStatus(Game *game)
 *
 * Game state to allow player to check their current stats.
 */
void gsMyStatus(Game *game) {
    char status_message[MAX_LINE_LENGTH] = MY_STATUS_MESSAGE;
    char hp_value[BYTE_STRING_SIZE];

    iToString(game->playerHero.current_stats.hp, hp_value);
    strncat(status_message, hp_value, MAX_LINE_LENGTH);

    if (!game->runOnce) {
        tinygl_text(status_message);
        game->runOnce = 1;
    }

    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        gs_update(game, GS_ENEMY_STATUS);
    }
}

/* Function: void gsEnemyStatus(Game *game)
 *
 * Game state to allow player to check the enemies current stats.
 */
void gsEnemyStatus(Game *game) {
    char status_message[MAX_LINE_LENGTH] = "  ENEMY HP: ";
    char hp_value[BYTE_STRING_SIZE];

    iToString(game->opponentHero.current_stats.hp, hp_value);
    strncat(status_message, hp_value, MAX_LINE_LENGTH);

    if (!game->runOnce) {
        tinygl_text(status_message);
        game->runOnce = 1;
    }

    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        gs_update(game, GS_ATTACK_SELECT);
    }
}

void gsSettleSpeedTie(Game *game) {
    static uint8_t bOpponentReceived = 0;
    static uint8_t bPlayerSent = 0;
    static uint8_t textSet = 0;

    if (!game->runOnce) {
        delay_ms(100);
        ir_uart_init();
        led_set (LED1, 1);
        bOpponentReceived = 0;
        bPlayerSent = 0;
        //game->playerRandInt = rand_uint8(0, 255);
        game->playerRandInt = 222;
        game->opponentRandInt = 0;
        game->speedTieResult = 0;
        game->runOnce = 1;
    }

    if (ir_uart_read_ready_p() && !bOpponentReceived) {
        game->opponentRandInt = (uint8_t)ir_uart_getc();
    }

    if (game->opponentRandInt != 0) {
        bOpponentReceived = 1;
    }

    if (!bPlayerSent) {
        ir_uart_putc(game->playerRandInt);
        bPlayerSent = 1;
    }

    if (bOpponentReceived && bPlayerSent && !textSet) {
        char debug[4];
        char debug2[4];
        char debug3[8];
        debug[0] = '\0';
        debug2[0] = '\0';
        debug3[0] = '\0';
        iToString(game->playerRandInt, debug);
        iToString(game->opponentRandInt, debug2);
        strncat(debug3, debug, MAX_LINE_LENGTH);
        strncat(debug3, debug2, MAX_LINE_LENGTH);
        tinygl_text(debug3);
        ir_uart_putc(game->playerRandInt);
        textSet = 1;
        led_set (LED1, 0);
    }

//    if (bOpponentReceived && bPlayerSent) {
//        if (opponentInt == playerInt) {
//            gs_update(game, GS_SETTLE_SPEED_TIE);
//        } else {
//            if (opponentInt > playerInt) {
//                game->speedTieResult = 1;
//            }
//            gs_update(game, GS_RESOLVE_TURN);
//        }
//    }
}


void determineResultOrStatus(Game *game) {
    if (game->playerHero.current_stats.hp <= 0 ||
        game->opponentHero.current_stats.hp <= 0) {
        if (game->playerHero.current_stats.hp > 0) {
            game->winner = 1;
        }
        gs_update(game, GS_RESULT);
    }
    else {
        gs_update(game, GS_MY_STATUS);
    }
}

void gs_resolve_turn(Game *game) {
    uint8_t tieResult = 0;
    uint8_t playerPriority = determineAttackPriority((Attack) game->playerHero.attackData[0]);
    uint8_t opponentPriority = determineAttackPriority((Attack) game->opponentHero.attackData[0]);
    Hero* firstHero;
    Hero* secondHero;

    if (playerPriority > opponentPriority) {
        firstHero = &game->playerHero;
        secondHero = &game->opponentHero;
    } else if (opponentPriority > playerPriority) {
        firstHero = &game->opponentHero;
        secondHero = &game->playerHero;
    } else if (game->playerHero.current_stats.speed == game->opponentHero.current_stats.speed){
        tieResult = game->speedTieResult;
        if (tieResult == 0) {
            firstHero = &game->playerHero;
            secondHero = &game->opponentHero;
        } else {
            firstHero = &game->opponentHero;
            secondHero = &game->playerHero;
        }
    } else if (game->playerHero.current_stats.speed > game->opponentHero.current_stats.speed) {
        firstHero = &game->playerHero;
        secondHero = &game->opponentHero;
    } else { // Opponent is faster
        firstHero = &game->opponentHero;
        secondHero = &game->playerHero;
    }

    executeAttack(firstHero, secondHero);
    if (secondHero->current_stats.hp > 0) {
        executeAttack(secondHero, firstHero);
    }

    // Use support function to determine the next game state and update accordingly
    determineResultOrStatus(game);
}


// TODO: Make sure rounds are working, currently reiniting game; we may need a reset_game function
void gsResult(Game *game) {
    if (game->winner) {
        if (!game->runOnce) {
            tinygl_text(VICTORY_TEXT);
            game->runOnce = 1;
        }
    }
    else { // Defeated
        if (!game->runOnce) {
            tinygl_text(DEFEAT_TEXT);
            game->runOnce = 1;
        }
    }

    if (navswitch_push_event_p(NAVSWITCH_PUSH) ||
        button_push_event_p(BUTTON1)) {
        game->runOnce = 0;
        tinygl_clear();
        gameInit(game); // This might work, yolo
    }
}
