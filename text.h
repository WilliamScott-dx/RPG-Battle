/***********************************************************************
 * @file    text.h
 * @author  Alex Cameron Miller, William Read Scott
 * @date    14 September 2015
 **********************************************************************/
#ifndef ASSIGNMENT_TEXT_H
#define ASSIGNMENT_TEXT_H

#define WELCOME_TEXT "  WELCOME! JOY-IN TO CONTINUE"
#define UNKNOWN_TEXT "  UNKNOWN"

#define MAX_NAME_SIZE 16  // Used for both Heroes and Attacks
#define MAX_LINE_LENGTH 32
#define BYTE_STRING_SIZE 4

// HERO NAMES
#define HERO_NONE_NAME "  NONE"
#define HERO_WIZARD_NAME "  WIZARD"
#define HERO_KNIGHT_NAME "  KNIGHT"
#define HERO_MONK_NAME "  MONK"

// ATTACK NAMES
// Wizard
#define A_FIREBALL_NAME "  FIREBALL"
#define A_SUBSTITUTE_NAME "  SUBSTITUTE"
#define A_CURE_NAME "  CURE"
#define A_SPELL_BARAGE_NAME "  SPELL BARRAGE"
// Monk
#define A_STRIKE_NAME "  STRIKE"
#define A_PROTECT_NAME "  PROTECT"
#define A_MEDITATE_NAME "  MEDITATE"
#define A_BERSERK_NAME "  BERSERK"
// Knight
#define A_STOMP_NAME " STOMP"
#define A_IRONCLAD_NAME "  HEAL"
#define A_PRIDWEN_NAME "  PRIDWEN"
#define A_EXCALIBUR_NAME "  EXCALIBUR"
// END ATTACK NAMES

#define MY_STATUS_MESSAGE "  MY HP: "

// GAME STATE: ATTACK SELECT
#define ATTACK_SELECT_TEXT "  SELECT ATTACK USING JOY"

// GAME STATE: RESULT
#define VICTORY_TEXT "  VICTORY"
#define DEFEAT_TEXT "  DEFEAT"

#endif // ASSIGNMENT_TEXT_H