//
// Created by louis on 08/02/2025.
//
#include "combat.h"
#include <stdio.h>
#include <stdlib.h>

#define BASE_MOVE_DAMAGE 5

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

    snprintf(wild.name, sizeof(wild.name), "%s", names[index]);
    return wild;
}

/* On ne passe plus de Pokémon à levelUp via un paramètre additionnel :
   on utilise le Pokémon en combat (ally) */
void battle(Player *player, Pokemon wild) {
    // On utilise le premier Pokémon du joueur comme combattant
    Pokemon *ally = &player->pokemons[0];

    printf("Un %s sauvage apparait ! Niveau: %d\n", wild.name, wild.level);
    printf("Stats du %s: HP: %d/%d, Attaque: %d, Defense: %d, Vitesse: %d\n",
           wild.name, wild.hp, wild.maxHp, wild.attack, wild.defense, wild.speed);

    while (ally->hp > 0 && wild.hp > 0) {
        int action;
        printf("\nVotre tour !\n");
        printf("Que voulez-vous faire ?\n");
        printf("1 - Attaquer\n");
        printf("2 - Esquiver\n");
        printf("3 - Utiliser un objet\n");
        printf("4 - Capturer\n");
        printf("5 - Fuir\n");
        scanf("%d", &action);

        switch (action) {
            case 1: {  // Attaquer
                int damage = calculateDamage(ally->attack, wild.defense);
                wild.hp -= damage;
                if (wild.hp < 0)
                    wild.hp = 0;
                printf("Vous attaquez %s ! Dégâts: %d, HP restant: %d\n",
                       wild.name, damage, wild.hp);
            } break;

            case 2: {  // Esquiver
                printf("Vous tentez d'esquiver !\n");
                float dodgeRate = (float)wild.accuracy / ((float)wild.accuracy + (float)ally->evasion) + 0.1f;
                if (dodgeRate > 1.0f)
                    dodgeRate = 1.0f;
                float chance = (float)rand() / (float)RAND_MAX;
                if (chance < dodgeRate) {
                    printf("Esquive réussie ! Vous évitez l'attaque ennemie.\n");
                    continue; // Passe directement au prochain tour
                } else {
                    printf("Esquive échouée !\n");
                }
            } break;

            case 3: {  // Utiliser un objet
                int itemChoice;
                printf("Quel objet souhaitez-vous utiliser ?\n");
                printf("1 - Potion (+5 HP) Restant : %d\n2 - Super Potion (+10 HP) Restant : %d\n3 - Rare Candy (+1 lvl) Restant : %d\n", player->potion, player->superPotion, player->rareCandy);
                scanf("%d", &itemChoice);

                switch (itemChoice) {
                    case 1:
                        if (player->potion > 0) {
                            ally->hp += 5;
                            printf("Vous utilisez une Potion !\n");
                            player->potion--;
                        } else {
                            printf("Vous n'avez pas de Potion.\n");
                        }
                        break;
                    case 2:
                        if (player->superPotion > 0) {
                            ally->hp += 10;
                            printf("Vous utilisez une Super Potion !\n");
                            player->superPotion--;
                        } else {
                            printf("Vous n'avez pas de Super Potion.\n");
                        }
                        break;
                    case 3:
                        if (player->rareCandy > 0) {
                            printf("Vous utilisez un Rare Candy !\n");
                            candyLevelUp(ally);  // Utilise le Rare Candy pour faire monter de niveau le Pokémon en combat
                            player->rareCandy--;
                        } else {
                            printf("Vous n'avez pas de Rare Candy.\n");
                        }
                        break;
                    default:
                        printf("Choix invalide.\n");
                        break;
                }
            } break;

            case 4: {  // Capturer
                printf("Vous tentez de capturer %s !\n", wild.name);
                float captureRate = ((float)wild.maxHp - wild.hp) / ((float)wild.maxHp) - 0.5f;
                if (captureRate < 0)
                    captureRate = 0;
                float chance = (float)rand() / (float)RAND_MAX;
                if (chance < captureRate) {
                    printf("Capture réussie ! Vous avez capturé %s !\n", wild.name);
                    player->pokemons[player->numPokemons++] = wild;
                    return;  // Fin du combat
                } else {
                    printf("La capture a échoué.\n");
                }
            } break;

            case 5: {  // Fuir
                printf("Vous tentez de fuir !\n");
                float successRate = (float)ally->speed / ((float)ally->speed + wild.speed);
                float chance = (float)rand() / (float)RAND_MAX;
                if (chance < successRate) {
                    printf("Vous avez réussi à fuir !\n");
                    return;  // Fin du combat
                } else {
                    printf("La fuite a échoué !\n");
                }
            } break;

            default:
                printf("Choix invalide.\n");
                break;
        }

        if (wild.hp <= 0) {
            printf("%s a été vaincu !\n", wild.name);
            int exp_gagnee = (rand() % 51) + 75;
            ally->exp += exp_gagnee;
            printf("%s a gagné %d points d'expérience\n", ally->name, exp_gagnee);
            levelUp(ally);
            break;
        }

        if (wild.hp > 0) {
            printf("%s attaque %s !\n", wild.name, ally->name);
            int damage = calculateDamage(wild.attack, ally->defense);
            ally->hp -= damage;
            if (ally->hp < 0)
                ally->hp = 0;
            printf("Dégâts: %d, HP restant: %d\n", damage, ally->hp);

            if (ally->hp <= 0) {
                printf("Vous avez perdu le combat.\n");
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
        printf("%s est passé au niveau %d !\n", pokemon->name, pokemon->level);
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
    printf("%s est passé au niveau %d grâce au Rare Candy !\n", pokemon->name, pokemon->level);
}


void exploreNature(Player *player) {
    if (player->numPokemons == 0) {
        printf("Vous devez avoir au moins un Pokémon pour explorer.\n");
        return;
    }
    Pokemon wild = generateWildPokemon(player->pokemons[0]);
    battle(player, wild);
}
