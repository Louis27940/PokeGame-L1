#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 20
#define MAX_SAVE_NAME 50
#define MAX_ITEM_NAME 20
#define MAX_POKEMONS 10

typedef struct {
    char name[20];
    int hp;
    int maxHp;  // Ajout de maxHp pour stocker les HP maximum
    int attack;
    int defense;
    int speed;
    int accuracy;
    int evasion;
} Pokemon;

typedef struct {
    int potion;
    int superPotion;
    int rareCandy;
    int supcoins;
    Pokemon pokemons[MAX_POKEMONS];
    int numPokemons;
} Player;

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
            printf("  HP: %d/%d\n", player->pokemons[i].hp, player->pokemons[i].maxHp);  // Affiche les HP actuels et max
            printf("  Attaque: %d\n", player->pokemons[i].attack);
            printf("  Defense: %d\n\n", player->pokemons[i].defense);
        }
    }
}

Pokemon generateWildPokemon() {
    char *names[] = {"Pikachu", "Eevee", "Rattata", "Zubat", "Geodude"};
    int index = rand() % 5;

    int hp_values[] = {35, 40, 30, 30, 45};
    int attack_values[] = {55, 52, 56, 45, 60};
    int defense_values[] = {30, 50, 35, 45, 60};

    Pokemon wild = {
        .name = "",
        .hp = hp_values[index],
        .maxHp = hp_values[index],  // Initialiser maxHp
        .attack = attack_values[index],
        .defense = defense_values[index],
        .speed = (rand() % 10) + 5,
        .accuracy = (rand() % 5) + 1,
        .evasion = (rand() % 5) + 1
    };

    snprintf(wild.name, sizeof(wild.name), "%s", names[index]);
    return wild;
}

int calculateDamage(int attack, int defense) {
    int damage = attack - (defense / 2);
    return damage < 0 ? 0 : damage;  // Les dégâts ne peuvent pas être négatifs
}

void battle(Player *player, Pokemon wild) {
    Pokemon *ally = &player->pokemons[0];
    printf("Un %s sauvage apparait !\n", wild.name);

    int flee = 0;
    while (ally->hp > 0 && wild.hp > 0 && !flee) {
        printf("\nVotre tour !\n");
        printf("Que voulez-vous faire ?\n");
        printf("1 - Attaquer\n");
        printf("2 - Esquiver\n");
        printf("3 - Fuir\n");
        printf("4 - Capturer\n");
        int action;
        scanf("%d", &action);

        switch (action) {
            case 1:  // Attaquer
                int damage = calculateDamage(ally->attack, wild.defense);
                wild.hp -= damage;
                if (wild.hp < 0) wild.hp = 0;  // S'assurer que les HP du Pokémon sauvage ne sont pas inférieurs à 0
                printf("Vous attaquez %s ! Degats: %d, HP restant: %d\n", wild.name, damage, wild.hp);
                break;
            case 2:  // Esquiver
                printf("Vous tentez d'esquiver !\n");
                if (rand() % 2 == 0) {
                    printf("Esquive reussie !\n");
                } else {
                    printf("Esquive echouee.\n");
                }
                break;
            case 3:  // Fuir
                printf("Vous tentez de fuir !\n");
                flee = 1;
                break;
            case 4:  // Capturer
                printf("Vous tentez de capturer %s !\n", wild.name);
                if (rand() % 3 == 0) {  // Chance de capture
                    printf("%s a ete capture !\n", wild.name);
                    player->pokemons[player->numPokemons++] = wild;
                    wild.hp = 0;  // Le combat se termine si le pokemon est capturé
                } else {
                    printf("La capture a echoue.\n");
                }
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }

        if (wild.hp <= 0) {
            printf("%s a ete vaincu !\n", wild.name);
            break;
        }

        if (flee) {
            printf("Vous avez fui le combat !\n");
            break;
        }

        // Tour de l'ennemi
        if (!flee) {
            int damage = calculateDamage(wild.attack, ally->defense);
            ally->hp -= damage;
            if (ally->hp < 0) ally->hp = 0;  // S'assurer que les HP du Pokémon du joueur ne sont pas inférieurs à 0
            printf("%s attaque %s ! Degats: %d, HP restant: %d\n", wild.name, ally->name, damage, ally->hp);
        }
    }

    if (ally->hp <= 0) {
        printf("Vous avez perdu le combat.\n");
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

void exploreNature(Player *player) {
    if (player->numPokemons == 0) {
        printf("Vous devez avoir au moins un Pokemon pour explorer.\n");
        return;
    }

    Pokemon wild = generateWildPokemon();
    battle(player, wild);
}

int main() {
    char Username[MAX_USERNAME];
    int starterChoice;
    int Location = 0;
    int choiceBuyorSell;
    int itemChoice;
    Player player = {0, 0, 0, 0, {}, 0};

    Pokemon charmander = {"Charmander", 39, 39, 52, 43, 65, 100, 100};
    Pokemon squirtle = {"Squirtle", 44, 44, 48, 65, 43, 100, 100};
    Pokemon bulbasaur = {"Bulbasaur", 45, 45, 49, 49, 45, 100, 100};

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
        printf("|       1 - Explorer la nature        |\n");
        printf("|       2 - Acheter des objets        |\n");
        printf("|       3 - Vendre des objets         |\n");
        printf("|       4 - Afficher votre inventaire |\n");
        printf("|       5 - Afficher vos Pokemons     |\n");
        printf("|       6 - Centre Pokemon            |\n");
        printf("|       7 - Quitter                   |\n");
        printf("|                                     |\n");
        printf("+-------------------------------------+\n");
        printf("Entrez votre choix : ");
        scanf("%d", &Location);

        switch (Location) {
            case 1:
                exploreNature(&player);
                break;
            case 2:
                printf("Voulez-vous acheter ou vendre ?\n");
                printf("1 - Acheter\n");
                printf("2 - Vendre\n");
                scanf("%d", &choiceBuyorSell);
                if (choiceBuyorSell == 1) {
                    printf("Que voulez-vous acheter ?\n");
                    printf("1 - Potion (100 Supcoins)\n");
                    printf("2 - Super Potion (300 Supcoins)\n");
                    printf("3 - Rare Candy (700 Supcoins)\n");
                    scanf("%d", &itemChoice);
                    handleItemTransaction(&player, itemChoice, 1);
                } else if (choiceBuyorSell == 2) {
                    printf("Que voulez-vous vendre ?\n");
                    printf("1 - Potion\n");
                    printf("2 - Super Potion\n");
                    printf("3 - Rare Candy\n");
                    scanf("%d", &itemChoice);
                    handleItemTransaction(&player, itemChoice, 0);
                } else {
                    printf("Choix invalide.\n");
                }
                break;
            case 3:
                printf("Que voulez-vous vendre ?\n");
                printf("1 - Potion\n");
                printf("2 - Super Potion\n");
                printf("3 - Rare Candy\n");
                scanf("%d", &itemChoice);
                handleItemTransaction(&player, itemChoice, 0);
                break;
            case 4:
                showInventory(&player);
                break;
            case 5:
                showPokemons(&player);
                break;
            case 6:
                printf("Bienvenue au Centre Pokemon !\n");
                healPokemons(&player);
                break;
            case 7:
                printf("Merci d'avoir joue. À bientôt !\n");
                return 0;
            default:
                printf("Choix invalide.\n");
        }
    }
}