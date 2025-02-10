//
// Created by louis on 10/02/2025.
//

#include "joueur.h"
#include "colors.h"
#include <string.h>


const char *getTypeColor(const Pokemon *p) {
    if (strcmp(p->type, "Fire") == 0) {
        return RED;
    }
    else if (strcmp(p->type, "Water") == 0) {
        return BLUE;
    }
    else if (strcmp(p->type, "Grass") == 0) {
        return GREEN;
    }
    else if (strcmp(p->type, "Electric") == 0) {
        return YELLOW;
    }
    else if (strcmp(p->type, "Normal") == 0) {
        return WHITE;
    }
    else if (strcmp(p->type, "Poison") == 0) {
        return MAGENTA;
    }
    else if (strcmp(p->type, "Ground") == 0) {
        return BROWN;
    }
    else {
        return RESET; // Par défaut, pas de couleur spéciale
    }
}