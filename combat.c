//
// Created by louis on 08/02/2025.
//
#include "combat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"


// Affichage stylisé des barres de HP
void printHpBar(Pokemon p) {
    printf(GREEN "[" RESET );
    int hpPercent = (p.hp * 10) / p.maxHp; // Échelle sur 10
    for (int i = 0; i < 10; i++) {
        if (i < hpPercent)
            printf(GREEN "|" RESET );
        else
            printf(RED "|" RESET );
    }
    printf(GREEN "] %d/%d" RESET, p.hp, p.maxHp);
}

    Pokemon generateWildPokemon(Pokemon playerPokemon) {
    char *names[] = {"Pikachu", "Eevee", "Rattata", "Zubat", "Geodude"};
    int index = rand() % 5;

    Pokemon wild = {
        .name = "",
        .level = playerPokemon.level
    };

    wild.maxHp   = playerPokemon.maxHp;
    wild.attack  = playerPokemon.attack + (rand() % 5) - 2;
    if (wild.attack < 1){ wild.attack = 1;}
    wild.defense = playerPokemon.defense + (rand() % 5) - 2;
    if (wild.defense < 1) {wild.defense = 1;}
    wild.speed   = playerPokemon.speed + (rand() % 5) - 2;
    if (wild.speed < 1) {wild.speed = 1;}
    wild.accuracy = (rand() % 5) + 1;
    wild.evasion  = (rand() % 5) + 1;
    wild.exp = 0;

    switch (index) {
        case 0:  // Pikachu
            strcpy(wild.type, "Electric");
            wild.attacks[0] = (Attack){"Eclair", 2, 0, 0, 0};
            wild.attacks[1] = (Attack){"Coup de Queue", 1, 0, 2, 0};
            wild.attacks[2] = (Attack){"Tonnerre", 3, 1, 0, 0};
            wild.attacks[3] = (Attack){"Vive-Attaque", 1, 0, 0, 1};
            wild.numAttacks = 4;
            break;

        case 1:  // Eevee
            strcpy(wild.type, "Normal");
            wild.attacks[0] = (Attack){"Charge", 1, 0, 0, 0};
            wild.attacks[1] = (Attack){"Morsure", 2, 0, 0, 1};
            wild.attacks[2] = (Attack){"Jet de Sable", 0, 0, 0, 2};
            wild.attacks[3] = (Attack){"Coup de Boule", 3, 0, 1, 0};
            wild.numAttacks = 4;
            break;

        case 2:  // Rattata
            strcpy(wild.type, "Poison");
            wild.attacks[0] = (Attack){"Morsure", 3, 0, 0, 0};
            wild.attacks[1] = (Attack){"Vive-Attaque", 1, 0, 0, 1};
            wild.attacks[2] = (Attack){"Hate", 0, 0, 0, 2};
            wild.attacks[3] = (Attack){"Crochet Venin", 2, 1, 0, 0};
            wild.numAttacks = 4;
            break;

        case 3:  // Zubat
            strcpy(wild.type, "Water");
            wild.attacks[0] = (Attack){"Ultrason", 0, 0, 0, 3};
            wild.attacks[1] = (Attack){"Piqure", 1, 0, 0, 0};
            wild.attacks[2] = (Attack){"Aile d'Acier", 3, 1, 0, 0};
            wild.attacks[3] = (Attack){"Morsure", 2, 0, 0, 1};
            wild.numAttacks = 4;
            break;

        case 4:  // Geodude
            strcpy(wild.type, "Ground");
            wild.attacks[0] = (Attack){"Jet-Pierres", 2, 0, 0, 0};
            wild.attacks[1] = (Attack){"Armure", 0, 0, 1, 0};
            wild.attacks[2] = (Attack){"Eboulement", 3, 0, 0, 0};
            wild.attacks[3] = (Attack){"Boul'Armure", 0, 0, 2, 0};
            wild.numAttacks = 4;
            break;

        default:
            strcpy(wild.type, "Normal");
            wild.numAttacks = 0;
            break;

}

    snprintf(wild.name, sizeof(wild.name), "%s", names[index]);
    return wild;
}


