#ifndef TOOLS_C
#define TOOLS_C

#include "tools.h"

cla *parseur(char *chemin){
    FILE *I=fopen(chemin,"r");
    if(!I)
        return NULL;
    int i=0,j=0,k=0;
    int *o=(int*)malloc(sizeof(int)*10);
    char *l=(char*)malloc(sizeof(char)*50),*tmp=(char*)malloc(sizeof(char)*10);
    char *b={" "};
    while(1){
        fgets(l,50,I);
        if(l[0]=='p')
            break;
    }
    tmp=strtok(l,b);
    for(;i<3;i++)
        tmp=strtok(NULL,b);
    int y=atoi(tmp);
    free(tmp);
    tmp=(char*)malloc(sizeof(char)*10);
    cla *r=(cla*)malloc(sizeof(cla)*y);
    i=0;
    while(fgets(l,50,I)){
        tmp=strtok(l,b);
        o[i++]=atoi(tmp);
        while(o[i-1]!=0){
            tmp=strtok(NULL,b);
            o[i++]=atoi(tmp);
            free(tmp);
            tmp=(char*)malloc(sizeof(char)*10);
        }
        r[j].nb=i;
        r[j].v=(int*)malloc(sizeof(int)*i);
        for(;k<i;k++){
            r[j].v[k]=o[k];
        }
        free(o);
        o=(int*)malloc(sizeof(int)*10);
        k=0;
        i=0;
        j++;
    }
    return r;
}



#endif //TOOLS_C
