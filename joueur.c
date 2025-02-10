//
// Created by louis on 08/02/2025.
//

#include "joueur.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "combat.h"
#include "shop.h"

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define RESET "\x1B[0m"

void showInventory(Player *player, Pokemon *ally) {
    printf("Votre inventaire:\n");
    printf(BLUE"Potion: %d\n"RESET, player->potion);
    printf(GREEN"Super Potion: %d\n"RESET, player->superPotion);
    printf(RED"Rare Candy: %d\n"RESET, player->rareCandy);
    printf(YELLOW"Supcoins: %d\n"RESET, player->supcoins);
    printf("Souhaitez vous utiliser un bonbon sur votre pokemon actif ? (o/n) :");
    char choice;
    scanf(" %c", &choice);
    switch (choice) {
        case 'o':
            if (player->rareCandy > 0) {
                printf("Vous utilisez un Rare Candy !\n");
                candyLevelUp(ally);  // Utilise le Rare Candy pour faire monter de niveau le Pokémon en combat
                player->rareCandy--;
            } else {
                printf("Vous n'avez pas de Rare Candy.\n");
            }
        break;
        case 'n':
            break;
        default:
            printf("Choix invalide.\n");
        break;
    }
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