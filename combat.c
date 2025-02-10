//
// Created by louis on 08/02/2025.
//
#include "combat.h"
#include <stdio.h>
#include <stdlib.h>

#define BASE_MOVE_DAMAGE 5
//Couleurs
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define BROWN "\x1B[38;5;94m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define RESET "\x1B[0m"

// Affichage stylisé des barres de HP
void printHpBar(Pokemon p) {
    printf(GREEN "[" RESET );
    int hpPercent = (p.hp * 10) / p.maxHp; // Échelle sur 10
    for (int i = 0; i < 10; i++) {
        if (i < hpPercent)
            printf(GREEN "|" RESET );
        else
            printf(RED "|" RESET );
    }
    printf(GREEN "] %d/%d" RESET, p.hp, p.maxHp);
}

Pokemon generateWildPokemon(Pokemon playerPokemon) {
    char *names[] = {"Pikachu", "Eevee", "Rattata", "Zubat", "Geodude"};
    int index = rand() % 5;

    Pokemon wild = {
        .name = "",
        .level = playerPokemon.level + (rand() % 3 - 1)
    };

    if (wild.level < 1) {
        wild.level = 1;
    }

    wild.maxHp = playerPokemon.maxHp;
    wild.hp = wild.maxHp;
    wild.attack = playerPokemon.attack + (rand() % 5);
    wild.defense = playerPokemon.defense + (rand() % 5);
    wild.speed = playerPokemon.speed + (rand() % 5);
    wild.accuracy = (rand() % 5) + 1;
    wild.evasion = (rand() % 5) + 1;
    wild.exp = 0;
    switch (index) {
        case 0 : wild.type = "Electric"; break;
        case 1 : wild.type = "Normal"; break;
        case 2 : wild.type = "Poison"; break;
        case 3 : wild.type = "Water"; break;
        case 4 : wild.type = "Ground"; break;
        default : wild.type = "Normal"; break;
    }

    snprintf(wild.name, sizeof(wild.name), "%s", names[index]);
    return wild;
}

/* On ne passe plus de Pokémon à levelUp via un paramètre additionnel :
   on utilise le Pokémon en combat (ally) */
void battle(Player *player, Pokemon wild) {
    Pokemon *ally = &player->pokemons[0];

    printf(YELLOW "\n=============================\n");
    printf("  Un %s sauvage apparait ! \n", wild.name);
    printf("=============================\n" RESET);

    printf(RED "Niveau: %d\n" RESET, wild.level);
    printf("Stats du %s: ", wild.name);
    printHpBar(wild);
    printf("\nAttaque: %d | Defense: %d | Vitesse: %d\n",
           wild.attack, wild.defense, wild.speed);

    while (ally->hp > 0 && wild.hp > 0) {
        int action;

        printf(BLUE "\n-----------------------------\n");
        printf("Votre tour !\n");
        printf("-----------------------------\n" RESET);

        printf("%s | ", ally->name);
        printHpBar(*ally);
        printf("\n\n");

        printf("1- Attaquer\n");
        printf("2- Esquiver\n");
        printf("3- Utiliser un objet\n");
        printf("4- Capturer\n");
        printf("5- Fuir\n");
        printf(YELLOW "Choisissez une action: " RESET);

        scanf("%d", &action);

        switch (action) {
            case 1: {  // Attaquer
                int damage = calculateDamage(ally->attack, wild.defense);
                wild.hp -= damage;
                if (wild.hp < 0)
                    wild.hp = 0;
                printf("Vous attaquez %s ! Degats: %d, HP restant: %d\n",
                       wild.name, damage, wild.hp);
            } break;

            case 2: {  // Esquiver
                printf("Vous tentez d'esquiver !\n");
                float dodgeRate = (float)wild.accuracy / ((float)wild.accuracy + (float)ally->evasion) + 0.1f;
                if (dodgeRate > 1.0f)
                    dodgeRate = 1.0f;
                float chance = (float)rand() / (float)RAND_MAX;
                if (chance < dodgeRate) {
                    printf("Esquive reussie ! Vous evitez l'attaque ennemie.\n");
                    continue; // Passe directement au prochain tour
                } else {
                    printf("Esquive echouee !\n");
                }
            } break;

            case 3: {  // Utiliser un objet
                int itemChoice;
                int itemUsed = 0;
                if (itemUsed < 5) {
                    printf("Quel objet souhaitez-vous utiliser ?\n");
                    printf(CYAN "1 - Potion (+5 HP) Restant : %d\n" RESET GREEN "2 - Super Potion (+10 HP) Restant : %d\n" RESET RED "3 - Rare Candy (+1 lvl) Restant : %d\n" RESET , player->potion, player->superPotion, player->rareCandy);
                    scanf("%d", &itemChoice);

                    switch (itemChoice) {
                        case 1:
                            if (player->potion > 0) {
                                if (ally->hp + 5 > ally->maxHp) {
                                    ally->hp = ally->maxHp;
                                }
                                else {
                                    ally->hp += 5;
                                }
                                printf("Vous utilisez une "CYAN"Potion"RESET" !\n");
                                player->potion--;
                                itemUsed++;
                            } else {
                                printf("Vous n'avez pas de "CYAN"Potion"RESET".\n");
                            }
                        break;
                        case 2:
                            if (player->superPotion > 0) {
                                if (ally->hp + 10 > ally->maxHp) {
                                    ally->hp = ally->maxHp;
                                }
                                else {
                                    ally->hp += 10;
                                }
                                printf("Vous utilisez une "GREEN"Super Potion"RESET" !\n");
                                player->superPotion--;
                                itemUsed++;
                            } else {
                                printf("Vous n'avez pas de "GREEN"Super Potion"RESET".\n");
                            }
                        break;
                        case 3:
                            if (player->rareCandy > 0) {
                                printf("Vous utilisez un "RED"Rare Candy"RESET" !\n");
                                candyLevelUp(ally);  // Utilise le Rare Candy pour faire monter de niveau le Pokémon en combat
                                player->rareCandy--;
                                itemUsed++;
                            } else {
                                printf("Vous n'avez pas de "RED"Rare Candy"RESET".\n");
                            }
                        break;
                        default:
                            printf("Choix invalide.\n");
                        break;
                    }
                }
            } break;

            case 4: {  // Capturer
                printf("Vous tentez de capturer %s !\n", wild.name);
                float captureRate = ((float)wild.maxHp - wild.hp) / ((float)wild.maxHp) - 0.5f;
                if (captureRate < 0)
                    captureRate = 0;
                float chance = (float)rand() / (float)RAND_MAX;
                if (chance < captureRate) {
                    printf("Capture reussie ! Vous avez capture %s !\n", wild.name);
                    player->pokemons[player->numPokemons++] = wild;
                    return;  // Fin du combat
                } else {
                    printf("La capture a echoue.\n");
                }
            } break;

            case 5: {  // Fuir
                printf("Vous tentez de fuir !\n");
                float successRate = (float)ally->speed / ((float)ally->speed + wild.speed);
                float chance = (float)rand() / (float)RAND_MAX;
                if (chance < successRate) {
                    printf("Vous avez reussi a fuir !\n");
                    return;  // Fin du combat
                } else {
                    printf("La fuite a echoue !\n");
                }
            } break;

            default:
                printf("Choix invalide.\n");
                break;
        }

        if (wild.hp <= 0) {
            printf("%s a ete vaincu !\n", wild.name);
            int exp_gagnee = (rand() % 51) + 75;
            ally->exp += exp_gagnee;
            printf("%s a gagne %d points d'experience\n", ally->name, exp_gagnee);
            levelUp(ally);
            break;
        }

        if (wild.hp > 0) {
            printf("%s attaque %s !\n", wild.name, ally->name);
            int damage = calculateDamage(wild.attack, ally->defense);
            ally->hp -= damage;
            if (ally->hp < 0)
                ally->hp = 0;
            printf("Degats: %d, HP restant: %d\n", damage, ally->hp);

            if (ally->hp <= 0) {
                printf(RED"Vous avez perdu le combat.\n"RESET);
                break;
            }
        }
    }
}

int calculateDamage(int attack, int defense) {
    float rawDamage = ((float)attack * BASE_MOVE_DAMAGE) / (float)defense;
    int lower = (int)rawDamage;
    if (rawDamage == (float)lower) {
        return lower;
    } else {
        if (rand() % 2 == 0)
            return lower;
        else
            return lower + 1;
    }
}

int roundStat(float value) {
    int lower = (int)value;
    if (value == (float)lower) {
        // La valeur est déjà entière
        return lower;
    } else {
        // 50 % de chance d'arrondir vers le bas, 50 % vers le haut
        if (rand() % 2 == 0)
            return lower;
        else
            return lower + 1;
    }
}


void levelUp(Pokemon *pokemon) {
    int exp_needed = 500 + (pokemon->level - 1) * 1000;
    while (pokemon->exp >= exp_needed) {
        pokemon->exp -= exp_needed;
        pokemon->level++;
        exp_needed += 1000;
        // Mise à jour des stats avec arrondi aléatoire (50% chance de round up)
        pokemon->maxHp   = roundStat(pokemon->maxHp   * 1.3);
        pokemon->attack  = roundStat(pokemon->attack  * 1.3);
        pokemon->defense = roundStat(pokemon->defense * 1.3);
        pokemon->speed   = roundStat(pokemon->speed   * 1.3);
        pokemon->accuracy = roundStat(pokemon->accuracy * 1.3);
        pokemon->evasion  = roundStat(pokemon->evasion  * 1.3);
        pokemon->hp = pokemon->maxHp; // Soins complets après level-up
        printf("%s est passe au niveau %d !\n", pokemon->name, pokemon->level);
    }
}


void candyLevelUp(Pokemon *pokemon) {
    // Pour un Rare Candy, on fait monter d'un niveau directement
    pokemon->level++;
    // Mise à jour des stats avec arrondi aléatoire (50% chance de round up)
    pokemon->maxHp   = roundStat(pokemon->maxHp   * 1.3);
    pokemon->attack  = roundStat(pokemon->attack  * 1.3);
    pokemon->defense = roundStat(pokemon->defense * 1.3);
    pokemon->speed   = roundStat(pokemon->speed   * 1.3);
    pokemon->accuracy = roundStat(pokemon->accuracy * 1.3);
    pokemon->evasion  = roundStat(pokemon->evasion  * 1.3);
    pokemon->hp = pokemon->maxHp;
    printf("%s est passe au niveau %d grace au "RED"Rare Candy"RESET" !\n", pokemon->name, pokemon->level);
}


void exploreNature(Player *player) {
    if (player->numPokemons == 0) {
        printf("Vous devez avoir au moins un Pokemon pour explorer.\n");
        return;
    }
    Pokemon wild = generateWildPokemon(player->pokemons[0]);
    battle(player, wild);
}
