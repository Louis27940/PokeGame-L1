#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 20  // Taille maximale du nom d'utilisateur
#define MAX_SAVE_NAME 50  // Taille maximale du nom de la sauvegarde

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
    int Save;
    int Load;
    char saveName[MAX_SAVE_NAME];  // Nom du fichier de sauvegarde
    Pokemon starter;

    // Définir les Pokémon starters
    Pokemon charmander = {"Charmander", 39, 52, 43};
    Pokemon squirtle = {"Squirtle", 44, 48, 65};
    Pokemon bulbasaur = {"Bulbasaur", 45, 49, 49};

    // Demander si l'utilisateur veut charger une sauvegarde
    printf("Voulez-vous charger une sauvegarde ? 1 - Oui, 2 - Non : ");
    scanf("%d", &Load);

    if (Load == 1) {
        // Demander le nom du fichier de sauvegarde à charger
        printf("Entrez le nom de la sauvegarde à charger : ");
        scanf("%s", saveName);

        // Charger la sauvegarde depuis le fichier
        FILE *file = fopen(saveName, "r");
        if (file != NULL) {
            // Lire les informations sauvegardées
            fscanf(file, "Username: %s\n", Username);
            char starterName[20];
            fscanf(file, "Starter: %s\n", starterName);
            fscanf(file, "Stats: HP = %d, Attaque = %d, Défense = %d\n", &starter.hp, &starter.attack, &starter.defense);

            // Assigner le starter à partir du nom lu
            if (strcmp(starterName, "Charmander") == 0) {
                starter = charmander;
            } else if (strcmp(starterName, "Squirtle") == 0) {
                starter = squirtle;
            } else if (strcmp(starterName, "Bulbasaur") == 0) {
                starter = bulbasaur;
            }

            fclose(file);
            printf("Sauvegarde chargée avec succès !\n");
        } else {
            printf("Aucune sauvegarde trouvée. Commencez une nouvelle partie.\n");
        }
    } else {
        // Si l'utilisateur ne veut pas charger de sauvegarde, commencer une nouvelle partie
        printf("Veuillez entrer votre nom d'utilisateur : ");
        scanf("%19s", Username);

        printf("Bienvenue %s dans le monde Pokémon !\n", Username);

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
    }

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
                printf("Voulez-vous sauvegarder avant de quitter ? 1 - Oui, 2 - Non : ");
                scanf("%d", &Save);
                if (Save == 1) {
                    // Demander le nom de la sauvegarde
                    printf("Entrez le nom de la sauvegarde : ");
                    scanf("%s", saveName);

                    // Sauvegarde dans le fichier choisi
                    FILE *file = fopen(saveName, "w");
                    if (file != NULL) {
                        fprintf(file, "Username: %s\n", Username);
                        fprintf(file, "Starter: %s\n", starter.name);
                        fprintf(file, "Stats: HP = %d, Attaque = %d, Défense = %d\n", starter.hp, starter.attack, starter.defense);
                        fclose(file);
                        printf("Le jeu a été sauvegardé avec succès dans %s.\n", saveName);
                    } else {
                        printf("Erreur lors de la sauvegarde du jeu.\n");
                    }
                }
                printf("Vous avez quitté le Jeu. À bientôt !\n");
                return 0; // Quitte le jeu
            default:
                printf("Choix invalide. Essayez encore.\n");
                break;
        }
    }

    return 0;
}
