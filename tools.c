#ifndef TOOLS_C
#define TOOLS_C

#include "tools.h"
#include "list.c"
#include<string.h>
#include<stdio.h>

void parseur(char *ch,ptr_list *p,int *prm){
	FILE *I=fopen(ch,"r");
    if(!I){
		printf("Fichier introuvable\n");
		exit(EXIT_FAILURE);
	}
    int i=0,j=0;
    int *o=malloc(sizeof(int)*10);
    char *l=malloc(sizeof(char)*50),*tmp=(char*)malloc(sizeof(char)*10),*b={" "};
    while(1){
        fgets(l,50,I);
        if(l[0]=='p')
            break;
    }

    while(fgets(l,50,I)){
        tmp=strtok(l,b);
        o[i++]=atoi(tmp);
        while(o[i-1]!=0){
			tmp=malloc(sizeof(char)*10);
            tmp=strtok(NULL,b);
            o[i++]=atoi(tmp);
        }
        ajout_clause(p,o,i);
        free(o);
        o=malloc(sizeof(int)*10);
        i=0;
        j++;
	}
	if(tmp) free(tmp);
	if(o) free(o);
}

int get_sol(int x,sol *s){
	sol *tmp=s;
	while(tmp){
		if(tmp->num==x && tmp->val==1){
			free(tmp);
			return 1;
		}
		tmp++;
	}
	free(tmp);
	return 0;
}

int clause_sat(cla c, sol *s){
	int i=c.nb;
	while(i--)
		if(get_sol(c.v[i],s))
			return 1;
	return 0;
}

int formule_sat(ptr_list *p,sol *s){
	cla *c=p->pr;
	while(c){
		if(!clause_sat(*c,s)) return 0;
		c=c->next;
	}
	return 1;
}



#endif //TOOLS_C
