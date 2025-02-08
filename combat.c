//
// Created by louis on 08/02/2025.
//
#include "combat.h"
#include <stdio.h>
#include <stdlib.h>

// On définit ici la puissance de base d'une attaque.
#define BASE_MOVE_DAMAGE 50

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

void battle(Player *player, Pokemon wild) {
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
        printf("3 - Fuir\n");
        printf("4 - Capturer\n");
        scanf("%d", &action);

        switch (action) {
            case 1:  // Attaquer
            {
                int damage = calculateDamage(ally->attack, wild.defense);
                wild.hp -= damage;
                if (wild.hp < 0)
                    wild.hp = 0;
                printf("Vous attaquez %s ! Dégâts: %d, HP restant: %d\n",
                       wild.name, damage, wild.hp);
            }
            break;
            case 2:  // Esquiver
            {
                printf("Vous tentez d'esquiver !\n");
                /* Calcul du taux d'esquive selon la formule :
                   dodgeRate = (Launcher_Accuracy / (Launcher_Accuracy + Target_Evasion)) + 0.1 */
                float dodgeRate = (float)wild.accuracy / ((float)wild.accuracy + (float)ally->evasion) + 0.1f;
                if (dodgeRate > 1.0f)
                    dodgeRate = 1.0f;  // On limite la probabilité à 100%
                float chance = (float)rand() / (float)RAND_MAX;
                if (chance < dodgeRate) {
                    printf("Esquive réussie ! Vous évitez l'attaque ennemie.\n");
                    /* L'attaque ennemie est annulée pour ce tour */
                    continue;
                } else {
                    printf("Esquive échouée !\n");
                }
            }
            break;
            case 3:  // Fuir
            {
                printf("Vous tentez de fuir !\n");
                float successRate = (float)ally->speed / ((float)ally->speed + wild.speed);
                float chance = (float)rand() / (float)RAND_MAX;
                if (chance < successRate) {
                    printf("Vous avez réussi à fuir !\n");
                    return;  // Fin du combat
                } else {
                    printf("La fuite a échoué !\n");
                }
            }
            break;
            case 4:  // Capturer
            {
                printf("Vous tentez de capturer %s !\n", wild.name);
                /* Calcul du taux de capture selon la formule :
                   captureRate = ((Enemy_MaxHP - Enemy_HP) / Enemy_MaxHP) - 0.5 */
                float captureRate = ((float)wild.maxHp - wild.hp) / ((float)wild.maxHp) - 0.5f;
                if (captureRate < 0)
                    captureRate = 0;  // Aucune chance de capture si la formule donne une valeur négative
                float chance = (float)rand() / (float)RAND_MAX;
                if (chance < captureRate) {
                    printf("Capture réussie ! Vous avez capturé %s !\n", wild.name);
                    player->pokemons[player->numPokemons++] = wild;  // Clonage du Supémon ennemi
                    return;  // Fin du combat par capture
                } else {
                    printf("La capture a échoué.\n");
                }
            }
            break;
            default:
                printf("Choix invalide.\n");
                break;
        }

        if (wild.hp <= 0) {
            printf("%s a été vaincu !\n", wild.name);
            int exp_gagnee = (rand() % 51) + 75;  // XP gagnée
            ally->exp += exp_gagnee;
            printf("%s a gagné %d points d'expérience\n", ally->name, exp_gagnee);
            levelUp(ally);  // Vérifier si le Pokémon monte de niveau
            break;
        }

        // Tour du Pokémon sauvage (s'il est toujours en vie)
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
    // Vérifie si rawDamage est déjà entier
    if (rawDamage == (float)lower) {
        return lower;
    } else {
        // 50% de chance de retourner lower ou lower + 1
        if (rand() % 2 == 0)
            return lower;
        else
            return lower + 1;
    }
}

void levelUp(Pokemon *pokemon) {
    int exp_needed = 500 + (pokemon->level - 1) * 1000;  // XP requise pour le prochain niveau
    while (pokemon->exp >= exp_needed) {
        pokemon->exp -= exp_needed;  // Réduction de l'XP après passage de niveau
        pokemon->level++;
        exp_needed += 1000;  // Mise à jour de l'XP nécessaire pour le niveau suivant
        // Augmentation des stats
        pokemon->maxHp = (int)(pokemon->maxHp * 1.3);
        pokemon->attack = (int)(pokemon->attack * 1.3);
        pokemon->defense = (int)(pokemon->defense * 1.3);
        pokemon->hp = pokemon->maxHp; // Soins
        printf("%s est passé au niveau %d !\n", pokemon->name, pokemon->level);
    }
}

void exploreNature(Player *player) {
    if (player->numPokemons == 0) {
        printf("Vous devez avoir au moins un Pokémon pour explorer.\n");
        return;
    }

    // Utiliser le premier Pokémon du joueur pour générer le Pokémon sauvage
    Pokemon wild = generateWildPokemon(player->pokemons[0]);
    battle(player, wild);
}
