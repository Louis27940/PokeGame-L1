#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "joueur.h"
#include "combat.h"
#include "shop.h"
#include "save.h"

#define MAX_USERNAME 20

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define RESET "\x1B[0m"

int main() {
    srand(time(NULL));
    char Username[MAX_USERNAME];
    int starterChoice;
    int Location = 0;
    int choiceBuyorSell;
    int itemChoice;
    int option;
    Player player = {0, 0, 0, 0, {}, 0};


    Pokemon charmander = {RED "Charmander"RESET , 10, 10, 1, 1, 1, 2, 1, 1, 0};
    Pokemon squirtle = {BLUE "Squirtle" RESET , 9, 9, 1, 1, 2, 2, 3, 1, 0};
    Pokemon bulbasaur = {GREEN "Bulbasaur"RESET , 11, 11, 1, 2, 2, 1, 2, 1, 0};

    printf("Bienvenue dans le jeu Pokemon !\n");
    printf("1. Nouvelle partie\n2. Charger une sauvegarde\nVotre choix : ");
    if (scanf("%d", &option) != 1) {
        fprintf(stderr, "Entrée invalide.\n");
        return 1;
    }

    while(getchar() != '\n');  // Vider le buffer

    if (option == 2) {
        printf("Entrez votre nom d'utilisateur (nom de la sauvegarde) : ");
        scanf("%19s", Username);
        while(getchar() != '\n');

        if (!loadGameText(&player, Username)) {
            printf("La sauvegarde n'a pas pu être chargee. Une nouvelle partie sera cree.\n");
            /* Initialisation par défaut pour une nouvelle partie */
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

        /* Initialisation par défaut pour une nouvelle partie */
        player.supcoins = 100;
        player.potion = 5;
        player.superPotion = 2;
        player.rareCandy = 1;
        player.numPokemons = 0;

        /* Ici, vous pouvez ajouter la sélection d'un starter, etc. */
    }

    if (strcmp(Username, "ADMIN") == 0) {
        player.supcoins = 999999;
        player.potion = 99;
        player.superPotion = 99;
        player.rareCandy = 99;
    }

    printf("Bienvenue %s dans le monde Pokemon !\n", Username);
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
            printf("|      [1] "RED"Charmander"RESET"  (Feu)             |\n");
            printf("|      [2] "BLUE"Squirtel"RESET"    (Eau)             |\n");
            printf("|      [3] "GREEN"Bulbasaur"RESET"   (Plante)          |\n");
            printf("|                                        |\n");
            printf("+----------------------------------------+\n");
            printf("Votre choix : ");

            result = scanf("%d", &starterChoice);
            if (result != 1) {
                printf("Entrée invalide !\n");
                while (getchar() != '\n'); // On vide le buffer
                continue; // On redemande la saisie
            }

            // Valider la plage de valeurs (ici, il semble que seuls 1 à 3 soient valides)
            if (starterChoice < 1 || starterChoice > 3) {
                printf("Choix invalide ! Veuillez sélectionner un nombre entre 1 et 3.\n");
                continue; // On redemande la saisie
            }

            // Traitement du choix valide
            switch (starterChoice) {
                case 1:
                    player.pokemons[player.numPokemons++] = charmander;
                printf("Vous avez choisi "RED"Charmander"RESET" !\n");
                break;
                case 2:
                    player.pokemons[player.numPokemons++] = squirtle;
                printf("Vous avez choisi "BLUE"Squirtle"RESET" !\n");
                break;
                case 3:
                    player.pokemons[player.numPokemons++] = bulbasaur;
                printf("Vous avez choisi "GREEN"Bulbasaur"RESET" !\n");
                break;
            }
            break; // Sortir de la boucle après un choix valide
        }
    }




    while (1) {
        printf("\n");
        printf("+-------------------------------------+\n");
        printf("|                                     |\n");
        printf("|  [1] Explorer la nature             |\n");
        printf("|  [2] Boutique                       |\n");
        printf("|  [3] Inventaire                     |\n");
        printf("|  [4] Liste des Pokemons             |\n");
        printf("|  [5] Centre Pokemon                 |\n");
        printf("|  [6] Quitter le jeu                 |\n");
        printf("|                                     |\n");
        printf("+-------------------------------------+\n");
        printf("Votre choix : ");

        result = scanf("%d", &Location);
        if (result != 1) {
            printf("Entree invalide ! Veuillez entrer un nombre.\n");
            while (getchar() != '\n'); // Vider le buffer
            continue;
        }

        if (Location < 1 || Location > 6) {
            printf("Choix invalide ! Veuillez selectionner un nombre entre 1 et 6.\n");
            continue;
        }

        // Traitement du choix...
        switch (Location) {
            case 1:
                exploreNature(&player);
            break;
            case 2:
                printf("1 - Acheter | 2 - Vendre\n");
            scanf("%d", &choiceBuyorSell);
            printf("1 - Potion | 2 - Super Potion | 3 - Rare Candy\n");
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