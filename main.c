#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 20
#define MAX_SAVE_NAME 50
#define MAX_ITEM_NAME 20
#define MAX_POKEMONS 10  // Nombre maximal de Pokemon

typedef struct {
    char name[20];
    int hp;
    int attack;
    int defense;
} Pokemon;

typedef struct {
    int potion;
    int superPotion;
    int rareCandy;
    int supcoins;
    Pokemon pokemons[MAX_POKEMONS];  // Tableau de Pokemon
    int numPokemons;  // Nombre de Pokemon captures
} Player;

void buyItem(Player *player, int itemChoice) {
    int price = 0;
    char itemName[MAX_ITEM_NAME];

    switch (itemChoice) {
        case 1:
            price = 100;
            strcpy(itemName, "Potion");
            if (player->supcoins >= price) {
                player->supcoins -= price;
                player->potion++;
                printf("Vous avez achete une %s pour %d Supcoins.\n", itemName, price);
            } else {
                printf("Vous n'avez pas assez de Supcoins pour acheter une %s.\n", itemName);
            }
            break;
        case 2:
            price = 300;
            strcpy(itemName, "Super Potion");
            if (player->supcoins >= price) {
                player->supcoins -= price;
                player->superPotion++;
                printf("Vous avez achete une %s pour %d Supcoins.\n", itemName, price);
            } else {
                printf("Vous n'avez pas assez de Supcoins pour acheter une %s.\n", itemName);
            }
            break;
        case 3:
            price = 700;
            strcpy(itemName, "Rare Candy");
            if (player->supcoins >= price) {
                player->supcoins -= price;
                player->rareCandy++;
                printf("Vous avez achete une %s pour %d Supcoins.\n", itemName, price);
            } else {
                printf("Vous n'avez pas assez de Supcoins pour acheter une %s.\n", itemName);
            }
            break;
        default:
            printf("Choix invalide.\n");
            break;
    }
}

void sellItem(Player *player, int itemChoice) {
    int price = 0;
    char itemName[MAX_ITEM_NAME];

    switch (itemChoice) {
        case 1:
            price = 50;
            strcpy(itemName, "Potion");
            if (player->potion > 0) {
                player->supcoins += price;
                player->potion--;
                printf("Vous avez vendu une %s pour %d Supcoins.\n", itemName, price);
            } else {
                printf("Vous n'avez pas de %s a vendre.\n", itemName);
            }
            break;
        case 2:
            price = 150;
            strcpy(itemName, "Super Potion");
            if (player->superPotion > 0) {
                player->supcoins += price;
                player->superPotion--;
                printf("Vous avez vendu une %s pour %d Supcoins.\n", itemName, price);
            } else {
                printf("Vous n'avez pas de %s a vendre.\n", itemName);
            }
            break;
        case 3:
            price = 350;
            strcpy(itemName, "Rare Candy");
            if (player->rareCandy > 0) {
                player->supcoins += price;
                player->rareCandy--;
                printf("Vous avez vendu une %s pour %d Supcoins.\n", itemName, price);
            } else {
                printf("Vous n'avez pas de %s a vendre.\n", itemName);
            }
            break;
        default:
            printf("Choix invalide.\n");
            break;
    }
}

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
            printf("  HP: %d\n", player->pokemons[i].hp);
            printf("  Attaque: %d\n", player->pokemons[i].attack);
            printf("  Defense: %d\n\n", player->pokemons[i].defense);
        }
    }
}

