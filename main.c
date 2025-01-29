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
    Pokemon starter;

    // Définir les Pokémon starters
    Pokemon charmander = {"Charmander", 39, 52, 43};
    Pokemon squirtle = {"Squirtle", 44, 48, 65};
    Pokemon bulbasaur = {"Bulbasaur", 45, 49, 49};

    // Demande du nom d'utilisateur
    printf("Please enter your username: ");
    scanf("%19s", Username);

    printf("Bienvenue %s dans le monde Pokémon!\n", Username);

    // Menu
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

    return 0;
}
