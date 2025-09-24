#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define nbElem 1000
#define nbFois 1000000

void genererTableau(int tab[], int n) {
    for (int i = 0; i < n; i++) tab[i] = rand() % 1000;
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

int rechercheIterative(int tab[], int n, int valeur) {
    for (int i = 0; i < n; i++) if (tab[i] == valeur) return 1;
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
    int tab[nbElem], tabTrie[nbElem];
    genererTableau(tab, nbElem);
    for (int i = 0; i < nbElem; i++) tabTrie[i] = tab[i];
    trierTableau(tabTrie, nbElem);
    Noeud* racine = construireABR(tabTrie, 0, nbElem - 1);

    double tempsSeq = 0, tempsDicho = 0, tempsABR = 0;
    int valeur = -1;

    for (int essai = 0; essai < 10; essai++) {
        clock_t debut, fin;

        debut = clock();
        for (int i = 0; i < nbFois; i++) rechercheIterative(tab, nbElem, valeur);
        fin = clock();
        tempsSeq += (double)(fin - debut) / CLOCKS_PER_SEC;

        debut = clock();
        for (int i = 0; i < nbFois; i++) rechercheDichotomique(tabTrie, nbElem, valeur);
        fin = clock();
        tempsDicho += (double)(fin - debut) / CLOCKS_PER_SEC;

        debut = clock();
        for (int i = 0; i < nbFois; i++) rechercheABR(racine, valeur);
        fin = clock();
        tempsABR += (double)(fin - debut) / CLOCKS_PER_SEC;
    }

    printf("Temps moyen (pire cas) recherche iterative : %lf sec\n", tempsSeq / 10);
    printf("Temps moyen (pire cas) recherche dichotomique : %lf sec\n", tempsDicho / 10);
    printf("Temps moyen (pire cas) recherche ABR : %lf sec\n", tempsABR / 10);

    return 0;
}
