# Projet IS : "RobostrikeIS"

Principalement inspiré du jeu en ligne multijoueurs [Robostrike](http://www.robostrike.com/)(2001) lui même imaginé à partir du jeu de société [RoboRally](https://fr.wikipedia.org/wiki/RoboRally/)(1994), RobostrikeIS permet d'alier action et stratégie.

## Règles du jeu

Lors d’une manche, les joueurs choisissent six actions ordonnées (avancer, reculer, droite, gauche, attaquer, …) avant la fin du temps imparti. Une fois que les joueurs ont tous entré leurs ordres ou que le temps est écoulé, le jeu exécute les actions des joueurs tour par tour. 

### Déplacements

Les joueurs peuvent avancer, reculer, tourner sur eux même et sauter des cases en utilisant des boosts.

### Attaques

Chaque joueur commence la partie avec cinq points de vie et toute attaque entraîne la perte d’un point de vie pour le joueur touché.


## Instalation

### Linux

Une bibliothèque SFML à jour est necssaire

```
 cmake -DBUILD_CODE_COVERAGE=OFF ..
 make -j3
```

### Windows

En cours

```
en cours
```

### Mac OS

En cours
```
demander à Lucas
```


## Sources

* [C++](https://en.wikipedia.org/wiki/C++) - Programmation en C++
* [Serveur](https://maven.apache.org/) - Apache 5.2
* [Guide de l'ENSEA](https://intranet.ensea.fr) - Code de bonne conduite
