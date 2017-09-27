#ifndef ABR_C
#define ABR_C

#include "abr.h"

typedef struct Arbre abr;

struct Arbre{
    abr *noeudpere;
    ptr_list *f;
    sol *s;
    abr *fdroit;
    abr *fgauche;
};

void init(abr *b, ptr_list *f,int x){
    b->noeudpere=NULL;
    b->fdroit=NULL;
    b->fgauche=NULL;
    b->f=f;
    b->s=malloc(sizeof(int)*x);
}

void addFD();
void addFG();


#endif // ABR_C
