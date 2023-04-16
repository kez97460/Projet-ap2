# Remerciements

- merci à Antoine Pieren pour avoir récupéré un fichier texte du dictionnaire français et avoir remplacé tous les caractères non-ASCII

# Introduction

Le sujet détaillé du projet se trouve dans le fichier `2023_projet_Algo_Prog_sem_II.pdf`.  

L'ensemble du code de ce projet est écrit et commenté **en anglais**. Seul ce README est écrit en français. 

La suite de ce README a pour objectif d'expliquer les choix qui ont été faits lors de la réalisation du projet. 

# Réalisation
## Structures de données utilisées

### Définition
La principale structure de données utilisée dans ce projet est une variante de l'[*arbre préfixe*](https://fr.wikipedia.org/wiki/Trie_(informatique)), aussi appelé *trie*.

Elle est définie comme ceci :
```c
typedef struct _tree_node
{
    int nb_occ; 
    struct _tree_node* children[NB_CHARS]; 
}tree_node;

typedef tree_node* prefix_tree;
```

On définit ainsi des noeuds constitué d'un nombre d'occurence (*nb_occ*) et d'un tableau de 27 fils, eux même des noeuds.  
Les 27 fils correspondent aux différents symboles présents dans un mot, avec les correspondances suivantes :
- l'indice 0 correspond à `'\0'` (fin de mot)
- les indices 1 à 26 correspondent aux lettres de l'albhabet (a=1, b=2 ...)

On définit ensuite un arbre par sa racine, un pointeur vers un noeud.

Lors de l'ajout et suppression de mots, on prendra soin de maintenir vraie la propriété suivante :

| **Propriété** |
|---|
| Pur tout noeud d'un arbre, le nombre d'occurences de ce noeud est égal au maximum des nombres d'occurences des mots passant par ce noeud. |

---
### Fonctions de base

Pour utiliser cette structure de données, plusieurs fonctions de base ont été créées.

D'abord, 2 fonctions pour ajouter un mot :
```c
int add_word(prefix_tree root, char* word)
void update_word(prefix_tree root, char* word, int new_number)
```

`add_word` crée les noeuds nécessaires pour le mot, et incrémente le nombre d'occurences **uniquement du `'\0'` à la fin du mot**, puis renvoie ce nombre d'occurences.  
`upadte_word` prend un mot, un nouveau nombre d'occurences (plus grand que l'ancien), et change le nombre d'occurence de **chaque lettre du mot** en conséquence. Si un nombre négatif est donné, la fonction va lire le nb_occ du `'\0'` elle même comme *new_number*.

Une fonction `add_and_update_word(prefix_tree root, char* word)` fait les deux à la suite. La séparation premet d'éventuelles optimisations dans le cas où un même mot est ajouté plusieurs fois au même moment.

Ensuite, une fonction pour supprimer toutes les occurences d'un mot :
```c
int delete_word(prefix_tree root, char* word)
```
Cette fonction renvoie le *nb_occ* du mot supprimé.

Enfin, une fonction qui renvoie le mot avec le plus grand nombre d'occurence (en cas d'égalité, le 1er dans l'ordre alphabétique) :
```c
char* get_most_common_word(prefix_tree root)
```
--- 
### Utilisation dans le projet

Dans ce projet, il fallait créer une application de saisie intuitive.  
Un début de mot est donc donné, et l'algorithme va devoir proposer les $n$ (ici $n$ = 3) mots les plus communs qui commencent par ce préfixe.

Avec la structure définie ci-dessus, le fonctionnement est très simple :
1. Lire le début de mot entré
2. Se déplacer dans l'arbre pour chaque lettre (déplacer une copie de la racine vers le fils correspondant, s'il existe)
3. Choisir les $n$ fins de mots les plus communs dans le sous-arbre dans lequel on se retrouve
4. Le mot complet est alors la concaténation de ce qui est entré et ce qui est donné par l'arbre

Seule l'étape 3 n'est pas évidente avec notre structure de données. En effet on ne peut récupérer que le mot le plus commun, donc un seul.

Pour résoudre ce problème, deux solutions ont été envisagées :
- Au lieu de récupérer le plus commun, trier tous les mots par nombre d'occurence décroissant
- Après avoir récupéré un mot, le sauvegarder temporairement et le supprimer, puis recommencer

Le tri a une compléxité dépendant de la taille de l'arbre, alors que la suppression est en temps constant (ne dépendant que de la taille des mots).  
De plus $n$ est ici très petit (3), et donc trier des arbres contenant des milliers de mots est clairement inutile.  
Si n était grand la méthode du tri aurait peut être été privilégiée.

Une fonction a donc été créée pour cette étape :
```c
word_array get_most_common_words(prefix_tree root, int nb_words);
```
où le type word_array est simplement un tableau de strings ainsi que son nombre d'éléments.

--- 
### Avantages

Cette structure de données est très efficace pour régler ce problème.

En effet **toutes les fonctions ont une complexité en temps ne dépendant que de la taille d'un mot**, et peuvent donc être considérées en temps constant (les mots français ont une longueur inférieure à 25 lettres).

De plus, si beaucoup de mots sont présents (par exemple un dictionnaire entier), de la mémoire est économisée car des mots ayant les mêmes préfixes partagent des noeuds.

La lecture des mots dans la structure est assez intuitive pour un être humain. Par exemple le code ci-dessous :
```c
root->children[6]->children[5]->children[21]->children[18]->children[0]->nb_occ
```
Correspond au nombre d'occurences du mot `{'f', 'e', 'u', 'r', '\0'}` soit `"feur"` dans l'arbre de racine `root`.  
Il suffit de faire correspondre les nombres à la place de la lettre dans l'alphabet (f est la 6ème lettre...).  
Cette simplicité a grandement aidé à la détection de bugs.


--- 
### Inconvénients, améliorations possibles

Il est actuellement impossible de stocker des mots composés car seuls les caractères \[a-z\] sont supportés par la structure.  
Il serait cependant assez simple de l'étendre pour inclure plus de caractères (il suffit de modifier le nombre de fils, et la fonction qui transforme les char en un indice). 