void battle(Player *player, Pokemon wild) {
    Pokemon *ally = &player->pokemons[player->activePokemonIndex];

    printf(YELLOW "\n=============================\n");
    printf("Un %s%s%s "YELLOW"sauvage apparait ! Niveau: %d\n", getTypeColor(&wild), wild.name, RESET, wild.level);
    printf("=============================\n" RESET);

    printf(RED "Niveau: %d\n" RESET, wild.level);
    printf("Stats du %s%s%s: ", getTypeColor(&wild), wild.name, RESET);
    printHpBar(wild);
    printf("\nAttaque: %d | Defense: %d | Vitesse: %d\n",
           wild.attack, wild.defense, wild.speed);

    while (ally->hp > 0 && wild.hp > 0) {
        int action;

        printf(BLUE "\n-----------------------------\n");
        printf("Votre tour !\n");
        printf("-----------------------------\n" RESET);

        printf("%s%s%s | ", getTypeColor(ally), ally->name, RESET);
        printHpBar(*ally);
        printf("\n\n");

        printf("1- Attaquer\n");
        printf("2- Changer de Pokemon\n");
        printf("3- Utiliser un objet\n");
        printf("4- Capturer\n");
        printf("5- Fuir\n");
        printf(YELLOW "Choisissez une action: " RESET);

        scanf("%d", &action);

        switch (action) {
            case 1: {
                int attackChoice;
                printf("Choisissez une attaque :\n");
                for (int i = 0; i < ally->numAttacks; i++) {
                    printf("  [%d] %s (Degats: %d, Attaque: +%d, Defence: +%d, Evasion: +%d)\n",
                           i + 1, ally->attacks[i].name, ally->attacks[i].damage, ally->attacks[i].effect_attack, ally->attacks[i].effect_defence, ally->attacks[i].effect_evasion);
                }
                printf("Votre choix : ");
                scanf("%d", &attackChoice);

                if (attackChoice < 1 || attackChoice > ally->numAttacks) {
                    printf("Choix invalide, attaque par defaut utilisee.\n");
                    attackChoice = 1;
                }

                // Récupération de l'attaque choisie
                Attack chosenAttack = ally->attacks[attackChoice - 1];

                int damage = calculateDamage(ally->attack, chosenAttack.damage, wild.defense);

                wild.hp -= damage;
                if (wild.hp < 0)
                    wild.hp = 0;

                printf("Vous utilisez %s !\n",
                        chosenAttack.name);

                if (chosenAttack.effect_attack > 0) {
                    ally->attack += chosenAttack.effect_attack;
                    printf("%s%s%s augmente son attaque de %d points !\n", getTypeColor(ally), ally->name, RESET, chosenAttack.effect_attack);
                }
                else if (chosenAttack.effect_defence > 0) {
                    ally->defense += chosenAttack.effect_defence;
                    printf("%s%s%s augmente sa defence de %d points !\n", getTypeColor(ally), ally->name, RESET, chosenAttack.effect_defence);
                }
                else if (chosenAttack.effect_evasion > 0) {
                    ally->evasion += chosenAttack.effect_evasion;
                    printf("%s%s%s augmente son evasion de %d points !\n", getTypeColor(ally), ally->name, RESET, chosenAttack.effect_evasion);
                }
                printf("Vous attaquez %s%s%s ! Degats: %d ",
                       getTypeColor(&wild), wild.name, RESET, damage);
                printHpBar(wild);
                printf("\n");

            } break;

            case 2: {
                switchActivePokemon(player);
                break;
            } break;

            case 3: {
                int itemChoice;
                int itemUsed = 0;
                if (itemUsed < 5) {
                    printf("Quel objet souhaitez-vous utiliser ?\n");
                    printf(CYAN "1 - Potion (+5 HP) Restant : %d\n" RESET GREEN "2 - Super Potion (+10 HP) Restant : %d\n" RESET RED "3 - Rare Candy (+1 lvl) Restant : %d\n" RESET , player->potion, player->superPotion, player->rareCandy);
                    scanf("%d", &itemChoice);

                    switch (itemChoice) {
                        case 1:
                            if (player->potion > 0) {
                                if (ally->hp + 5 > ally->maxHp) {
                                    ally->hp = ally->maxHp;
                                }
                                else {
                                    ally->hp += 5;
                                }
                                printf("Vous utilisez une "CYAN"Potion"RESET" !\n");
                                player->potion--;
                                itemUsed++;
                            } else {
                                printf("Vous n'avez pas de "CYAN"Potion"RESET".\n");
                            }
                        break;
                        case 2:
                            if (player->superPotion > 0) {
                                if (ally->hp + 10 > ally->maxHp) {
                                    ally->hp = ally->maxHp;
                                }
                                else {
                                    ally->hp += 10;
                                }
                                printf("Vous utilisez une "GREEN"Super Potion"RESET" !\n");
                                player->superPotion--;
                                itemUsed++;
                            } else {
                                printf("Vous n'avez pas de "GREEN"Super Potion"RESET".\n");
                            }
                        break;
                        case 3:
                            if (player->rareCandy > 0) {
                                printf("Vous utilisez un "RED"Rare Candy"RESET" !\n");
                                candyLevelUp(ally);  // Utilise le Rare Candy pour faire monter de niveau le Pokémon en combat
                                player->rareCandy--;
                                itemUsed++;
                            } else {
                                printf("Vous n'avez pas de "RED"Rare Candy"RESET".\n");
                            }
                        break;
                        default:
                            printf("Choix invalide.\n");
                        break;
                    }
                }
            } break;

            case 4: {
                printf("Vous tentez de capturer %s !\n", wild.name);
                float captureRate = ((float)wild.maxHp - wild.hp) / ((float)wild.maxHp) - 0.5f;
                if (captureRate < 0)
                    captureRate = 0;
                float chance = (float)rand() / (float)RAND_MAX;
                if (chance < captureRate) {
                    printf("Capture reussie ! Vous avez capture %s !\n", wild.name);
                    player->pokemons[player->numPokemons++] = wild;
                    return;  // Fin du combat
                } else {
                    printf("La capture a echoue.\n");
                }
            } break;

            case 5: {
                printf("Vous tentez de fuir !\n");
                float successRate = (float)ally->speed / ((float)ally->speed + wild.speed);
                float chance = (float)rand() / (float)RAND_MAX;
                if (chance < successRate) {
                    printf("Vous avez reussi a fuir !\n");
                    return;  // Fin du combat
                } else {
                    printf("La fuite a echoue !\n");
                }
            } break;

            default:
                printf("Choix invalide.\n");
                break;
        }

        if (wild.hp <= 0) {
            printf("%s%s%s a ete vaincu !\n", getTypeColor(&wild), wild.name, RESET);
            int exp_gagnee = (rand() % (500 - 100 + 1)) + 100;
            int coin_gagnee = (rand() % (500 - 100 + 1)) + 100;
            ally->exp += exp_gagnee;
            player->supcoins += coin_gagnee;
            printf("Vous avez gagne %d "YELLOW"Supcoins\n"RESET, coin_gagnee);
            printf("%s%s%s a gagne %d points d'experience\n", getTypeColor(ally), ally->name, RESET, exp_gagnee);
            levelUp(ally);
            break;
        }

        if (wild.hp > 0) {
            printf("%s%s%s attaque %s%s%s !\n",
                   getTypeColor(&wild), wild.name, RESET,
                   getTypeColor(ally), ally->name, RESET);

            if (wild.numAttacks > 0) {
                int randomIndex = rand() % wild.numAttacks;
                Attack wildAttack = wild.attacks[randomIndex];
                printf("%s%s%s utilise %s%s%s !\n",
                       getTypeColor(&wild), wild.name, RESET,
                       getTypeColor(&wild), wildAttack.name, RESET);

                int damage = calculateDamage(wild.attack, wildAttack.damage, ally->defense);
                ally->hp -= damage;
                if (ally->hp < 0)
                    ally->hp = 0;
                printf("Degats infliges : %d, HP restant de %s%s%s : %d\n",
                       damage, getTypeColor(ally), ally->name, RESET, ally->hp);

                if (wildAttack.effect_attack > 0) {
                    wild.attack += wildAttack.effect_attack;
                    printf("%s%s%s augmente son attaque de %d points !\n",
                           getTypeColor(&wild), wild.name, RESET, wildAttack.effect_attack);
                } else if (wildAttack.effect_defence > 0) {
                    wild.defense += wildAttack.effect_defence;
                    printf("%s%s%s augmente sa defense de %d points !\n",
                           getTypeColor(&wild), wild.name, RESET, wildAttack.effect_defence);
                } else if (wildAttack.effect_evasion > 0) {
                    wild.evasion += wildAttack.effect_evasion;
                    printf("%s%s%s augmente son esquive de %d points !\n",
                           getTypeColor(&wild), wild.name, RESET, wildAttack.effect_evasion);
                }
            } else {
                int damage = calculateDamage(wild.attack, 1, ally->defense);
                ally->hp -= damage;
                if (ally->hp < 0)
                    ally->hp = 0;
                printf("Degats infliges (attaque par défaut) : %d, HP restant de %s%s%s : %d\n",
                       damage, getTypeColor(ally), ally->name, RESET, ally->hp);
            }

            if (ally->hp <= 0) {
                printf(RED "Vous avez perdu le combat.\n" RESET);
            }
        }

    }
}

