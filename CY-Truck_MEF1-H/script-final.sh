#!/bin/bash

# Vérification des arguments
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <chemin_fichier_csv> <option>"
    exit 1
fi

# Récupération de l'argument
fichier_csv="$1"
option="$2"

# Vérification de l'existence du fichier CSV
if [ ! -f "$fichier_csv" ]; then
    echo "Erreur : Le fichier $fichier_csv n'existe pas."
    exit 2
fi

# Vérification de l'existence des dossiers temp et images
mkdir -p temp
mkdir -p images

# Nettoyage du dossier temp
rm -rf temp/*

# Exécution du traitement en fonction de l'option
if [ "$option" == "-d1" ]; then
    # Traitement D1 : Conducteurs avec le plus de trajets
    echo "Traitement D1 : Conducteurs avec le plus de trajets"
    gcc -o temp/exect-d1 progc/d1.c
    ./temp/exect-d1 "$fichier_csv"
    gnuplot gp/d1.gp
    convert -rotate 90 images/option_d1.png images/option_d1.png
    open images/option_d1.png
    
elif [ "$option" == "-d2" ]; then
     echo "TRAITEMENT D2 : conducteurs et la plus grande distance"
    gcc -o temp/exect-d2 progc/d2.c
    ./temp/exect-d2 "$fichier_csv"
    gnuplot gp/d2.gp
    convert -rotate 90 images/option_d2.png images/option_d2.png
    open images/option_d2.png
    
elif [ "$option" == "-l" ]; then
    # Traitement L : Conducteurs avec le plus long trajets
    # Calcul du temps d'exécution
    start_time=$(date +%s)
    echo "Traitement L : Les plus long trajets"
    # Calculer la somme des distances pour chaque trajet
# Note : La distance est dans la 5ème colonne, l'identifiant de la route est dans la 1ère colonne
    awk -F';' '{ distance[$1] += $5 } END { for (trajet in distance) print trajet, distance[trajet] }' "$fichier_csv" |      
    sort -nrk2 | # Tri par distance décroissante
    head -n 10 |  # Garder les 10 premières lignes
    sort -nrk1 > "temp/output-l.txt"  # Redirection vers le fichier de sortie et tri final par identifiant de trajet croissant

    end_time=$(date +%s)
    elapsed_time=$((end_time - start_time))
    echo "Temps d'exécution du traitement L : $elapsed_time secondes"
    gnuplot gp/l.gp
    open images/option_l.png

elif [ "$option" == "-s" ]; then 
    #traitement de S : 
    echo "Traitement S : statistiques sur les étapes"
    cut -d';' -f1,2,5 "$fichier_csv" > temp/s1.csv
    tail -n +2 temp/s1.csv > temp/s2.csv
    gcc -o temp/exect progc/S.c 
    ./temp/exect temp/s2.csv
    head -n 50 temp/sortie.csv > temp/s.txt
    gnuplot gp/s.gp
    open images/option_s.png

elif [ "$option" == "-t" ]; then 
    gcc -o temp/exect progc/t.c
    tail -n +2 $fichier_csv | cut -d';' -f1,2,3,4 | temp/exect > temp/output-t.txt
    gnuplot gp/t.gp
    open images/option_t.png
    

elif [ "$option" == "-h" ]; then
    echo "Bienvenu dans le centre d'aide"
    echo "Les options disponible dans ce programme sont :"
    echo "TRAITEMENT [D1] : conducteurs avec le plus de trajets : option -d1"
    echo "TRAITEMENT [D2] : conducteurs et la plus grande distance: option -d2"
    echo "TRAITEMENT [L] : les 10 trajets les plus longs : option -l"
    echo "TRAITEMENT [T] : les 10 villes les plus traversées : option -t"
    echo "Traitement [S] : statistiques sur les étapes : option -s"


else
    echo "Option non reconnue : $option"
    echo "Si vous voulez connaitre toute les options choisissez l'option -h"
    exit 3
fi



exit 0
