#!/bin/bash

echo "Choisissez le programme à compiler :"
echo "1. d1-in-c.c"
echo "2. d2-in-c.c"
read -p "Entrez le numéro du programme (1 ou 2): " choice

# Définition des noms de fichier source et exécutable
SOURCE1="d1-in-C.c"
EXECUTABLE1="d1"
SOURCE2="d2-in-c.c"
EXECUTABLE2="d2"

# Fonction de compilation
compile_and_run() {
    gcc $1 -o $2
    if [ $? -eq 0 ]; then
        echo "Compilation réussie. Exécution du programme..."
        ./$2
    else
        echo "La compilation a échoué."
    fi
    gnuplot d1.gp
}

# Sélection du programme à compiler
case $choice in
    1)
        compile_and_run $SOURCE1 $EXECUTABLE1
        ;;
    2)
        compile_and_run $SOURCE2 $EXECUTABLE2
        ;;
    *)
        echo "Choix non valide."
        ;;
esac
