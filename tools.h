/* 
 * File:   tools.h
 * Author: gamasson
 *
 * Created on 14 septembre 2017, 12:04
 */

#ifndef TOOLS_H
#define	TOOLS_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Arbre abr;

typedef struct  Variable{
    int num;
    int inv;
}var;

typedef struct Clause{
    int *v;
    //var *v;
    int nb;
}cla;

struct Arbre{
    abr *noeudpere;
    cla *c;
    sol *s;
    abr *fdroit;
    abr *fgauche;
};

typedef struct Solution{
    int num;
    int sol;
}sol;


cla *parseur(char*); // lit le fichier cnf et retour un tableau de clause

int clause_sat(cla); // verifie si cla est satisfait

int formule_sat(cla*,sol*); // evalue la formule cla en fonction de sol

cla *simplification(cla*,int); //  simplifie cla* en fonction de la variable indique par l'int

void suppression_clause(cla*,int); // supprime la clause i du tableau cla* si cla(i) est SAT (a preciser)

int is_unit(cla); // cla est unitaire ? 

sol stock_sol(int,int); // (a preciser) stockage de la solution int valeur int numero de la variable 

int var_plus_pre(cla*); // detecte la variable la plus presente et renvoie son indice

/**
 * coder structure abr
 **/

#endif	/* TOOLS_H */

