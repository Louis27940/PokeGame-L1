//
// Created by louis on 08/02/2025.
//

#include "save.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void saveGameText(const Player *player, const char *username) {
    char filename[100];
    /* On construit le nom de fichier, par exemple "Alice.txt" */
    snprintf(filename, sizeof(filename), "%s.txt", username);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sauvegarde");
        return;
    }

    /* On écrit le nom d'utilisateur sur la première ligne */
    fprintf(fp, "%s\n", username);

    /* On écrit les informations du joueur sur la deuxième ligne :
       supcoins, potion, superPotion, rareCandy, numPokemons */
    fprintf(fp, "%d %d %d %d %d\n",
            player->supcoins,
            player->potion,
            player->superPotion,
            player->rareCandy,
            player->numPokemons);

    /* Pour chaque pokémon, on écrit ses informations sur une ligne */
    for (int i = 0; i < player->numPokemons; i++) {
         Pokemon p = player->pokemons[i];
         fprintf(fp, "%s %d %d %d %d %d %d %d %d %d\n",
                 p.name, p.hp, p.maxHp, p.attack, p.defense,
                 p.speed, p.accuracy, p.evasion, p.level, p.exp);
    }

    fclose(fp);
    printf("Sauvegarde effectuée dans le fichier '%s'.\n", filename);
}

int loadGameText(Player *player, const char *username) {
    char filename[100];
    snprintf(filename, sizeof(filename), "%s.txt", username);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
         perror("Erreur lors de l'ouverture du fichier de sauvegarde");
         return 0;
    }

    char fileUsername[100];
    /* Lecture de la première ligne : le nom d'utilisateur */
    if (fscanf(fp, "%99s", fileUsername) != 1) {
         fclose(fp);
         return 0;
    }

    /* Lecture des informations du joueur */
    if (fscanf(fp, "%d %d %d %d %d",
           &player->supcoins,
           &player->potion,
           &player->superPotion,
           &player->rareCandy,
           &player->numPokemons) != 5) {
         fclose(fp);
         return 0;
    }

    /* Limiter le nombre de pokémons à MAX_POKEMONS */
    if (player->numPokemons > MAX_POKEMONS) {
         player->numPokemons = MAX_POKEMONS;
    }

    /* Lecture des informations pour chaque pokémon */
    for (int i = 0; i < player->numPokemons; i++) {
         if (fscanf(fp, "%19s %d %d %d %d %d %d %d %d %d",
                    player->pokemons[i].name,
                    &player->pokemons[i].hp,
                    &player->pokemons[i].maxHp,
                    &player->pokemons[i].attack,
                    &player->pokemons[i].defense,
                    &player->pokemons[i].speed,
                    &player->pokemons[i].accuracy,
                    &player->pokemons[i].evasion,
                    &player->pokemons[i].level,
                    &player->pokemons[i].exp) != 10) {
             fclose(fp);
             return 0;
         }
    }

    fclose(fp);
    printf("Sauvegarde chargée depuis le fichier '%s'.\n", filename);
    return 1;
}
