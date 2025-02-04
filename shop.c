//
// Created by louis on 08/02/2025.
//

#include "shop.h"
#include <stdio.h>

void handleItemTransaction(Player *player, int itemChoice, int isBuying) {
    int price = 0;
    char itemName[MAX_ITEM_NAME];
    int *itemCount = NULL;

    // Assign the appropriate item details based on the choice
    switch (itemChoice) {
        case 1:
            price = 100;
        snprintf(itemName, MAX_ITEM_NAME, "Potion");
        itemCount = &player->potion;
        break;
        case 2:
            price = 300;
        snprintf(itemName, MAX_ITEM_NAME, "Super Potion");
        itemCount = &player->superPotion;
        break;
        case 3:
            price = 700;
        snprintf(itemName, MAX_ITEM_NAME, "Rare Candy");
        itemCount = &player->rareCandy;
        break;
        default:
            printf("Choix invalide.\n");
        return;
    }

    // Process buying or selling
    if (isBuying) {
        if (player->supcoins >= price) {
            player->supcoins -= price;
            (*itemCount)++;
            printf("Vous avez achete une %s pour %d Supcoins.\n", itemName, price);
        } else {
            printf("Vous n'avez pas assez de Supcoins pour acheter une %s.\n", itemName);
        }
    } else {
        if (*itemCount > 0) {
            player->supcoins += price;
            (*itemCount)--;
            printf("Vous avez vendu une %s pour %d Supcoins.\n", itemName, price);
        } else {
            printf("Vous n'avez pas de %s a vendre.\n", itemName);
        }
    }
}