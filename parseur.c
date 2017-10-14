void parseur(char *ch,clause *p,int *prm){
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
        realloc(tmp,sizeof(char)*10);
        tmp=strtok(l,b);
        o[i++]=atoi(tmp);
        k=abs(o[i-1]-1);
        q[k]++;
        while(o[i-1]!=0){
			realloc(tmp,sizeof(char)*10);
            tmp=strtok(NULL,b);
            o[i++]=atoi(tmp);
        }
        ajout_clause(p,o,i-1);
        realloc(o,sizeof(int)*10);
        i=0;
        j++;
	}
	if(tmp) free(tmp);
	if(o) free(o);
}

void ajout_clause(clause *p,int *va,int nb){
	int i=0;
	clause *c=malloc(sizeof(clause));
	if(!c) exit(EXIT_FAILURE);
	c->nombre_literaux=nb;
	c->Sat=0;
	c->variable=malloc(sizeof(int)*nb);
	for(;i<nb;i++)
        c->variable[i]=va[i];
	clause *tmp=p;
	while(tmp) tmp=tmp->nxt;
	c->prv=tmp;
	if(p){
        tmp->nxt=c;
        c->prv=tmp;
        c->nxt=NULL;
	}
	else{
        c->nxt=NULL;
        c->prv=NULL;
        p=malloc(sizeof(clause));
        p=c;
	}
}

void solveur_sat(arbre *a, int numero_variable_a_evaluer, int assignation,int nb_var,int nb_cla){
    int i;
    arbre *b=malloc(sizeof(arbre));
    b->continuer_simpliflication=1;
    b->nombre_clause_sat=a->nombre_clause_sat;
    b->numero_variable_a_evaluer=a->numero_variable_a_evaluer;
    b->formule=simplifier_formule(a,assignation);
    b->nombre_clause=nb_cla;
    b->historique_des_evalutions=malloc(sizeof(int)*nb_var);
    for(i=0;i<numero_variable_a_evaluer && numero_variable_a_evaluer>1;i++)
        b->historique_des_evalutions[i]=a->historique_des_evalutions[i-1];
    b->historique_des_evalutions[i]=assignation;
    if(formule_est_sat(b)){
        printf("SAT\n");
        exit(EXIT_SUCCESS);
    }
    else if(numero_variable_a_evaluer==nb_var){
        printf("UNSAT\n");
        exit(EXIT_SUCCESS);
    }
    solveur_sat(b,numero_variable_a_evaluer+1,1,nb_var,nb_cla);
    solveur_sat(b,numero_variable_a_evaluer+1,0,nb_var,nb_cla);
}
