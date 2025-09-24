#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define nbElem 10

void genererTableau(int tab[], int n) {
    for (int i = 0; i < n; i++) {
        tab[i] = rand() % 1000;
    }
}

int comparer(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void trierTableau(int tab[], int n) {
    qsort(tab, n, sizeof(int), comparer);
}

typedef struct Noeud {
    int valeur;
    struct Noeud *gauche;
    struct Noeud *droite;
} Noeud;

Noeud* construireABR(int tab[], int debut, int fin) {
    if (debut > fin) return NULL;
    int milieu = (debut + fin) / 2;
    Noeud* racine = (Noeud*) malloc(sizeof(Noeud));
    racine->valeur = tab[milieu];
    racine->gauche = construireABR(tab, debut, milieu - 1);
    racine->droite = construireABR(tab, milieu + 1, fin);
    return racine;
}

void afficherTableau(int tab[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

void afficherArbre(Noeud* racine, int niveau) {
    if (racine == NULL) return;
    afficherArbre(racine->droite, niveau + 1);
    for (int i = 0; i < niveau; i++) printf("   ");
    printf("%d\n", racine->valeur);
    afficherArbre(racine->gauche, niveau + 1);
}

int rechercheIterative(int tab[], int n, int valeur) {
    for (int i = 0; i < n; i++) {
        if (tab[i] == valeur) return 1;
    }
    return 0;
}

int rechercheDichotomique(int tab[], int n, int valeur) {
    int gauche = 0, droite = n - 1;
    while (gauche <= droite) {
        int milieu = (gauche + droite) / 2;
        if (tab[milieu] == valeur) return 1;
        else if (tab[milieu] < valeur) gauche = milieu + 1;
        else droite = milieu - 1;
    }
    return 0;
}

int rechercheABR(Noeud* racine, int valeur) {
    if (racine == NULL) return 0;
    if (racine->valeur == valeur) return 1;
    else if (valeur < racine->valeur) return rechercheABR(racine->gauche, valeur);
    else return rechercheABR(racine->droite, valeur);
}

int main() {
    srand(time(NULL));
    int tab[nbElem];
    int tabTrie[nbElem];
    genererTableau(tab, nbElem);
    printf("Tableau non trie :\n");
    afficherTableau(tab, nbElem);
    for (int i = 0; i < nbElem; i++) tabTrie[i] = tab[i];
    trierTableau(tabTrie, nbElem);
    printf("\nTableau trie :\n");
    afficherTableau(tabTrie, nbElem);
    Noeud* racine = construireABR(tabTrie, 0, nbElem - 1);
    printf("\nArbre binaire recherche:\n");
    afficherArbre(racine, 0);
    int valeurRecherchee;
    printf("\nEntrez une valeur a rechercher : ");
    scanf("%d", &valeurRecherchee);
    printf("Tableau non trie : %s\n", rechercheIterative(tab, nbElem, valeurRecherchee) ? "Trouve" : "Non trouve");
    printf("Tableau trie : %s\n", rechercheDichotomique(tabTrie, nbElem, valeurRecherchee) ? "Trouve" : "Non trouve");
    printf("ABR : %s\n", rechercheABR(racine, valeurRecherchee) ? "Trouve" : "Non trouve");
    return 0;
}
