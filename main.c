/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ml
 *
 * Created on 18 septembre 2017, 13:51
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "sat2.h"

/*
 * 
 */
void * genererTableau(int taille){
    int *tab;
    tab=(int *)malloc(sizeof(int)*taille);
    return tab;
}

int main(int argc, char** argv) {
    /*
	ptr_list *p=malloc(sizeof(ptr_list));
	p->pr=NULL;
	p->der=NULL;
        int prm[2]; // prm[1] :nb clause , prm[0] :nb variable
	parseur("fichier.cnf",p, prm);
	affiche_formule(*p);
	libere(p);
    */
    /* // Test unitaire qui vérifie que la fonction "var_est_dans_clause" a le comportement attendu.
    clause * Clause = (clause*)malloc(sizeof(clause));
    Clause->Sat=0;
    Clause->nombre_literaux=5;
    Clause->nxt=NULL;
    Clause->prv=NULL;
    Clause->variable=genererTableau(3);
    Clause->variable[0]=1;
    Clause->variable[1]=8;
    Clause->variable[2]=3;
    unit_test_var_est_dans_clause(6,Clause);
    */ 
    
    /* // Test unitaire de la fonction simplifier_clause(). Elle renvoie la clause simplifiée ainsi que le statut de la clause (SAT ou pas SAT);
    clause * Clause = (clause*)malloc(sizeof(clause));
    Clause->Sat=0;
    Clause->nombre_literaux=3;
    Clause->nxt=NULL;
    Clause->prv=NULL;
    Clause->variable=genererTableau(3);
    Clause->variable[0]=1;
    Clause->variable[1]=-5;
    Clause->variable[2]=3;
    unit_test_simplifier_clause(-5,Clause, 1);
    */
    
    /* //test unitaire de la fonction supprimer_formule.
    clause * Clause = (clause*)malloc(sizeof(clause));
    clause * Clause2 = (clause*)malloc(sizeof(clause));
    clause * Clause3 = (clause*)malloc(sizeof(clause));
    Clause->Sat=0;
    Clause->nombre_literaux=3;
    Clause->nxt=Clause2;
    Clause->prv=NULL;
    Clause->variable=genererTableau(3);
    Clause->variable[0]=1;
    Clause->variable[1]=-5;
    Clause->variable[2]=3;
    
    Clause2->Sat=0;
    Clause2->nombre_literaux=3;
    Clause2->nxt=Clause3;
    Clause2->prv=Clause;
    Clause2->variable=genererTableau(3);
    Clause2->variable[0]=3;
    Clause2->variable[1]=7;
    Clause2->variable[2]=-9;
    
    Clause3->Sat=0;
    Clause3->nombre_literaux=3;
    Clause3->nxt=NULL;
    Clause3->prv=Clause2;
    Clause3->variable=genererTableau(3);
    Clause3->variable[0]=8;
    Clause3->variable[1]=2;
    Clause3->variable[2]=-2;
    
    
    
    arbre * Arbre=(arbre *)malloc(sizeof(arbre));
    Arbre->fils_droit=NULL;
    Arbre->fils_gauche=NULL;
    Arbre->formule= Clause;
    Arbre->numero_variable_a_evaluer=2;
    Arbre->pere=NULL;
    unit_test_simplifier_formule(Arbre);
    */
    return 0;
}
  


