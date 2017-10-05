/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "sat2.h"
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
                    if (clause->variable[i]==numero_variable_a_evaluer) clause->variable[i]=-1001;
                }
                clause->Sat=0;
               
            }
        }
          
    }
}

int var_est_dans_clause(int numero_variable_a_evaluer,clause *clause){
    for( int i=0; i< clause->nombre_literaux ; i++){
        if( clause->variable[i] == numero_variable_a_evaluer || clause->variable[i] == (- numero_variable_a_evaluer)) return 1;
    } 
    return 0;
}
clause * simplifier_formule(arbre * arbre){
    while(arbre->formule){ //traitement pour une clause;
        simplifier_clause(arbre->numero_variable_a_evaluer,arbre->formule, 0);  //jai mis une assignation à zero. c'est pas dynamique là! 
        if(arbre->formule->Sat){
            ...;
        }
        else{
            ...;
        }
        arbre->formule=arbre->formule->nxt; //on passe à la clause suivante  
    }
}