#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema.h"

Produtos le_produto(FILE *arq){
    Produtos prod;
    fscanf(arq, "%s", prod.nome);
    fscanf(arq, "%d", &prod.code);
    fscanf(arq, "%f", &prod.valor);
    return prod;
}

Sistema *carrega_sistema(char * file_name){
    
    Sistema *SIS = NULL;
    FILE *arq = NULL;
    Produtos ptemp;

    SIS = malloc(sizeof(Sistema));
    SIS->pdt = NULL;
    SIS->np = 0;

    printf("Abrindo o arquivo %s...\n", file_name);
    arq = fopen( file_name, "rt");
    if(arq == NULL) return SIS;

    printf("Arquivo aberto com sucesso!\n");

    while(1){
        ptemp = le_produto(arq);
        if(feof(arq)!=0) break;
        add_prod(SIS, &ptemp);
    }
    fclose(arq);
    return SIS;
}

void salvar_sis(Sistema *sis, char *file_name){
    FILE *arq = NULL;
    Produtos p;
    int i;
    arq = fopen(file_name, "wt");
    if(arq == NULL){
        printf("Erro ao criar o arquivo para salvar\n");
        exit(0);
    }
    for(i=0;i<sis->np;i++){
        p = sis->pdt[i];
        fprintf(arq, "%s %d %.2f\n", p.nome, p.code, p.valor);
    }
    fclose(arq);
}

void print_prod(Produtos p){
    printf("------------------------\n");
    printf("Produto: %s\n", p.nome);
    printf("Codigo: %d\n", p.code);
    printf("Valor: %.2f\n", p.valor);
}

void print_produtos(Sistema *sis){
    int i;
    printf("Quantidade de produtos cadastrados: %d\n", sis->np);

    for(i=0;i<sis->np;i++){
        print_prod(sis->pdt[i]);
    }
}

void add_prod(Sistema *sis, Produtos const *p){
    Produtos *pdt = NULL;
    pdt = (Produtos*) realloc( sis->pdt, (sis->np+1)*sizeof(Produtos));
    if(p != sis->pdt){
        if(pdt==NULL) exit(0);
        sis->pdt = pdt; 
    }
    sis->pdt[sis->np] = *p;
    sis->np++;
}

Produtos *busca_prod(Sistema *sis, char *nome){
    int i;
    for(i=0;i<sis->np;i++){
        if(strcmp(nome, sis->pdt[i].nome)==0){
            return &(sis->pdt[i]);
        }
    }
    return NULL;
}
