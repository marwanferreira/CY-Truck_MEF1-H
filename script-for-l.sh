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

# Calcul de la distance totale pour chaque trajet
awk -F ';' '
BEGIN {
    OFMT = "%.2f";  # Format de sortie pour les nombres à virgule
}
{
    if (NR > 1) {  
        gsub(",", ".", $5);  # Convertir les virgules en points pour les distances
        trajet[$1] += $5;  # Accumuler la distance pour chaque trajet
    }
}
END {
    for (t in trajet) {
        print t, trajet[t];  # Affiche l'ID du trajet et la distance totale
    }
}' "$CSV_FILE" | sort -k2,2nr | head -10 | sort -k1,1n

# Fin du chronomètre
end_time=$(date +%s)

# Calcul de la durée d'exécution
echo "Durée d'exécution: $((end_time - start_time)) secondes."
