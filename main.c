#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 20  // Taille maximale du nom d'utilisateur

typedef struct {
    char name[20];
    int hp;
    int attack;
    int defense;
} Pokemon;

int main() {
    char Username[MAX_USERNAME];
    int starterChoice;
    int Location = 0;  // Initialiser Location à 0
    Pokemon starter;

    // Définir les Pokémon starters
    Pokemon charmander = {"Charmander", 39, 52, 43};
    Pokemon squirtle = {"Squirtle", 44, 48, 65};
    Pokemon bulbasaur = {"Bulbasaur", 45, 49, 49};

    // Demande du nom d'utilisateur
    printf("Please enter your username: ");
    scanf("%19s", Username);

    printf("Bienvenue %s dans le monde Pokémon!\n", Username);

    // Menu pour choisir le starter
    printf("+-----------------------------------+\n");
    printf("|                                   |\n");
    printf("|       Choisir votre starter       |\n");
    printf("|                                   |\n");
    printf("|       1 - Charmander              |\n");
    printf("|       2 - Squirtle                |\n");
    printf("|       3 - Bulbasaur               |\n");
    printf("|                                   |\n");
    printf("+-----------------------------------+\n");
    printf("Entrez le numéro de votre choix (1, 2 ou 3) : ");
    scanf("%d", &starterChoice);

    // Assigner le starter choisi
    switch (starterChoice) {
        case 1:
            starter = charmander;
            break;
        case 2:
            starter = squirtle;
            break;
        case 3:
            starter = bulbasaur;
            break;
        default:
            printf("Choix invalide. Aucun Pokémon sélectionné.\n");
            return 0;
    }

    // Afficher les informations du starter choisi
    printf("Vous avez choisi %s !\n", starter.name);
    printf("Stats : HP = %d, Attaque = %d, Défense = %d\n", starter.hp, starter.attack, starter.defense);
    printf("Bonne chance pour votre aventure, %s !\n", Username);

    // Menu des options d'action
    while (1) {
        printf("+-------------------------------------+\n");
        printf("|                                     |\n");
        printf("|       Ou voulez-vous aller ?        |\n");
        printf("|                                     |\n");
        printf("|       1 - La nature                 |\n");
        printf("|       2 - Shop                      |\n");
        printf("|       3 - Pokemon Center            |\n");
        printf("|       4 - Quitter le Jeu            |\n");
        printf("|                                     |\n");
        printf("+-------------------------------------+\n");
        printf("Entrez votre choix (1, 2, 3 ou 4) : ");
        scanf("%d", &Location);

        switch (Location) {
            case 1:
                printf("Vous entrez dans la nature.\n");
                break;
            case 2:
                printf("Vous entrez dans le Shop.\n");
                break;
            case 3:
                printf("Vous entrez dans le Pokémon Center.\n");
                break;
            case 4:
                printf("Vous avez quitté le Jeu. À bientôt !\n");
                return 0; // Quitte le jeu
            default:
                printf("Choix invalide. Essayez encore.\n");
                break;
        }
    }

    return 0;
}
