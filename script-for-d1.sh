#!/bin/bash

# Nom du fichier CSV
CSV_FILE="data.csv"

# Vérifie si le fichier CSV existe
if [ ! -f "$CSV_FILE" ]; then
    echo "Le fichier $CSV_FILE n'existe pas."
    exit 1
fi
echo "debut du script"
# Début du chronomètre
start_time=$(date +%s)

# Extrait les données, en évitant de compter plusieurs fois le même Route ID pour un conducteur
awk -F ';' '
{
    route_driver_pair = $1 ":" $6  # Crée une paire unique Route ID:Nom du Conducteur
    if (!(route_driver_pair in counted_pairs)) {
        counted_pairs[route_driver_pair] = 1  # Marque la paire comme comptée
        conducteur[$6]++  # Incrémente le compteur pour ce conducteur
    }
}
END {
    for (c in conducteur) {
        print conducteur[c] " " c  # Affiche le nombre de trajets uniques et le nom du conducteur
    }
}' "$CSV_FILE" | sort -nr | head -10

# Fin du chronomètre
end_time=$(date +%s)

# Calcul de la durée d'exécution
echo "Durée d'exécution: $((end_time - start_time)) secondes."
