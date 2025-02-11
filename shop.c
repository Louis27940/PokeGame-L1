//
// Created by louis on 08/02/2025.
//

#include "shop.h"
#include <stdio.h>
#include "colors.h"


void handleItemTransaction(Player *player, int itemChoice, int isBuying) {
    int price = 0;
    char itemName[MAX_ITEM_NAME];
    int *itemCount = NULL;

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

    if (isBuying) {
        if (player->supcoins >= price) {
            player->supcoins -= price;
            (*itemCount)++;
            printf("Vous avez achete une %s pour %d "YELLOW"Supcoins"RESET".\n", itemName, price);
        } else {
            printf("Vous n'avez pas assez de "YELLOW"Supcoins"RESET" pour acheter une %s.\n", itemName);
        }
    } else {
        if (*itemCount > 0) {
            player->supcoins += price;
            (*itemCount)--;
            printf("Vous avez vendu une %s pour "YELLOW" %d Supcoins.\n"RESET, itemName, price);
        } else {
            printf("Vous n'avez pas de %s a vendre.\n", itemName);
        }
    }
}