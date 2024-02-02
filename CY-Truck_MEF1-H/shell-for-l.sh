#!/bin/bash

# Nom du fichier CSV
INPUT_FILE="data.csv"
# Nom du fichier de sortie
OUTPUT_FILE="output_l.txt"

# Vérifier que le fichier existe
if [ ! -f "$INPUT_FILE" ]; then
    echo "Le fichier $INPUT_FILE n'existe pas."
    exit 1
fi
# Début du chronomètre
start_time=$(date +%s)

# Calculer la somme des distances pour chaque trajet
# Note : La distance est dans la 5ème colonne, l'identifiant de la route est dans la 1ère colonne
awk -F';' '{ distance[$1] += $5 } END { for (trajet in distance) print trajet, distance[trajet] }' "$INPUT_FILE" |
    sort -nrk2 | # Tri par distance décroissante
    head -n 10 |  # Garder les 10 premières lignes
    sort -nrk1 > "$OUTPUT_FILE"  # Redirection vers le fichier de sortie et tri final par identifiant de trajet croissant

# Fin du chronomètre
end_time=$(date +%s)

# Calcul de la durée d'exécution
echo "Durée d'exécution: $((end_time - start_time)) secondes."
