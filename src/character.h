#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdint.h>
#include <stdbool.h>

#define CHARACTER_NAME_SIZE 32

struct character {
    char name[CHARACTER_NAME_SIZE];
    float health;
    float max_health;

    uint8_t strength;

    float damage;
};

struct character character_create(char *name, float health, uint8_t strength);

/**
 * Calculate the character's final damage according to his attributes.
 */
float character_calc_final_damage(const struct character *c);

/**
 * Show all character stats.
 */
void character_print_stats(const struct character *c);

void character_take_dmg(struct character *c, float damage);

void character_restore_health(struct character *c, float heal_amount);

bool character_has_died(struct character *c);

#endif
