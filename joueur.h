//
// Created by louis on 08/02/2025.
//

#ifndef JOUEUR_H
#define JOUEUR_H

#define MAX_POKEMONS 10
#define MAX_TYPE 10
#define MAX_ATTACKS 4

typedef struct {
    char name[20];
    int damage;
    int effect_attack;
    int effect_defence;
    int effect_evasion;
} Attack;

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
    char type[MAX_TYPE];
    Attack attacks[MAX_ATTACKS];
    int numAttacks;
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
