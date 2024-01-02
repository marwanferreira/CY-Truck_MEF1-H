#!/bin/bash

# Nom du fichier CSV
CSV_FILE="data.csv"

# Vérifie si le fichier CSV existe
if [ ! -f "$CSV_FILE" ]; then
    echo "Le fichier $CSV_FILE n'existe pas."
    exit 1
fi
echo "Début du script"
# Début du chronomètre
start_time=$(date +%s)

# Extrait les données, les trie et affiche les 10 premiers conducteurs
awk -F ';' '
{
    conducteur[$6]++  # Incrémente le compteur pour chaque conducteur (en supposant que la 6ème colonne contient les noms des conducteurs)
}
END {
    for (c in conducteur) {
        print conducteur[c] " " c  # Affiche le nombre de trajets et le nom du conducteur
    }
}' "$CSV_FILE" | sort -nr | head -10

# Fin du chronomètre
end_time=$(date +%s)

# Calcul de la durée d'exécution
echo "Durée d'exécution: $((end_time - start_time)) secondes."
