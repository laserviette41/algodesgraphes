/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sat2.h
 * Author: ml
 *
 * Created on 1 octobre 2017, 15:24
 */

#ifndef SAT2_H
#define SAT2_H

#ifdef __cplusplus
extern "C" {
#endif
    
    struct clause{
    int nombre_literaux;
    int Sat; // cette variable va stocker 1 si la clause est sat ou 0 sinon. Elle va servir dans pour la fonction simplifier_formule. Sa valeur sera affectée par la fonction simplifier_clause
    //int conflit; // Si la variable "Sat" passe de 1 à 0, alors il y'a conflit;
    int *variable; //Tableau qui stock les litéreaux;
    struct clause *nxt; // pointeur sur la clause suivante;
    struct clause *prv; // pointeur sur la clause précedente;
    };
    typedef struct clause clause;
    

    struct arbre{
    //struct    arbre  * pere;
    //struct    arbre * fils_droit;
    //struct    arbre * fils_gauche;
    int continuer_simpliflication;//dis si on doit continuer à simplifier la formule ou pas; On va regarder si une clause est unitaire puis vérifier en fonction de notre assignation si la formule est UNSAT;
    int numero_variable_a_evaluer; // a chaque noeud, on incrementera cette var. Au noeud 0, on evalue la variable 0. Au noeud 1 on evalue la var 1.
    //int *historique_des_evalutions; // c'est un tableau. En clair au noeud 0 gauche, il contiendra par exemple 0. Puis au noeud 1 gauche, il contiendra 0 et 1 ou 0 et 0
    clause *formule; // la liste chainée de clause 
    int nombre_clause;
    int nombre_clause_sat; //cette variable indique le nombre de clause SAT dans la formule, elle est assigné après le passage de simplifier_formule;
    };
    typedef struct arbre arbre;
   
    
void simplifier_clause(int numero_variable_a_evaluer,clause *, int assignation); // Ne simplifie qu'une clause. Le numéro de la variable à evaluer est stocké dans l'arbre( i.e le noeud courant)
    
    // si on est sur arbre gauche, numero_variable_a_evaluer va toujours prendre la valeur 0
    //si on est  sur arbre droite, numero_variable_a_evaluer va toujours prendre la valeur 1
    //En simplifiant la clause avec la valeur 1, on on la stock dans "historique_des_evalutions" du noeud courant
    
    //code ..
    
    // si c'est la clause est SAT, on met "Sat" à 1;
    // sinon on résuit juste la clause et "Sat" à 0. Par exemple on aura (a ou non b ou c) qui devient (nonB ou c) par exemple.
    
    int var_est_dans_clause(int,clause *); // fonction annexe utilisé par simplifier_clause; Elle dit si la variable courante à évaluer est dans la clause ou pas.
    int clause_est_unitaire(clause *clause); // Vérifie si la clause est unitaire. 
    clause * simplifier_formule(arbre*,int); // Le numero variable a evaluer est dans le noeud courant (arbre courant) ainsi que la formule aussi;
    // Elle appelle simplifier_clause et des boucles boucles boucles..
    // Puis elle va regarder ce qu'il y a dans "Sat" et faire les supressions dans la chaine de clause(c'est à dire dans la formule);
    
    void unit_test_var_est_dans_clause(int numero_variable_a_evaluer,clause *clause);
    void unit_test_simplifier_clause(int numero_variable_a_evaluer,clause *clause, int assignation);
    void unit_test_simplifier_formule(arbre * arbre);
    
    int formule_est_sat(arbre * arbre);
    int test_formule_est_sat(arbre * arbre);
    void unit_clause_est_unitaire(clause *clause);
    
    void solveur_sat(arbre *, int numero_variable_a_evaluer, int assignation);
        
    
#ifdef __cplusplus
}
#endif

#endif /* SAT2_H */

