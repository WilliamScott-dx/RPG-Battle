/***********************************************************************
 * @file    rpgbattle.h
 * @author  Alex Cameron Miller, William Read Scott
 * @date    14 September 2015
 **********************************************************************/
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include "rpgbattle_utils.h"

/* Function: uint8_t rand_uint8(uint8_t min, uint8_t max)
 *
 * Returns a random uint8_t between the min and the max values.
 */
uint8_t rand_uint8(uint8_t min, uint8_t max) {
    return (uint8_t) (rand()%(max-min)+min);
}

/* Function: iToString(uint8_t num, char *dest)
 *
 * Copies an integer to a char for printing purposes.
 */
void iToString(uint8_t num, char *dest) {
    char first = (num / 100) + '0';
    char second  = ((num / 10) % 10) + '0';
    char third = (num % 10) + '0';

    dest[0] = first;
    dest[1] = second;
    dest[2] = third;
    dest[3] = '\0';
}