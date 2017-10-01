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

    struct Arbre{
        arbre noeud * pere;
        arbre fils * droit;
        arbre fils * gauche;
        int numero_variable_a_evaluer; // a chaque noeud, on incrementera cette var. Au noeud 0, on evalue la variable 0. Au noeud 1 on evalue la var 1.
        int *historique_des_evalutions; // c'est un tableau. En clair au noeud 0 gauche, il contiendra par exemple 0. Puis au noeud 1 gauche, il contiendra 0 et 1 ou 0 et 0
        clause *formule; // la liste chainée de clause 
    };
    typedef struct Arbre arbre;
    
    typedef struct Clause{
        int nombre_literaux;
        int Sat; // cette variable va stocker 1 si la clause est sat ou 0 sinon. Elle va servir dans pour la fonction simplifier_formule. Sa valeur sera affectée par la fonction simplifier_clause
        int *variable; //Tableau qui stock les litéreaux;
    }clause;
    
    
    void simplifier_clause(int numero_variable_a_evaluer,clause); // Ne simplifie qu'une clause. Le numéro de la variable à evaluer est stocké dans l'arbre( i.e le noeud courant)
    
    // si on est sur arbre gauche, numero_variable_a_evaluer va toujours prendre la valeur 0
    //si on est  sur arbre droite, numero_variable_a_evaluer va toujours prendre la valeur 1
    //En simplifiant la clause avec la valeur 1, on on la stock dans "historique_des_evalutions" du noeud courant
    
    //code ..
    
    // si c'est la clause est SAT, on met "Sat" à 1;
    // sinon on résuit juste la clause et "Sat" à 0. Par exemple on aura (a ou non b ou c) qui devient (nonB ou c) par exemple.
    
    
    clause * simplifier_formule(int numero_variable_a_evaluer, arbre formule); // Le numero variable a evaluer est dans le noeud courant ainsi que la formule
    // Elle appelle simplifier_clause et des boucles boucles boucles..
    // Puis elle va regarder ce qu'il y a dans "Sat" et faire les supressions dans la chaine de clause( formule);
#ifdef __cplusplus
}
#endif

#endif /* SAT2_H */
