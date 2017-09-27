#ifndef LIST_H
#define LIST_H

#include<stdlib.h>
#include<stdio.h>

typedef struct Clause cla;

typedef struct Pointeur ptr_list;

struct Clause{
	int *v;
	int nb;
	cla *nxt;
	cla *prv;
};

struct Pointeur{
	cla *pr;
	cla *der;
};

ptr_list *init();

void ajout_clause(ptr_list*, int*, int);

void affiche_formule(ptr_list);

void suppression_clause(cla*);

void libere(ptr_list*);

#endif // LIST_H