int calculateDamage(int attack, int basse_move_dammage, int defense) {
    float rawDamage = ((float)attack * basse_move_dammage) / (float)defense;
    int lower = (int)rawDamage;
    if (rawDamage == (float)lower) {
        return lower;
    } else {
        if (rand() % 2 == 0)
            return lower;
        else
            return lower + 1;
    }
}

void switchActivePokemon(Player *player) {
    if (player->numPokemons <= 1) {
        printf("Vous n'avez qu'un seul Pokemon, vous ne pouvez pas changer !\n");
        return;
    }

    printf("\nChoisissez un nouveau Pokemon actif :\n");
    for (int i = 0; i < player->numPokemons; i++) {
        printf("[%d] %s (HP: %d/%d)\n", i + 1, player->pokemons[i].name,
               player->pokemons[i].hp, player->pokemons[i].maxHp);
    }

    int choice;
    printf("Entrez le numero du Pokemon (1-%d) : ", player->numPokemons);
    scanf("%d", &choice);

    if (choice < 1 || choice > player->numPokemons) {
        printf("Choix invalide !\n");
        return;
    }

    if (player->pokemons[choice - 1].hp <= 0) {
        printf("Ce Pokemon est K.O. ! Vous ne pouvez pas l'envoyer au combat.\n");
        return;
    }

    player->activePokemonIndex = choice - 1;
    printf("Vous avez choisi %s comme Pokemon actif !\n", player->pokemons[player->activePokemonIndex].name);
}


