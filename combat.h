//
// Created by louis on 08/02/2025.
//

#ifndef COMBAT_H
#define COMBAT_H

#include "joueur.h"

Pokemon generateWildPokemon(Pokemon playerPokemon);
void battle(Player *player, Pokemon wild);
int calculateDamage(int attack, int defense);
void levelUp(Pokemon *pokemon);
void exploreNature(Player *player);

#endif //COMBAT_H
