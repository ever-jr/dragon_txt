#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "term_helper.h"
#include "character.h"

struct game_state {
    bool has_ended;
    struct character *main_character;
};

void game_update(struct game_state *gs) {
    if (character_has_died(gs->main_character)) {
        gs->has_ended = true;
    }
}

void game_show_gameover_message(const struct game_state *gs) {
    if (character_has_died(gs->main_character)) {
        printf("\n| YOU DIED! |\n");
        return;
    }
    printf("\n| YOU EXITED THE GAME... for some reason |\n");
}

int main() {
    th_clear();

    struct game_state game;
    game.has_ended = false;

    // defining player ------------------------------------
    struct character player;
    {
        // build character
        char player_name[CHARACTER_NAME_SIZE];

        printf("[CHARACTER CREATION]\nEnter character name: ");
        fgets(player_name, CHARACTER_NAME_SIZE, stdin); // read input

        // remove trailing newline if present
        size_t len = strlen(player_name);
        if (len > 0 && player_name[len - 1] == '\n') {
            player_name[len - 1] = '\0';
        }

        player = character_create(player_name, 100.0f, 1);
    }
    game.main_character = &player;
    // ----------------------------------------------------

    // defining enemies -----------------------------------
    struct character enemy_goblin = character_create("Goblin                         ", 30.0f, 1);

    struct character enemy_orc = character_create("Orc                            ", 220.0f, 4);
    // ----------------------------------------------------


    #define COMMAND_SIZE 7
    char command[COMMAND_SIZE];

    do {
        th_clear();

        character_print_stats(&player);
        printf("\n[COMMANDS]\n- exit\n- sdmg\n- battle\n: ");
        fgets(command, COMMAND_SIZE, stdin); // read input

        // remove trailing newline if present
        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n') {
            command[len - 1] = '\0';
        } else {
            // clear leftover input from stdin
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        if (strcmp(command, "exit") == 0) {
            game.has_ended = true;
        } else if (strcmp(command, "sdmg") == 0) {
            character_take_dmg(&player, 10.0f);
        } else if (strcmp(command, "battle") == 0) {
            struct character enemy = enemy_goblin;

            bool is_running_from_battle = false;
            bool is_enemy_dead = character_has_died(&enemy);

            while (!is_enemy_dead
                && !character_has_died(game.main_character)
                && !is_running_from_battle
            ) {
                th_clear();

                character_print_stats(&player);
                printf("\nVS\n\n");
                character_print_stats(&enemy);

                printf("\n[COMMANDS]\n- exit\n- atk\n- run\n: ");
                fgets(command, COMMAND_SIZE, stdin); // read input

                // remove trailing newline if present
                size_t len = strlen(command);
                if (len > 0 && command[len - 1] == '\n') {
                    command[len - 1] = '\0';
                } else {
                    // clear leftover input from stdin
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                }

                if (strcmp(command, "exit") == 0) {
                    game.has_ended = true;
                    break;
                } else if (strcmp(command, "atk") == 0) {
                    float player_damage = character_calc_final_damage(game.main_character);
                    character_take_dmg(&enemy, player_damage);
                } else if (strcmp(command, "run") == 0) {
                    is_running_from_battle = true;
                }

                game_update(&game);
                is_enemy_dead = character_has_died(&enemy);

                float enemy_damage = character_calc_final_damage(&enemy);
                character_take_dmg(game.main_character, enemy_damage);
            }

            if (is_enemy_dead) {
                th_clear();
                printf("%s has died!\n", enemy.name);
                th_stop();
            }
        }

        game_update(&game);
    } while (!game.has_ended);

    game_show_gameover_message(&game);

    return 0;
}
