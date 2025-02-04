//
// Created by louis on 08/02/2025.
//

#ifndef SAVE_H
#define SAVE_H

#include "joueur.h"
/* sauvegarde username.txt*/
void saveGameText(const Player *player, const char *username);

/*charge username.txt*/
int loadGameText(Player *player, const char *username);

#endif //SAVE_H
