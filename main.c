#include "list.c"
#include "tools.c"

int main(){
	ptr_list *p=malloc(sizeof(ptr_list));
	p->pr=NULL;
	p->der=NULL;
    int prm[3]; // prm[0]=nb var | prm[1]=nb clause| prm[2]=var la plus presente
	parseur("fichier2.cnf.txt",p,prm);
	printf("%d :: %d :: %d\n",prm[0],prm[1],prm[2]);
	//libere(p);
    return 0;
}
