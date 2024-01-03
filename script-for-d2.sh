#!/bin/bash

# Nom du fichier CSV
CSV_FILE="data.csv"

# Vérifie si le fichier CSV existe
if [ ! -f "$CSV_FILE" ]; then
    echo "Le fichier $CSV_FILE n'existe pas."
    exit 1
fi

# Début du chronomètre
start_time=$(date +%s)

# Calcul de la distance totale parcourue par chaque conducteur
awk -F ';' '
BEGIN {
    OFMT = "%.2f";  # Format de sortie pour les nombres à virgule
}
{
    if (NR > 1) {  
        gsub(",", ".", $5);
        conducteur[$6] += $5;  # Accumuler la distance
    }
}
END {
    for (c in conducteur) {
        print conducteur[c], c;  # Affiche la distance totale et le nom du conducteur
    }
}' "$CSV_FILE" | sort -nr | head -10

# Fin du chronomètre
end_time=$(date +%s)

# Calcul de la durée d'exécution
echo "Durée d'exécution: $((end_time - start_time)) secondes."
