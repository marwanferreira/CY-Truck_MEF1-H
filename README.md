# CYTRUCK_MEF1-H


## Prérequis

Avant de commencer à utiliser ou à compiler ce projet, vous devez installer GNUplot et ImageMagick. Ces outils sont nécessaires pour la génération de graphiques et la manipulation d'images.

### Installation sur macOS

Pour installer GNUplot et ImageMagick sur macOS, vous pouvez utiliser Homebrew avec les commandes suivantes :

```bash
 brew install gnuplot
 brew install imagemagick
```

### Installation sur Ubuntu

Ouvrez le terminal et exécutez les commandes suivantes:

```bash
# Mise à jour de la liste des paquets
sudo apt-get update

# Installation de Gnuplot
sudo apt-get install gnuplot

# Installation de ImageMagick
sudo apt-get install imagemagick
```

## Description Générale

Vous êtes le gérant d'une société nationale de transport routier, et vous cherchez à optimiser l'analyse des données de trajets routiers? Ce projet consiste à développer un programme en shell qui analyse un fichier de données volumineux, utilise un programme C pour des traitements spécifiques si nécessaire, puis génère des graphiques résumant les résultats.

## Structure du Projet

L'organisation du projet suit les directives spécifiées dans les consignes :

- **data/** : Ce répertoire contient le fichier CSV d'entrée contenant les données des trajets routiers.

- **gp/** : Ce repertoire continient tous les codes necessaire a la gestion des images/graphique.
  
- **progc/** : Ici, vous trouverez les programmes C nécessaires pour le traitement des données, ainsi que leurs fichiers Makefile et l'exécutable généré.

- **images/** : Ce répertoire contiendra les graphiques générés à partir des résultats des traitements.

- **demo/** : Ce répertoire comprend des exemples d'exécution de notre application, notamment des données d'entrée et les résultats de divers traitements.

- **temp/** : Un dossier temporaire où les fichiers intermédiaires nécessaires au traitement sont stockés.

Cette structure facilite la gestion et l'organisation des fichiers du projet CYTRUCK.

## Utilisation du Script Shell

Avant l'utilisation de notre application, veuillez vous accorder les droits d'exécution de l'application dans votre terminal via la commande suivante :

```bash
chmod +x script-final.sh
./script-final.sh <chemin de votre fichier de donnée> <option voulu>
```
## Utilisation du Script Shell

Le script shell prend en paramètres le chemin du fichier CSV d'entrée et les choix de traitements à effectuer. Voici les options disponibles :

- **-h** : Affiche l'aide expliquant les options disponibles.
- **-d1** : Traite les conducteurs avec le plus de trajets.
- **-d2** : Traite les conducteurs avec la plus grande distance parcourue.
- **-l** : Traite les 10 trajets les plus longs.
- **-t** : Traite les 10 villes les plus traversées.
- **-s** : Traite les statistiques sur les étapes.


