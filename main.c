/***********************************************************************
 * @file    main.c
 * @author  Alex Cameron Miller, William Read Scott
 * @date    14 September 2015
 **********************************************************************/

// C Headers
#include <stdlib.h>

// System Includes
#include "button.h"
#include "display.h"
#include "ir_uart.h"
#include "navswitch.h"
#include "pacer.h"
#include "system.h"
#include "tinygl.h"
#include "timer.h"

// RPG Specific Includes
#include "rpgbattle.h"
#include "gfx_utils.h"
#include "text.h"

int main (void) {

    // INIT SYSTEM
    system_init ();
    pacer_init (LOOP_RATE);
    tinygl_init (LOOP_RATE);
    navswitch_init ();
    button_init ();
    ir_uart_init();
    init_tinygl_text();
    timer_init();

    int time1 = timer_get();
    timer_wait(500);
    int time2 = timer_get();
    int time3 = time2 - time1;
    srand(time3);

    // INIT GAME
    Game game;
    gameInit(&game);

    while (1) {
        pacer_wait();
        tinygl_update();
        navswitch_update();
        button_update();

        if (game.state == GS_WELCOME) {
            gsWelcome(&game);
        }
        else if (game.state == GS_HERO_SELECT) {
            gsHeroSelect(&game);
        }
        else if (game.state == GS_CONNECT) {
            gsConnect(&game);
        }
        else if (game.state == GS_MY_STATUS) {
            gsMyStatus(&game);
        }
        else if (game.state == GS_ENEMY_STATUS) {
            gsEnemyStatus(&game);
        }
        else if (game.state == GS_ATTACK_SELECT) {
            gsAttackSelect(&game);
        }
        else if (game.state == GS_SETTLE_SPEED_TIE) {
            gsSettleSpeedTie(&game);
        }
        else if (game.state == GS_EXCHANGE_ATTACKS) {
            gsExchangeAttacks(&game);
        }
        else if (game.state == GS_RESOLVE_TURN) {
            gs_resolve_turn(&game);
        }
        else {
            gsResult(&game);
        }
    }

    return 0;
}
