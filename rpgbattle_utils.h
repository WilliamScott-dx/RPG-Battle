#ifndef ASSIGNMENT_RPGBATTLE_UTILS_H
#define ASSIGNMENT_RPGBATTLE_UTILS_H

#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

/* Function rand_uint8
 *
 * @param   int min
 * @param   int max
 *
 * Returns a random number between the min and the max.
 */
uint8_t rand_uint8(uint8_t min, uint8_t max);

// Copies an 8 bit int into a string
void iToString(uint8_t num, char *dest);

#endif // ASSIGNMENT_RPGBATTLE_UTILS_H