/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "sat2.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
 * \fn void simplifier_clause(int numero_variable_a_evaluer,clause *clause, int assignation)
 * \brief fonction qui simplifie une clause et dit si cette clause est sat ou pas.
 * \param Assignation vaut soit 0 soit 1
 * \return La clause simplifiée
 */
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


/**
 * \fn int var_est_dans_clause(int numero_variable_a_evaluer,clause *clause)
 * \brief Cette fonction vérifie si une variable est dans la clause
 * \return 1 si la variable est dans la clause et 0 sinon
 */

int var_est_dans_clause(int numero_variable_a_evaluer,clause *clause){
    for( int i=0; i< clause->nombre_literaux ; i++){
        if( clause->variable[i] == numero_variable_a_evaluer || clause->variable[i] == (- numero_variable_a_evaluer)) return 1;
    } 
    return 0;
}


/**
 * \fn int clause_est_unitaire(clause *clause)
 * \brief fonction qui vérifie si une clause contient qu'un seul litéral
 * \return 1 si clause unitaire et 0 sinon
 */
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

/**
 * \fn clause * simplifier_formule(arbre * arbre, int assignation)
 * \brief fonction qui simplifie une formule( liste chainée de clause ).
 * \param Assignation: Il s'agit de la valeur (0 ou 1) qu'on ouhaite affecté à la variable à simplifiée. Et cette dernieère se trouve dan l'arbre
 * \return La clause simplifiée et affecte 0 ou 1 à la variable " int continuer_simplification"
 */


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


/**
 * \fn unit_test_var_est_dans_clause(int numero_variable_a_evaluer,clause *clause)
 * \brief fonction qui test le bon fonctionnement de la fonction "var_est_dans_clause(int numero_variable_a_evaluer,clause *clause)" .
 
 * \return Informe par affichage ue la variable est dans la clause ou pas
 */

void unit_test_var_est_dans_clause(int numero_variable_a_evaluer,clause *clause){
    int res=0;
    res=var_est_dans_clause(numero_variable_a_evaluer,clause);
    if(res==1) printf("la variable est bien dans la clause");
    else if(res == 0) printf("la variable n'est pas dans la clause");
}

/**
 * \fn void unit_test_simplifier_clause(int numero_variable_a_evaluer,clause *clause, int assignation)
 * \brief Fonction qui vérifie si "test_simplifier_clause(int numero_variable_a_evaluer,clause *clause, int assignation)" fonctionne
 * \return Message de bon fonctionnement ou pas
 */
void unit_test_simplifier_clause(int numero_variable_a_evaluer,clause *clause, int assignation){ //cette fonction va afficher la la clause simplifié;
    simplifier_clause(numero_variable_a_evaluer,clause,assignation);
    for(int i=0; i< clause->nombre_literaux; i++){
        printf(" %d | ", clause->variable[i]);
    }
    printf("\nLe contenu de la variable SAT est à: %d  après le passage de la fonction simplifier_clause() \n", clause->Sat);
}

/**
 * \fn void unit_test_simplifier_formule(arbre * arbre)
 * \brief fonction qui test le bon fonctionnement de la fonction "simplifier_formule(arbre * arbre)" .
 
 * \return Affiche toutes les clauses et dit si, pour chacune, si elle est sat ou pas
 */
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

/**
 * \fn int test_formule_est_sat(arbre * arbre)
 * \brief Cette fonction teste si une formule complète est SAT ou pas.
 
 * \return 1 si SAT et 0 sinon
 */
int test_formule_est_sat(arbre * arbre){
    
    if(arbre->nombre_clause_sat==arbre->nombre_clause) return 1;
    else return 0;
}

/**
 * \fn void unit_clause_est_unitaire(clause *clause)
 * \brief Cette fonction vérifie que la fonction "clause_est_unitaire(clause *clause)" a le bon comportement
 
 * \return Un message qui dit si la clause est bien unitaire ou pas
 */
void unit_clause_est_unitaire(clause *clause){
    if (clause_est_unitaire(clause)) printf("la clause est unitaire");
    else printf("la clause n'est pas unitaire");
}


 void solveur_sat_Gabriel(arbre *a, int numero_variable_a_evaluer, int assignation,int nb_var){
    int i;
    arbre *b=malloc(sizeof(arbre));
    b->continuer_simpliflication=1;
    b->nombre_clause_sat=a->nombre_clause_sat;
    b->numero_variable_a_evaluer=a->numero_variable_a_evaluer;
    b->formule=simplifier_formule(a,assignation);
    b->nombre_clause=a->nombre_clause;
    b->historique_des_evalutions=malloc(sizeof(int)*nb_var);
    for(i=0;i<numero_variable_a_evaluer && numero_variable_a_evaluer>1;i++)
        b->historique_des_evalutions[i]=a->historique_des_evalutions[i-1];
    b->historique_des_evalutions[i]=assignation;
    if(formule_est_sat(a)){
        printf("SAT\n");
        exit(EXIT_SUCCESS);
    }
    else if(numero_variable_a_evaluer==nb_var){
        printf("UNSAT\n");
        exit(EXIT_SUCCESS);
    }
    solveur_sat(b,numero_variable_a_evaluer+1,0,nb_var);
    solveur_sat(b,numero_variable_a_evaluer+1,1,nb_var);
}

