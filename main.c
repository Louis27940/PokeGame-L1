#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "joueur.h"
#include "combat.h"
#include "shop.h"
#include "save.h"
#include "colors.h"

#define MAX_USERNAME 20

int main() {
    srand(time(NULL));
    char Username[MAX_USERNAME];
    int starterChoice;
    int Location = 0;
    int choiceBuyorSell;
    int itemChoice;
    int option;
    Player player = {0, 0, 0, 0, {}, 0};


    Pokemon charmander = {"Supmander" , 10, 10, 1, 1, 1, 2, 1, 1, 0, "Fire"};
    Pokemon squirtle = {"Supirtle" , 9, 9, 1, 1, 2, 2, 3, 1, 0, "Water"};
    Pokemon bulbasaur = {"Supasaur" , 11, 11, 1, 2, 2, 1, 2, 1, 0, "Grass"};

    charmander.attacks[0] = (Attack) {"Scratch", 3, 0,0,0};
    charmander.attacks[1] = (Attack) {"Growl", 0, 1,0,0};
    charmander.numAttacks = 2;

    squirtle.attacks[0] = (Attack) {"Pound", 2, 0,0,0};
    squirtle.attacks[1] = (Attack) {"Shell", 0, 0,1,0};
    squirtle.numAttacks = 2;

    bulbasaur.attacks[0] = (Attack) {"Pound", 2, 0,0,0};
    bulbasaur.attacks[1] = (Attack) {"Foliage", 0, 0,0,1};
    bulbasaur.numAttacks = 2;

    printf("Bienvenue dans le jeu Supemon !\n");
    printf("1. Nouvelle partie\n2. Charger une sauvegarde\nVotre choix : ");
    if (scanf("%d", &option) != 1) {
        fprintf(stderr, "Entree invalide.\n");
        return 1;
    }
    while(getchar() != '\n');  // Vider le buffer

    if (option == 2) {
        printf("Entrez votre nom d'utilisateur (nom de la sauvegarde) : ");
        scanf("%19s", Username);
        while(getchar() != '\n');

        if (!loadGameText(&player, Username)) {
            printf("La sauvegarde n'a pas pu être chargee. Une nouvelle partie sera cree.\n");

            player.supcoins = 100;
            player.potion = 5;
            player.superPotion = 2;
            player.rareCandy = 1;
            player.numPokemons = 0;
        }
    } else {
        printf("Entrez votre nom d'utilisateur : ");
        scanf("%19s", Username);
        while(getchar() != '\n');

        player.supcoins = 100;
        player.potion = 5;
        player.superPotion = 2;
        player.rareCandy = 1;
        player.numPokemons = 0;
    }
    if (strcmp(Username, "ADMIN") == 0) {
        player.supcoins = 999999;
        player.potion = 99;
        player.superPotion = 99;
        player.rareCandy = 99;
    }
    printf("Bienvenue %s dans le monde Supemon !\n", Username);
    int result;
    if (player.numPokemons == 0) {
        while (1) {
            printf("\n");
            printf("+----------------------------------------+\n");
            printf("|            "YELLOW"~~~* * * * *~~~"RESET"             |\n");
            printf("|         CHOISISSEZ UN STARTER          |\n");
            printf("|            "YELLOW"~~~* * * * *~~~"RESET"             |\n");
            printf("+----------------------------------------+\n");
            printf("|                                        |\n");
            printf("|      [1] "RED"Supmander"RESET"  (Feu)             |\n");
            printf("|      [2] "BLUE"Supirtel"RESET"    (Eau)             |\n");
            printf("|      [3] "GREEN"Supasaur"RESET"   (Plante)          |\n");
            printf("|                                        |\n");
            printf("+----------------------------------------+\n");
            printf("Votre choix : ");

            result = scanf("%d", &starterChoice);
            if (result != 1) {
                printf("Entrée invalide !\n");
                while (getchar() != '\n');
                continue;
            }
            if (starterChoice < 1 || starterChoice > 3) {
                printf("Choix invalide ! Veuillez sélectionner un nombre entre 1 et 3.\n");
                continue;
            }
            switch (starterChoice) {
                case 1:
                    player.pokemons[player.numPokemons++] = charmander;
                printf("Vous avez choisi "RED"Suprmander"RESET" !\n");
                break;
                case 2:
                    player.pokemons[player.numPokemons++] = squirtle;
                printf("Vous avez choisi "BLUE"Supirtle"RESET" !\n");
                break;
                case 3:
                    player.pokemons[player.numPokemons++] = bulbasaur;
                printf("Vous avez choisi "GREEN"Supasaur"RESET" !\n");
                break;
            }
            break;
        }
    }

    while (1) {
        printf("\n");
        printf("+-------------------------------------+\n");
        printf("|                                     |\n");
        printf("|  [1] Explorer la nature             |\n");
        printf("|  [2] Boutique                       |\n");
        printf("|  [3] Inventaire                     |\n");
        printf("|  [4] Liste des Supemons             |\n");
        printf("|  [5] Centre Supemon                 |\n");
        printf("|  [6] Quitter le jeu                 |\n");
        printf("|                                     |\n");
        printf("+-------------------------------------+\n");
        printf("Votre choix : ");

        result = scanf("%d", &Location);
        if (result != 1) {
            printf("Entree invalide ! Veuillez entrer un nombre.\n");
            while (getchar() != '\n');
            continue;
        }
        if (Location < 1 || Location > 6) {
            printf("Choix invalide ! Veuillez selectionner un nombre entre 1 et 6.\n");
            continue;
        }
        switch (Location) {
            case 1:
                exploreNature(&player);
            break;
            case 2:
                printf("1 - Acheter | 2 - Vendre\n");
            scanf("%d", &choiceBuyorSell);
            printf(CYAN "1 - Potion "RESET"|"GREEN" 2 - Super Potion "RESET"|"RED" 3 - Rare Candy\n"RESET);
            scanf("%d", &itemChoice);
            handleItemTransaction(&player, itemChoice, (choiceBuyorSell == 1));
            break;
            case 3:
                showInventory(&player, &player.pokemons[0]);
            break;
            case 4:
                showPokemons(&player);
            break;
            case 5:
                healPokemons(&player);
            break;
            case 6:
                printf("Au revoir !\n");
            saveGameText(&player, Username);
            return 0;
            default:
                printf("Choix invalide.\n");
            break ;
        }
    }
    return 0;
}