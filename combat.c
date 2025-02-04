//
// Created by louis on 08/02/2025.
//

#include "combat.h"
#include <stdio.h>
#include <stdlib.h>

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
    printf("Stats du %s: HP: %d/%d, Attaque: %d, Defense: %d, Vitesse: %d\n", wild.name, wild.hp, wild.maxHp, wild.attack, wild.defense, wild.speed);

    int flee = 0;
    while (ally->hp > 0 && wild.hp > 0 && !flee) {
        int action; // Déclaration de la variable action ici

        // Tour du joueur
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
                    if (wild.hp < 0) wild.hp = 0;
                    printf("Vous attaquez %s ! Degats: %d, HP restant: %d\n", wild.name, damage, wild.hp);
                }
                break;
            case 2:  // Esquiver
                printf("Vous tentez d'esquiver !\n");
                if (rand() % 2 == 0) {
                    printf("Esquive reussie !\n");
                    continue; // Si l'esquive réussit, on passe à la prochaine itération sans subir de dégâts
                } else {
                    printf("Esquive echouee.\n");
                }
                break;
            case 3:  // Fuir
                printf("Vous tentez de fuir !\n");
                flee = 1;
                break;
            case 4:  // Capturer
                printf("Vous tentez de capturer %s !\n", wild.name);
                if (rand() % 3 == 0) {
                    printf("%s a ete capture !\n", wild.name);
                    player->pokemons[player->numPokemons++] = wild;
                    wild.hp = 0;
                } else {
                    printf("La capture a echoue.\n");
                }
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }

        if (wild.hp <= 0) {
            printf("%s a ete vaincu !\n", wild.name);
            int exp_gagnee = (rand() % 51) + 75;  // XP gagnée
            ally->exp += exp_gagnee;
            printf("%s a gagne %d points d'experience\n", ally->name, exp_gagnee);
            levelUp(ally);  // Vérifier si le Pokémon monte de niveau
            break;
        }

        // Tour du Pokémon sauvage
        if (wild.hp > 0) { // Vérifier si le Pokémon sauvage est toujours en vie
            printf("%s attaque %s !\n", wild.name, ally->name);
            int damage = calculateDamage(wild.attack, ally->defense);
            ally->hp -= damage;
            if (ally->hp < 0) ally->hp = 0;
            printf("Degats: %d, HP restant: %d\n", damage, ally->hp);

            if (ally->hp <= 0) {
                printf("Vous avez perdu le combat.\n");
                break;
            }
        }
    }
}

int calculateDamage(int attack, int defense) {
    int damage = (attack - (defense / 2)) / 2;
    return damage < 0 ? 0 : damage;
}

void levelUp(Pokemon *pokemon) {
    int exp_needed = 500 + (pokemon->level - 1) * 1000;  // Exp requise pour le prochain niveau
    while (pokemon->exp >= exp_needed) {
        pokemon->exp -= exp_needed;  // Réduction de l'XP après passage de niveau
        pokemon->level++;
        exp_needed += 1000;  // Mise à jour de l'XP nécessaire pour le niveau suivant
        // Augmentation des stats
        pokemon->maxHp = (int)(pokemon->maxHp * 1.3);
        pokemon->attack = (int)(pokemon->attack * 1.3);
        pokemon->defense = (int)(pokemon->defense * 1.3);
        pokemon->hp = pokemon->maxHp; // Soins
        printf("%s est passe au niveau %d !\n", pokemon->name, pokemon->level);
    }
}

void exploreNature(Player *player) {
    if (player->numPokemons == 0) {
        printf("Vous devez avoir au moins un Pokemon pour explorer.\n");
        return;
    }

    // Utiliser le premier Pokémon du joueur pour générer le Pokémon sauvage
    Pokemon wild = generateWildPokemon(player->pokemons[0]);
    battle(player, wild);
}