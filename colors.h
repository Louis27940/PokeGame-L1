//
// Created by louis on 10/02/2025.
//

#ifndef COLORS_H
#define COLORS_H

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define BROWN "\x1B[38;5;94m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"
#define RESET "\x1B[0m"
const char *getTypeColor(const Pokemon *p);

#endif //COLORS_H