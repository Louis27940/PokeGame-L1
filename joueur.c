//
// Created by louis on 08/02/2025.
//

#include "joueur.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "combat.h"
#include "shop.h"
#include "colors.h"

void showInventory(Player *player, Pokemon *ally) {
    printf("Votre inventaire:\n");
    printf(CYAN"Potion: %d\n"RESET, player->potion);
    printf(GREEN"Super Potion: %d\n"RESET, player->superPotion);
    printf(RED"Rare Candy: %d\n"RESET, player->rareCandy);
    printf(YELLOW"Supcoins: %d\n"RESET, player->supcoins);
    printf("Souhaitez vous utiliser un "RED"Rare Candy"RESET" sur votre pokemon actif ? (o/n) :");
    char choice;
    scanf(" %c", &choice);
    switch (choice) {
        case 'o':
            if (player->rareCandy > 0) {
                printf("Vous utilisez un "RED"Rare Candy"RESET" !\n");
                candyLevelUp(ally);  // Utilise le Rare Candy pour faire monter de niveau le Pokémon en combat
                player->rareCandy--;
            } else {
                printf("Vous n'avez pas de "RED"Rare Candy"RESET".\n");
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
        printf("=== Votre equipe de Pokemon ===\n");
        for (int i = 0; i < player->numPokemons; i++) {
            // Vérifie si c'est le Pokémon actif
            int isActive = (i == player->activePokemonIndex);

            // Affichage du nom avec une icône si actif
            printf("\n[%d] %s%s%s %s\n",
                   i + 1,
                   getTypeColor(&player->pokemons[i]),
                   player->pokemons[i].name,
                   RESET,
                   isActive ? " (Actif)" : "");

            // Affichage des statistiques
            printf("  -> HP: %d/%d\n", player->pokemons[i].hp, player->pokemons[i].maxHp);
            printf("  -> Attaque: %d\n", player->pokemons[i].attack);
            printf("  -> Defense: %d\n", player->pokemons[i].defense);
            printf("  -> Vitesse: %d\n", player->pokemons[i].speed);
            printf("  -> Accuracie: %d\n", player->pokemons[i].accuracy);
            printf("  -> Evasion: %d\n", player->pokemons[i].evasion);
            printf("  -> Niveau: %d\n", player->pokemons[i].level);
            printf("  -> Exp: %d\n", player->pokemons[i].exp);

            // Séparateur sauf pour le dernier Pokémon
            if (i < player->numPokemons - 1) {
                printf("-----------------------------------\n");
            }
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
        printf("%s%s%s a ete soignee ! HP retablis a %d.\n", getTypeColor(&player->pokemons[i]), player->pokemons[i].name, RESET, player->pokemons[i].hp);
    }
}