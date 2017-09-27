#include "list.c"
#include "tools.c"

int main(){
	ptr_list *p=malloc(sizeof(ptr_list));
	p->pr=NULL;
	p->der=NULL;
    int prm[2];
	parseur("fichier.cnf",p);
	affiche_formule(*p);
	libere(p);
    return 0;
}
