//
// Created by louis on 08/02/2025.
//

#include "save.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void saveGameText(const Player *player, const char *username) {
    char filename[100];
    snprintf(filename, sizeof(filename), "%s.txt", username);

    FILE *fp = fopen(filename, "w+");
    if (fp == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sauvegarde");
        return;
    }

    fprintf(fp, "%s\n", username);

    //joueur
    fprintf(fp, "%d %d %d %d %d\n",
            player->supcoins,
            player->potion,
            player->superPotion,
            player->rareCandy,
            player->numPokemons);
    fprintf(fp, "%d\n", player->activePokemonIndex);
    //supemons
    for (int i = 0; i < player->numPokemons; i++) {
        Pokemon p = player->pokemons[i];
        fprintf(fp, "%s %s %d %d %d %d %d %d %d %d %d %d\n",
                p.name, p.type, p.hp, p.maxHp, p.attack, p.defense,
                p.speed, p.accuracy, p.evasion, p.level, p.exp, p.numAttacks);

        //attaques
        for (int j = 0; j < p.numAttacks; j++) {
            Attack a = p.attacks[j];
            fprintf(fp, "%s %d %d %d %d\n",
                    a.name, a.damage, a.effect_attack, a.effect_defence, a.effect_evasion);
        }
    }

    fclose(fp);
    printf("Sauvegarde effectuee dans le fichier '%s'.\n", filename);
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
    if (fscanf(fp, "%19s", fileUsername) != 1) {
        fclose(fp);
        return 0;
    }

    if (fscanf(fp, "%d %d %d %d %d",
               &player->supcoins,
               &player->potion,
               &player->superPotion,
               &player->rareCandy,
               &player->numPokemons) != 5) {
        fclose(fp);
        return 0;
    }

    if (player->numPokemons > MAX_POKEMONS) {
        player->numPokemons = MAX_POKEMONS;
    }
    if (fscanf(fp, "%d", &player->activePokemonIndex) != 1) {
        fclose(fp);
        return 0;
    }

    for (int i = 0; i < player->numPokemons; i++) {
        Pokemon *p = &player->pokemons[i];

        if (fscanf(fp, "%19s %9s %d %d %d %d %d %d %d %d %d %d",
                   p->name, p->type, &p->hp, &p->maxHp, &p->attack,
                   &p->defense, &p->speed, &p->accuracy, &p->evasion,
                   &p->level, &p->exp, &p->numAttacks) != 12 ) {
            fclose(fp);
            return 0;
        }

        if (p->numAttacks > MAX_ATTACKS) {
            p->numAttacks = MAX_ATTACKS;
        }

        for (int j = 0; j < p->numAttacks; j++) {
            if (fscanf(fp, "%19s %d %d %d %d",
                       p->attacks[j].name,
                       &p->attacks[j].damage,
                       &p->attacks[j].effect_attack,
                       &p->attacks[j].effect_defence,
                       &p->attacks[j].effect_evasion) != 5) {
                fclose(fp);
                return 0;
            }
        }
    }

    fclose(fp);
    printf("Sauvegarde chargee depuis le fichier '%s'.\n", filename);
    printf("Joueur: %s | Supcoins: %d | Pokemon Actif: %s\n",
       fileUsername, player->supcoins, player->pokemons[player->activePokemonIndex].name);

    return 1;
}
