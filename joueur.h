//
// Created by louis on 08/02/2025.
//

#ifndef JOUEUR_H
#define JOUEUR_H

#define MAX_POKEMONS 10

typedef struct {
    char name[20];
    int hp;
    int maxHp;
    int attack;
    int defense;
    int speed;
    int accuracy;
    int evasion;
    int level;
    int exp;
} Pokemon;

typedef struct {
    int potion;
    int superPotion;
    int rareCandy;
    int supcoins;
    Pokemon pokemons[MAX_POKEMONS];
    int numPokemons;
} Player;

void showInventory(Player *player, Pokemon *ally);
void showPokemons(Player *player);
void healPokemons(Player *player);


#endif //JOUEUR_H
