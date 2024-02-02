# Définition des variables pour les compilateurs et les drapeaux
CC=gcc
CFLAGS=-Wall
droit :
	chmod +x script-final.sh
# Chemin du script shell
SCRIPT = script-final.sh

# Règles pour chaque option
d1:
	@bash $(SCRIPT) data/data.csv -d1

d2:
	@bash $(SCRIPT) data/data.csv -d2

l:
	@bash $(SCRIPT) data/data.csv -l

s:
	@bash $(SCRIPT) data/data.csv -s

t:
	@bash $(SCRIPT) data/data.csv -t

h:
	@bash $(SCRIPT) -h

# Ajoutez d'autres règles si nécessaire

# Nettoyage
clean:
	rm -rf temp/*
	rm -rf images/*

.PHONY: all d1 d2 l s t h run clean
