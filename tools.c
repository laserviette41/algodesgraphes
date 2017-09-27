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
    int i=0,j=0,k;
    int *o=malloc(sizeof(int)*10);
    char *l=malloc(sizeof(char)*50),*tmp=(char*)malloc(sizeof(char)*10),*b={" "};
    while(1){
        fgets(l,50,I);
        if(l[0]=='p')
            break;
    }
    tmp=strtok(l,b);
    tmp=strtok(NULL,b);
    tmp=strtok(NULL,b);
    prm[0]=atoi(tmp);
    tmp=strtok(NULL,b);
    prm[1]=atoi(tmp);
    int q[prm[0]];
    for(i=0;i<prm[0];i++) q[i]=0;
    i=0;
    while(fgets(l,50,I)){
        tmp=strtok(l,b);
        o[i++]=atoi(tmp);
        k=abs(o[i-1]-1);
        q[k]++;
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
	prm[3]=var_plus_pre(q,prm[0]);
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
		c=c->nxt;
	}
	return 1;
}

int var_plus_pre(int *x,int n){
    int i=n,max=x[0],ind=0;
    while(i--)
        if(x[i]>max){
            max=x[i];
            ind=i;
        }
    return ind;
}


#endif //TOOLS_C
