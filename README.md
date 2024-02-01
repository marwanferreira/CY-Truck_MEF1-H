# Projet de Gestion de Données pour une Société de Transport Routier : CYTRUCK

## Description Générale

Vous êtes le gérant d'une société nationale de transport routier, et vous cherchez à optimiser l'analyse des données de trajets routiers? Ce projet consiste à développer un programme en shell qui analyse un fichier de données volumineux, utilise un programme C pour des traitements spécifiques si nécessaire, puis génère des graphiques résumant les résultats.

## Structure du Projet

L'organisation du projet suit les directives spécifiées dans les consignes :

- **data/** : Ce répertoire contient le fichier CSV d'entrée contenant les données des trajets routiers.

- **progc/** : Ici, vous trouverez les programmes C nécessaires pour le traitement des données, ainsi que leurs fichiers Makefile et l'exécutable généré.

- **images/** : Ce répertoire contiendra les graphiques générés à partir des résultats des traitements.

- **demo/** : Ce répertoire comprend des exemples d'exécution de notre application, notamment des données d'entrée et les résultats de divers traitements.

- **temp/** : Un dossier temporaire où les fichiers intermédiaires nécessaires au traitement sont stockés.

Cette structure facilite la gestion et l'organisation des fichiers du projet CYTRUCK.

## Utilisation du Script Shell

Avant l'utilisation de notre application, veuillez vous accorder les droits d'exécution de l'application dans votre terminal via la commande suivante :

```bash
chmod +x cytruck.sh
