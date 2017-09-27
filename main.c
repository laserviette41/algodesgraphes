#include "list.c"
#include "tools.c"

int main(){
	ptr_list *p=malloc(sizeof(ptr_list));
	p->pr=NULL;
	p->der=NULL;
    int prm[2]; // prm[0] nb variable prm[1] nb clause
	parseur("fichier.cnf",p);
	affiche_formule(*p);
	libere(p);
    return 0;
}
