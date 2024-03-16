cmake_minimum_required(VERSION 3.10)
project(prog)

# Spécifiez le chemin du répertoire contenant les fichiers d'en-tête SDL2
set(SDL2_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/SDL2")

# Spécifiez le chemin du répertoire contenant les bibliothèques SDL2
set(SDL2_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/lib")

# Spécifiez le chemin du répertoire contenant les fichiers d'en-tête SCRITCH
set(SCRITCH_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

# Liste des fichiers sources
set(SOURCES
    src/main.c
    src/project.c
    src/TxUtils.c
    src/node.c
    src/button.c
)

# Création de l'exécutable
add_executable(prog ${SOURCES})

# Inclusion des répertoires d'en-tête
include_directories(${SDL2_INCLUDE_DIR} ${SCRITCH_INCLUDE_DIR})

# Lien des bibliothèques SDL2
target_link_directories(prog PRIVATE ${SDL2_LIBRARY_DIR})
target_link_libraries(prog PRIVATE SDL2main SDL2)

add_definitions(-DSDL_MAIN_HANDLED)
