cmake_minimum_required(VERSION 3.26)
project(PokeGame)

set(CMAKE_C_STANDARD 11)

# Ajoutez tous les fichiers source ici :
add_executable(main
        main.c
        joueur.c
        combat.c
        shop.c
        save.c
        colors.c
)