int roundStat(float value) {
    int lower = (int)value;
    if (value == (float)lower) {
        // La valeur est déjà entière
        return lower;
    } else {
        // 50 % de chance d'arrondir vers le bas, 50 % vers le haut
        if (rand() % 2 == 0)
            return lower;
        else
            return lower + 1;
    }
}


void levelUp(Pokemon *pokemon) {
    int exp_needed = 500 + (pokemon->level - 1) * 1000;
    while (pokemon->exp >= exp_needed) {
        pokemon->exp -= exp_needed;
        pokemon->level++;
        exp_needed += 1000;
        // Mise à jour des stats avec arrondi aléatoire (50% chance de round up)
        pokemon->maxHp   = roundStat(pokemon->maxHp   * 1.3);
        pokemon->attack  = roundStat(pokemon->attack  * 1.3);
        pokemon->defense = roundStat(pokemon->defense * 1.3);
        pokemon->speed   = roundStat(pokemon->speed   * 1.3);
        pokemon->accuracy = roundStat(pokemon->accuracy * 1.3);
        pokemon->evasion  = roundStat(pokemon->evasion  * 1.3);
        pokemon->hp = pokemon->maxHp; // Soins complets après level up
        printf("%s%s%s est passe au niveau %d !\n", getTypeColor(pokemon), pokemon->name, RESET, pokemon->level);
    }
}


void candyLevelUp(Pokemon *pokemon) {
    // Pour un Rare Candy, on fait monter d'un niveau directement
    pokemon->level++;
    // Mise à jour des stats avec arrondi aléatoire (50% chance de round up)
    pokemon->maxHp   = roundStat(pokemon->maxHp   * 1.3);
    pokemon->attack  = roundStat(pokemon->attack  * 1.3);
    pokemon->defense = roundStat(pokemon->defense * 1.3);
    pokemon->speed   = roundStat(pokemon->speed   * 1.3);
    pokemon->accuracy = roundStat(pokemon->accuracy * 1.3);
    pokemon->evasion  = roundStat(pokemon->evasion  * 1.3);
    pokemon->hp = pokemon->maxHp;
    printf("%s%s%s est passe au niveau %d grace au "RED"Rare Candy"RESET" !\n", getTypeColor(pokemon), pokemon->name, RESET, pokemon->level);
}


void exploreNature(Player *player) {
    if (player->pokemons[player->activePokemonIndex].hp <= 0) {
        printf("Vous devez d'abord soigner vos pokemons pour explorer\n");
        return;
    }
    if (player->numPokemons == 0) {
        printf("Vous devez avoir au moins un Pokemon pour explorer.\n");
        return;
    }
    Pokemon wild = generateWildPokemon(player->pokemons[0]);
    battle(player, wild);
}