/**
 * \fn void solveur_sat(arbre * Arbre, int numero_variable_a_evaluer, int assignation)
 * \brief fonction qui répond au probleme de base. la formule est-elle SAT ?
 * \param Assignation : Il s'agit ici de l'assignation de la premiere variable qu'on veut évaluer
 * \return La réponse au problème
 */
void solveur_sat_Desire(arbre * Arbre, int numero_variable_a_evaluer, int assignation){
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

/* Solveur 
@params arbre *a : element d'étude
@params int numero_variable_a_evaluer : variable a évaluer
@params int assignation : vbaleur a assigner 
@params int nb _var : nombre de variable
@params int nb_cla ; nomvbre de clause
*/
void solveur_sat_Gabriel2(arbre *a, int numero_variable_a_evaluer, int assignation,int nb_var,int nb_cla){
    int i;
    arbre *b=malloc(sizeof(arbre));
    b->continuer_simpliflication=1;
    b->nombre_clause_sat=a->nombre_clause_sat;
    b->numero_variable_a_evaluer=a->numero_variable_a_evaluer;
    b->formule=simplifier_formule(a,assignation); // on simplifie la formule
    b->nombre_clause=nb_cla;
    b->historique_des_evalutions=malloc(sizeof(int)*nb_var);
    for(i=0;i<numero_variable_a_evaluer && numero_variable_a_evaluer>1;i++)
        b->historique_des_evalutions[i]=a->historique_des_evalutions[i-1];
    b->historique_des_evalutions[i]=assignation;
    if(formule_est_sat(b)){
        printf("SAT\n");
        exit(EXIT_SUCCESS);
    }
    else if(numero_variable_a_evaluer==nb_var){
        printf("UNSAT\n");
        exit(EXIT_SUCCESS);
    }
    solveur_sat(b,numero_variable_a_evaluer+1,1,nb_var,nb_cla);
    solveur_sat(b,numero_variable_a_evaluer+1,0,nb_var,nb_cla);
}

/* Fonction de lecture du fichier CNF
@params char *ch : chemin d'acces au fichiers CNF
@params clause *p : pointeur vers le premier élément de la liste chainé des clauses
@params int *prm : tableau permettant de récupere les parametres du problème
*/

void parseur(char *ch,clause *p,int *prm){
	FILE *I=fopen(ch,"r");
    if(!I){
		printf("Fichier introuvable\n");
		exit(EXIT_FAILURE);
	}
    int i=0,j=0,k;
    int *o=malloc(sizeof(int)*10);
    char *l=malloc(sizeof(char)*50),*tmp=(char*)malloc(sizeof(char)*10),*b={" "};
    while(1){
        fgets(l,50,I); // on saute les lignes de commentaires jusqu'a la ligne des parametres
        if(l[0]=='p')
            break;
    }
    tmp=strtok(l,b);
    tmp=strtok(NULL,b);
    tmp=strtok(NULL,b);
    prm[0]=atoi(tmp); // recuperation du nombre de variable
    tmp=strtok(NULL,b);
    prm[1]=atoi(tmp);// recuperation du nombre de clause
    int q[prm[0]];
    for(i=0;i<prm[0];i++) q[i]=0;
    i=0;
    while(fgets(l,50,I)){
        realloc(tmp,sizeof(char)*10);
        tmp=strtok(l,b);
        o[i++]=atoi(tmp);
        k=abs(o[i-1]-1);
        q[k]++;
        while(o[i-1]!=0){
	    realloc(tmp,sizeof(char)*10);
            tmp=strtok(NULL,b);
            o[i++]=atoi(tmp); // on stock la variable sous le format d'un int pour ensuite l'enregistré lors de la creation de la clause
        }
        ajout_clause(p,o,i-1);
        realloc(o,sizeof(int)*10);
        i=0;
        j++;
	}
	if(tmp) free(tmp);
	if(o) free(o);
}
 
 /* ajoute une clause a la liste chainee
@params clause *p : pointeur vers le premier élément de la liste
@params int *va : tableau contenant les variables 
@params  int nb : nombre de litéraux
*/

void ajout_clause(clause *p,int *va,int nb){
	int i=0;
	clause *c=malloc(sizeof(clause));
	if(!c) exit(EXIT_FAILURE);
	c->nombre_literaux=nb;
	c->Sat=0;
	c->variable=malloc(sizeof(int)*nb);
	for(;i<nb;i++)
        c->variable[i]=va[i];
	clause *tmp=p;
	while(tmp->nxt) tmp=tmp->nxt;
	c->prv=tmp;
	if(p){
        tmp->nxt=c;
        c->prv=tmp;
        c->nxt=NULL;
	}
	else{
        c->nxt=NULL;
        c->prv=NULL;
        p=malloc(sizeof(clause));
        p=c;
	}
}