/***********************************************************************
 * @file    gfx_utils.c
 * @author  Alex Cameron Miller, William Read Scott
 * @date    14 September 2015
 **********************************************************************/

#include "tinygl.h"
#include "gfx_utils.h"
#include "attack.h"
#include "text.h"
#include "../fonts/font3x5_1.h"

#define MESSAGE_RATE 30

void init_tinygl_text (void) {
    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_text(" ");
}

void setAttackName(Attack attack) {
    // Wizard Attacks
    if (attack == A_FIREBALL) {
        tinygl_text(A_FIREBALL_NAME);
    }
    else if (attack == A_CURE) {
        tinygl_text(A_CURE_NAME);
    }
    else if (attack == A_SUBSTITUTE) {
        tinygl_text(A_SUBSTITUTE_NAME);
    }
    else if (attack == A_SPELL_BARRAGE) {
        tinygl_text(A_SPELL_BARAGE_NAME);
    }
    // Knight Attacks
    else if (attack == A_STRIKE) {
        tinygl_text(A_STRIKE_NAME);
    }
    else if (attack == A_PROTECT) {
        tinygl_text(A_PROTECT_NAME);
    }
    else if (attack == A_MEDITATE) {
        tinygl_text(A_MEDITATE_NAME);
    }
    else if (attack == A_BERSERK) {
        tinygl_text(A_BERSERK_NAME);
    }
    // Fighter Attacks
    else if (attack == A_STOMP) {
        tinygl_text(A_STOMP_NAME);
    }
    else if (attack == A_IRONCLAD) {
        tinygl_text(A_IRONCLAD_NAME);
    }
    else if (attack == A_PRIDWEN) {
        tinygl_text(A_PRIDWEN_NAME);
    }
    else if (attack == A_EXCALIBUR) {
        tinygl_text(A_EXCALIBUR_NAME);
    }
    else { // Attack unkown
        tinygl_text(UNKNOWN_TEXT);
    }
}