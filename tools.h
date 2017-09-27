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


/// typedef de l'abr defini plus loin
typedef struct Arbre abr;

/** Solution du probleme
 *  @param num : numero de la variable
 *  @param val : valeur de la variable
 **/
typedef struct Solution{
    int num;
    int val;
}sol;

/** Structure de l'abr
 *  @param noeudpere :  pointeur vers le noeud precedent
 *  @param c : tableau de clause => formule
 *  @param s : solution hypothese de lu noeud
 *  @param fgauche
 *  @param fdroit
 **/
struct Arbre{
    abr *noeudpere;
    cla *c;
    sol *s;
    abr *fdroit;
    abr *fgauche;
};



int clause_sat(cla,sol*); // verifie si cla est satisfait

int formule_sat(ptr_list*,sol*); // evalue la formule cla en fonction de sol

cla *simplification(cla*,int); //  simplifie cla* en fonction de la variable indique par l'int

//void suppression_clause(cla*,int); // supprime la clause i du tableau cla* si cla(i) est SAT (a preciser)

int is_unit(cla); // cla est unitaire ?

sol stock_sol(int,int); // (a preciser) stockage de la solution int valeur int numero de la variable

int var_plus_pre(cla*); // detecte la variable la plus presente et renvoie son indice

void parseur(char*,ptr_list*,int*); // lit le cnf et stocke les variable dans une liste chaine

int get_sol(int,sol*); // cherche la solution de la variable int dans sol*

/**
 * coder structure abr
 **/

#endif	/* TOOLS_H */

