#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define nbElem 1000

typedef struct Noeud {
    int valeur;
    struct Noeud* gauche;
    struct Noeud* droite;
} Noeud;


Noeud* creerNoeud(int valeur) {
    Noeud* nouveau = (Noeud*)malloc(sizeof(Noeud));
    nouveau->valeur = valeur;
    nouveau->gauche = NULL;
    nouveau->droite = NULL;
    return nouveau;
}

Noeud* inserer(Noeud* racine, int valeur) {
    if (racine == NULL) {
        return creerNoeud(valeur);
    }
    
    if (valeur < racine->valeur) {
        racine->gauche = inserer(racine->gauche, valeur);
    } else if (valeur > racine->valeur) {
        racine->droite = inserer(racine->droite, valeur);
    }
    
    return racine;
}

void genererTableau(int tab[]) {
    for (int i = 0; i < nbElem; i++) {
        tab[i] = rand() % 10000 + 1;
    }
}


int comparer(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}


void genererTableauTrie(int tab[], int tabTrie[]) {
    memcpy(tabTrie, tab, nbElem * sizeof(int));
    qsort(tabTrie, nbElem, sizeof(int), comparer);
}

Noeud* genererABR(int tab[]) {
    Noeud* racine = NULL;
    
    for (int i = 0; i < nbElem; i++) {
        racine = inserer(racine, tab[i]);
    }
    
    return racine;
}

void libererABR(Noeud* racine) {
    if (racine != NULL) {
        libererABR(racine->gauche);
        libererABR(racine->droite); 
        free(racine);
    }
}

int main() {
    srand(time(NULL));
    
    int tab[nbElem];
    int tabTrie[nbElem];
    Noeud* racine = NULL;
    
    genererTableau(tab);
    genererTableauTrie(tab, tabTrie);
    racine = genererABR(tab);
    
    printf("Tableau original : ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
    
    printf("Tableau trie : ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", tabTrie[i]);
    }
    printf("\n");
    
    printf("ARB OK\n");
    
    libererABR(racine);
    
    return 0;
}