int main() {
    char Username[MAX_USERNAME];
    int starterChoice;
    int Location = 0;
    int Save;
    int choiceBuyorSell;
    int itemChoice;
    char saveName[MAX_SAVE_NAME];
    Player player = {0, 0, 0, 0, {}, 0};  // Commencer avec 0 Supcoins et aucun Pokemon

    Pokemon charmander = {"Charmander", 39, 52, 43};
    Pokemon squirtle = {"Squirtle", 44, 48, 65};
    Pokemon bulbasaur = {"Bulbasaur", 45, 49, 49};

    printf("Veuillez entrer votre nom d'utilisateur : ");
    scanf("%19s", Username);

    // Verifier si l'utilisateur est ADMIN
    if (strcmp(Username, "ADMIN") == 0) {
        player.supcoins = 999999;  // Si c'est ADMIN, lui donner 999999 Supcoins
        player.potion = 20;        // Donner 20 Potions
        player.superPotion = 20;   // Donner 20 Super Potions
        player.rareCandy = 20;     // Donner 20 Rare Candies
    } else {
        player.supcoins = 0;  // Sinon, les autres utilisateurs commencent avec 0 Supcoins
    }

    printf("Bienvenue %s dans le monde Pokemon !\n", Username);

    printf("+-----------------------------------+\n");
    printf("|                                   |\n");
    printf("|       Choisir votre starter       |\n");
    printf("|                                   |\n");
    printf("|       1 - Charmander              |\n");
    printf("|       2 - Squirtle                |\n");
    printf("|       3 - Bulbasaur               |\n");
    printf("|                                   |\n");
    printf("+-----------------------------------+\n");
    printf("Entrez le numero de votre choix (1, 2 ou 3) : ");
    scanf("%d", &starterChoice);

    switch (starterChoice) {
        case 1:
            player.pokemons[player.numPokemons++] = charmander;
            break;
        case 2:
            player.pokemons[player.numPokemons++] = squirtle;
            break;
        case 3:
            player.pokemons[player.numPokemons++] = bulbasaur;
            break;
        default:
            printf("Choix invalide. Aucun Pokemon selectionne.\n");
            return 0;
    }

    printf("Vous avez choisi %s !\n", player.pokemons[player.numPokemons - 1].name);
    printf("Stats : HP = %d, Attaque = %d, Defense = %d\n", player.pokemons[player.numPokemons - 1].hp, player.pokemons[player.numPokemons - 1].attack, player.pokemons[player.numPokemons - 1].defense);
    printf("Bonne chance pour votre aventure, %s !\n", Username);

    while (1) {
        printf("+-------------------------------------+\n");
        printf("|                                     |\n");
        printf("|       Ou voulez-vous aller ?        |\n");
        printf("|                                     |\n");
        printf("|       1 - La nature                 |\n");
        printf("|       2 - Shop                      |\n");
        printf("|       3 - Pokemon Center            |\n");
        printf("|       4 - Voir votre inventaire     |\n");
        printf("|       5 - Voir vos Pokemon          |\n");
        printf("|       6 - Quitter le Jeu            |\n");
        printf("|                                     |\n");
        printf("+-------------------------------------+\n");
        printf("Entrez votre choix (1, 2, 3, 4, 5 ou 6) : ");
        scanf("%d", &Location);

        switch (Location) {
            case 1:
                printf("Vous entrez dans la nature.\n");
                break;
            case 2:
                printf("Vous entrez dans le Shop.\n");
                showInventory(&player);
                printf("Souhaitez-vous acheter ou vendre ? 1 - Acheter, 2 - Vendre : ");
                scanf("%d", &choiceBuyorSell);
                if (choiceBuyorSell == 1) {
                    printf("1 - Potion (100 Supcoins)\n");
                    printf("2 - Super Potion (300 Supcoins)\n");
                    printf("3 - Rare Candy (700 Supcoins)\n");
                    printf("Choisissez l'objet a acheter (1, 2, 3) : ");
                    scanf("%d", &itemChoice);
                    buyItem(&player, itemChoice);
                } else if (choiceBuyorSell == 2) {
                    printf("1 - Potion\n");
                    printf("2 - Super Potion\n");
                    printf("3 - Rare Candy\n");
                    printf("Choisissez l'objet a vendre (1, 2, 3) : ");
                    scanf("%d", &itemChoice);
                    sellItem(&player, itemChoice);
                }
                break;
            case 3:
                printf("Vous entrez dans le Pokemon Center.\n");
                break;
            case 4:
                showInventory(&player);
                break;
            case 5:
                showPokemons(&player);  // Afficher tous les Pokemon du joueur
                break;
            case 6:
                printf("Voulez-vous sauvegarder avant de quitter ? 1 - Oui, 2 - Non : ");
                scanf("%d", &Save);
                if (Save == 1) {
                    printf("Entrez le nom de la sauvegarde : ");
                    scanf("%s", saveName);

                    FILE *file = fopen(saveName, "w");
                    if (file != NULL) {
                        fprintf(file, "Username: %s\n", Username);
                        fprintf(file, "Pokemons: %d\n", player.numPokemons);
                        for (int i = 0; i < player.numPokemons; i++) {
                            fprintf(file, "Pokemon %d: %s\n", i + 1, player.pokemons[i].name);
                            fprintf(file, "Stats: HP = %d, Attaque = %d, Defense = %d\n", player.pokemons[i].hp, player.pokemons[i].attack, player.pokemons[i].defense);
                        }
                        fclose(file);
                        printf("Le jeu a ete sauvegarde avec succes dans %s.\n", saveName);
                    } else {
                        printf("Erreur lors de la sauvegarde du jeu.\n");
                    }
                }
                printf("Vous avez quitte le Jeu. A bientot !\n");
                return 0;
        }
    }

    return 0;
}
