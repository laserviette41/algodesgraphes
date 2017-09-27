#ifndef LIST_C
#define LIST_C

#include "list.h"

ptr_list *init(){
	ptr_list *n=malloc(sizeof(ptr_list));
	n->pr=NULL;
	n->der=NULL;
	return n;
}

void ajout_clause(ptr_list *p,int *va,int nb){
	int i=0;
	cla *c=malloc(sizeof(cla));
	if(!c) exit(EXIT_FAILURE);
	c->nb=nb;
	c->v=malloc(sizeof(int)*nb);
	for(;i<nb;i++) c->v[i]=va[i];
	c->prv=p->der;
	c->nxt=NULL;
	if(p->der) p->der->nxt=c;
	else p->pr=c;
	p->der=c;
}

void affiche_formule(ptr_list p){
	cla *c=p.pr;
	int i;
	while(c){
		for(i=0;i<c->nb;i++) printf("%d :: ",c->v[i]);
		printf("\n");
		c=c->nxt;
	}
}

void libere(ptr_list *p){
	cla *tmp,*c=p->pr;
	int i;
    while(c){
      tmp=c;
      c=c->nxt;
      free(tmp);
    }
    free(p);
}

void suppression_clause(cla *c){

}

#endif // LIST_C
