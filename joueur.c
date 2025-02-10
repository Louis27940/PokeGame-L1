//
// Created by louis on 08/02/2025.
//

#include "joueur.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void showInventory(Player *player) {
    printf("Votre inventaire:\n");
    printf("Potion: %d\n", player->potion);
    printf("Super Potion: %d\n", player->superPotion);
    printf("Rare Candy: %d\n", player->rareCandy);
    printf("Supcoins: %d\n", player->supcoins);
}

void showPokemons(Player *player) {
    if (player->numPokemons == 0) {
        printf("Vous n'avez pas encore de Pokemon.\n");
    } else {
        printf("Voici vos Pokemon:\n");
        for (int i = 0; i < player->numPokemons; i++) {
            printf("Pokemon %d: %s\n", i + 1, player->pokemons[i].name);
            printf("  HP: %d/%d\n", player->pokemons[i].hp, player->pokemons[i].maxHp);
            printf("  Attaque: %d\n", player->pokemons[i].attack);
            printf("  Defense: %d\n", player->pokemons[i].defense);
            printf("  Vitesse: %d\n", player->pokemons[i].speed);
            printf("  Accuracie: %d\n", player->pokemons[i].accuracy);
            printf("  Evasion: %d\n", player->pokemons[i].evasion);
            printf("  Niveau: %d\n", player->pokemons[i].level);
            printf("  Exp: %d\n\n", player->pokemons[i].exp);
        }
    }
}

void healPokemons(Player *player) {
    if (player->numPokemons == 0) {
        printf("Vous n'avez pas encore de Pokemon à soigner.\n");
        return;
    }

    for (int i = 0; i < player->numPokemons; i++) {
        player->pokemons[i].hp = player->pokemons[i].maxHp;  // Remise à jour des HP au maximum
        printf("%s a ete soignee ! HP retablis a %d.\n", player->pokemons[i].name, player->pokemons[i].hp);
    }
}