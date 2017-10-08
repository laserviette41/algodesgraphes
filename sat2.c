/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "sat2.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void simplifier_clause(int numero_variable_a_evaluer,clause *clause, int assignation){
    if( !( var_est_dans_clause(numero_variable_a_evaluer, clause) ) ) {
        clause->Sat=0; // la clause n'est pas SAT du coup;
        // il n'y a donc rien à simplifier ici;
    } 
    else {
        if(numero_variable_a_evaluer>0){
            if (assignation == 0){
                for(int i=0; i< clause->nombre_literaux; i++){ //Je recherche la variable dans le tableau et  la supprime.
                    if(clause->variable[i]==numero_variable_a_evaluer) clause->variable[i]=0; // "0" est un code pour dire qu'on a supprimé la variable du tableau
                }
                clause->Sat=0; // la clause n'est pas sat. On l'a juste réduit.
                
            }
            else if (assignation==1) {
                clause->Sat=1;
                
            }
        }
        else if (numero_variable_a_evaluer<0){
            if (assignation == 0){
                clause->Sat=1;
                
            }
            else if (assignation==1){
                for(int i=0; i< clause->nombre_literaux; i++){
                    if (clause->variable[i]==numero_variable_a_evaluer) clause->variable[i]=0;
                }
                clause->Sat=0;
               
            }
        }
          
    }
} // Au final simplifier_clause va réduire la clause ou la laisser telle qu'elle. Et elle va aussi modifier la variable "int SAT" à 1 ou 0; 

int var_est_dans_clause(int numero_variable_a_evaluer,clause *clause){
    for( int i=0; i< clause->nombre_literaux ; i++){
        if( clause->variable[i] == numero_variable_a_evaluer || clause->variable[i] == (- numero_variable_a_evaluer)) return 1;
    } 
    return 0;
}
clause * simplifier_formule(arbre * arbre){
    clause *tmp=(clause*)malloc(sizeof(clause));
    tmp=arbre->formule;
    while(arbre->formule){ //traitement pour une clause;
        
        simplifier_clause(arbre->numero_variable_a_evaluer,arbre->formule, 0);  //jai mis une assignation à zero. c'est pas dynamique là! 
        
        if(arbre->formule->Sat){ //Si la clause courante est SAT
            arbre->formule->prv=arbre->formule->nxt; // je fais pointer la clause précédente vers celle qui suit la clause courante;
        }
        // Si la clause courante n'est pas SAT, la fonction "simplifier_clause" a déja résuit la clause convenablement;
  
        arbre->formule=arbre->formule->nxt; //on passe à la clause suivante ;
        //free(arbre->formule); // puis je supprime la clause courante. Où le free, ici ??
    }
    return tmp; // je retourne le pointeur sur la formule;
}


void unit_test_var_est_dans_clause(int numero_variable_a_evaluer,clause *clause){
    int res=0;
    res=var_est_dans_clause(numero_variable_a_evaluer,clause);
    if(res==1) printf("la variable est bien dans la clause");
    else if(res == 0) printf("la variable n'est pas dans la clause");
}

void unit_test_simplifier_clause(int numero_variable_a_evaluer,clause *clause, int assignation){ //cette fonction va afficher la la clause simplifié;
    simplifier_clause(numero_variable_a_evaluer,clause,assignation);
    for(int i=0; i< clause->nombre_literaux; i++){
        printf(" %d | ", clause->variable[i]);
    }
    printf("\nLe contenu de la variable SAT est à: %d  après le passage de la fonction simplifier_clause() \n", clause->Sat);
}

void unit_test_simplifier_formule(arbre * arbre){
    clause * Clause=(clause*)malloc(sizeof(clause));
    Clause=simplifier_formule(arbre);
    while(Clause){
        for(int i=0; i< 3; i++){
        printf("%d |", Clause->variable[i]);
        }
        printf("\n  clause suivante : \n");
        Clause=Clause->nxt;
    }
}