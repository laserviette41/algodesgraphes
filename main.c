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

int main(int argc, char** argv) {
    
    char *ch=malloc(sizeof(char)*50);
    int i,j;
    printf(" Entrer le nom du fichier CNF: ");
    scanf("%s",ch);
    clause *x=NULL;
    int prm[2]; // prm[0] nb de variable et prm[1] nb de clause
    parseur(ch,x,prm);
    arbre *a=init_a(x,prm[0],prm[1],0);
    solveur(a,1,0,prm[0],prm[1]);
    return 0;
}
   

  


