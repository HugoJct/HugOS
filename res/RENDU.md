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

## Sujet 

Nous voulions comprendre le plus en profondeur possible le fonctionnement d'un 
système d'exploitation de type UNIX à un niveau très bas. Mous avons donc décidé 
d'entreprendre la réalisation une implémentation minimale en partant de zéro 
avec pour objectif d'arriver le plus loin possible.

## État initial du projet

Nous ne sommes pas exactement partis de zéro car Hugo avait déjà entrepris
d'écrire un noyau UNIX et nous sommes donc repartis de son travail existant.
Cette base de travail contenait déjà tous les mécanismes permettant de charger 
un programme en mémoire depuis GRUB. Ce programme s'occupait, au lancement, de 
mettre en place de la segmentation et d'installer les mécanismes de gestion des
interruptions aussi bien logicielles que matérielles. Il était donc possible 
d'afficher du texte à l'écran (cela permettait de contrôler que tout se 
déroulait correctement) ainsi que de saisir du texte qui était ensuite affiché 
sans possiblité de récupérer l'entrée afin de s'en servir dans un programme.

## Exécution de programme externe au noyau 

La première étape a été de pouvoir exécuter du code externe au noyau. C'est 
ainsi que sont exécutés les programmes appartenant à l'utilisateur dans 
les systèmes de type UNIX. La décision ayant été prise de ne pas utiliser de 
mode utilisateur, il suffit de connaitre l'adresse à laquelle le code du 
programme a été chargé pour pouvoir exécuter celui-ci.
