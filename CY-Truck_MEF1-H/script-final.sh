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

    

    # Calcul du temps d'exécution
    start_time=$(date +%s)
    
    # Utilisation d'awk pour compter les trajets par conducteur en évitant les duplicatas
    # Utilisation d'awk pour compter les trajets par conducteur en évitant les duplicatas
    grep '^[^;]*;1;' "$fichier_csv" | cut -d';' -f6 | sort | uniq -c | sort -k1,1nr | head -n 10 > temp/output_d1.txt
    gnuplot d1.gp

    # Affichage du temps d'exécution
    end_time=$(date +%s)
    elapsed_time=$((end_time - start_time))
    echo "Temps d'exécution du traitement D1 : $elapsed_time secondes"

    
elif [ "$option" == "-d2" ]; then
    gcc -o temp/exect-d2 progc/d2.c
    ./temp/exect-d2 "$fichier_csv"
    gnuplot d1.gp
elif [ "$option" == "-l" ]; then
    # Traitement L : Conducteurs avec le plus long trajets
    echo "Traitement L : Les plus long trajets"
    # Calculer la somme des distances pour chaque trajet
    # Note : La distance est dans la 5ème colonne, l'identifiant de la route est dans la 1ère colonne
    awk -F';' '{ distance[$1] += $5 } END { for (trajet in distance) print trajet, distance[trajet] }' "$Fichier_csv" |
    sort -nrk2 | # Tri par distance décroissante
    head -n 10 |  # Garder les 10 premières lignes
    sort -nrk1   # Tri final par identifiant de trajet croissant
    

    # Calcul du temps d'exécution
    start_time=$(date +%s)



    # Affichage du temps d'exécution
    end_time=$(date +%s)
    elapsed_time=$((end_time - start_time))
    echo "Temps d'exécution du traitement L : $elapsed_time secondes"
elif [ "$option" == "-s" ]; then 
    #traitement de S : 
    cut -d';' -f1,2,5 "$fichier_csv" > temp/s1.csv
    tail -n +2 temp/s1.csv > temp/s2.csv
    gcc -o temp/exect progc/S.c 
    ./temp/exect temp/s2.csv
    head -n 50 temp/sortie.csv > temp/s.csv
else
    echo "Option non reconnue : $option"
    exit 3
fi

exit 0