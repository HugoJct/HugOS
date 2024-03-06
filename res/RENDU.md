# Systèmes Avancés M2 

## Sommaire

TODO
- expliquer ce qu'est un noyau
- expliquer segmentation
- expliquer mémoire virtuelle 
- expliquer interruptions

## Trinôme
- Hugo Jacotot 71802786
- Matthieu Le Franc 71800858
- David Andrawos 21955132

---

## Sujet 

Nous voulions comprendre le plus en profondeur possible le fonctionnement d'un 
système d'exploitation de type UNIX à un niveau très bas. 

Nous avons donc décidé d'entreprendre la réalisation d'une implémentation 
minimale d'un noyau en partant de zéro avec pour objectif d'arriver le plus loin 
possible.

---

### Qu'est-ce qu'un noyau ?

TODO

---

## État initial du projet

Nous ne sommes pas exactement partis de zéro car Hugo avait déjà entrepris
d'écrire un noyau UNIX et nous sommes donc repartis de son travail existant.

Cette base de travail contenait déjà tous les mécanismes permettant de charger 
un programme en mémoire depuis GRUB. Ce programme s'occupait, au lancement, de 
mettre en place de la segmentation et d'installer les mécanismes de gestion des
interruptions aussi bien logicielles que matérielles. 

Il était donc possible d'afficher du texte à l'écran (cela permettait de 
contrôler que tout se déroulait correctement) ainsi que de saisir du texte qui 
était ensuite affiché sans possiblité de récupérer l'entrée afin de s'en servir 
dans un programme.

---

### Framebuffer

Le framebuffer permet d'afficher du texte à l'écran en modifiant directement la 
mémoire. Il est constitué de 80 colonnes et de 25 lignes. La zone de la mémoire
correspondant au framebuffer peut être représentée comme un tableau d'entiers
de 16 bits. Chaque case de ce tableau représente un caractère. 

Les 8 premiers bits de chaque case sont utilisés pour stocker le code 
[ASCII](https://fr.wikipedia.org/wiki/American_Standard_Code_for_Information_Interchange) 
du caractère que l'on souhaite imprimer.

Il est également possible de choisir la couleur des caractères ainsi que la 
couleur de l'arrière-plan de ceux-ci. C'est ici que les 8 derniers bits de 
chaque case entrent en jeu:

- les 4 premiers codent la couleur du caractère 
- les 4 suivants codent la couleur de l'arrière-plan du caractère

TODO => image des couleurs et de l'ID correspondant

Pour écrire un caractère à l'écran on peut utiliser le code suivant:

```c

//fb l'adresse de base du framebuffer
//i la position du caractère à écrire 
//bg la couleur d'arrière-plan 
//fg la couleur du caractère
fb[(i * 2) + 1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
```

Dans l'architecture x86, le framebuffer se situe à l'adresse `0xB8000`.

Avec toutes ces informations en main, il est désormais possible d'écrire 
quelques fonctions permettant d'afficher du texte à l'écran facilement (faire en 
sorte que l'écran défile tout seul, retour automatique à la ligne, etc).

---

### Segmentation

### Interrupts

## Avancement du projet 

### Exécution de programme externe au noyau 

La première étape a été de pouvoir exécuter du code externe au noyau. C'est 
ainsi que sont exécutés les programmes appartenant à l'utilisateur dans 
les systèmes de type UNIX. La décision ayant été prise de ne pas utiliser de 
mode utilisateur, il suffit de connaitre l'adresse à laquelle le code du 
programme a été chargé pour pouvoir exécuter celui-ci.
