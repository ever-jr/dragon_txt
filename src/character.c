#include "character.h"
#include <stdio.h>
#include <string.h>

struct character character_create(const char name[CHARACTER_NAME_SIZE], float health, uint8_t strength) {
    struct character new_character;
    strncpy_s(new_character.name, CHARACTER_NAME_SIZE, name, CHARACTER_NAME_SIZE);
    new_character.name[CHARACTER_NAME_SIZE - 1] = '\0';
    new_character.health = health;
    new_character.max_health = health;
    new_character.strength = strength;
    new_character.damage = 10.0f;

    return new_character;
}

float character_calc_final_damage(const struct character *c) {
    uint8_t strength = c->strength;
    float damage = c->damage;

    if (strength <= 0) {
        strength = 1;
    }

    if (damage <= 0.0f) {
        return 0.0f;
    }

    return damage * (float)strength;
}

void character_print_stats(const struct character *c) {
    printf("+--[CHARACTER]---------\n| Name: %s\n| Health: %d/%d\n| Strength: %d\n| Damage: %d\n| \n| Final Damage: %d\n+----------------------\n",
           c->name, (int)c->health, (int)c->max_health, c->strength, (int)c->damage, (int)character_calc_final_damage(c));
}

void character_take_dmg(struct character *c, float damage) {
    float health = c->health;

    health -= damage;
    if (health < 0.0f) {
        health = 0.0f;
    }

    c->health = health;
}

void character_restore_health(struct character *c, float heal_amount) {
    float health = c->health;
    float max_health = c->max_health;

    health += heal_amount;
    if (health > max_health) {
        health = max_health;
    }

    c->health = health;
}

bool character_has_died(struct character *c) {
    return c->health <= 0.0f;
}
