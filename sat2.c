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
                    if(clause->variable[i]==numero_variable_a_evaluer){
                        clause->variable[i]=0; // "0" est un code pour dire qu'on a supprimé la variable du tableau                      
                    } 
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
int clause_est_unitaire(clause *clause){
    int cpt=0; // compte le nombre de 0 dans une clause;
    if(clause->nombre_literaux==1) return 1; // S'il y'a un seul litéral => clause unitaire
    int i;
    for(i=0; i<clause->nombre_literaux; i++){
        if(clause->variable[i]==0) cpt++;
    }
    if(cpt==clause->nombre_literaux-1) return 1; 
    else return 0;
    
}
clause * simplifier_formule(arbre * arbre, int assignation){
    clause *tmp=(clause*)malloc(sizeof(clause));
    tmp=arbre->formule;
    int cpt=0; //compte le nombre de clause SAT;
    while(arbre->formule){ //traitement pour une clause;
        
        if (clause_est_unitaire(arbre->formule)){
        int temp=0;
        for(int i=0; i<arbre->formule->nombre_literaux; i++){
            if(arbre->formule->variable[i]!=0) temp=arbre->formule->variable[i];
        }    
        if(temp==arbre->numero_variable_a_evaluer){
            if((temp>0 && assignation==0) || (temp<0 && assignation==1)){
                arbre->continuer_simpliflication=0;
                //return;
            }  
        }  
    }
        
        
        simplifier_clause(arbre->numero_variable_a_evaluer,arbre->formule, assignation);  //jai mis une assignation à zero. c'est pas dynamique là! 
         // Si la clause courante n'est pas SAT, la fonction "simplifier_clause" a déja résuit la clause convenablement;
        if(arbre->formule->Sat) cpt++;
        arbre->formule=arbre->formule->nxt; //on passe à la clause suivante ;
        //free(arbre->formule); // puis je supprime la clause courante. Où le free, ici ??
    }
    arbre->nombre_clause_sat=cpt;
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
    Clause=simplifier_formule(arbre,0); // assignation est mis à 0 ici arbitrairement pour tester;
    while(Clause){
        for(int i=0; i< Clause->nombre_literaux; i++){
        printf("%d| ", Clause->variable[i]);
        }
        if(Clause->Sat==1) printf("\n  etat de la clause: SAT  ");
        else printf("etat de la clause: pas SAT");
        printf("\n  clause suivante : \n");
        Clause=Clause->nxt;
    }
    printf("continuer à simplifier ? %d", arbre->continuer_simpliflication);
}

int test_formule_est_sat(arbre * arbre){
    
    if(arbre->nombre_clause_sat==arbre->nombre_clause) return 1;
    else return 0;
}

void unit_clause_est_unitaire(clause *clause){
    if (clause_est_unitaire(clause)) printf("la clause est unitaire");
    else printf("la clause n'est pas unitaire");
}
void solveur_sat(arbre * Arbre, int numero_variable_a_evaluer, int assignation){
    if(Arbre->continuer_simpliflication == 0) printf("formule unsat"); //CAS DE BASE
    //else if (Arbre->continuer_simpliflication == 1 && Arbre->numero_variable_a_evaluer==3); // LA SUITE DU CAS DE BASE
    else{
    arbre * sous_arbre1 = (arbre *)malloc(sizeof(arbre));
    arbre * sous_arbre2 = (arbre *)malloc(sizeof(arbre));
    sous_arbre1->continuer_simpliflication=1;
    sous_arbre1->nombre_clause=Arbre->nombre_clause;
    sous_arbre1->nombre_clause_sat=0;
    sous_arbre1->numero_variable_a_evaluer=Arbre->numero_variable_a_evaluer;
    
    
    sous_arbre2->continuer_simpliflication=1;
    sous_arbre2->nombre_clause=Arbre->nombre_clause_sat;
    sous_arbre2->nombre_clause_sat=0;
    sous_arbre2->numero_variable_a_evaluer=Arbre->numero_variable_a_evaluer;
    
    sous_arbre1->formule = simplifier_formule(Arbre,assignation);
    sous_arbre2->formule = simplifier_formule(Arbre,assignation+1);
    
    printf(" DÉBUT du IF:\n  ");  
    if(sous_arbre1->numero_variable_a_evaluer<4){
        sous_arbre1->numero_variable_a_evaluer++;
        sous_arbre2->numero_variable_a_evaluer++;
        solveur_sat(sous_arbre1, sous_arbre1->numero_variable_a_evaluer, 0);
        solveur_sat(sous_arbre2, sous_arbre2->numero_variable_a_evaluer+1, 1);
    } 

    }
   
}
 