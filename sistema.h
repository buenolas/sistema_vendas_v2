#include <stdio.h>

typedef struct produtos{
    char nome[50];
    int code;
    float valor;
} Produtos;

typedef struct sistema{
    Produtos *pdt;
    int np;
}Sistema;

Sistema *carrega_sistema( char *fname); //feito
void salvar_sis(Sistema *sis, char *fname);//feito

void print_produtos(Sistema *sis);//feito
void add_prod(Sistema *sis, Produtos const *p);//feito
Produtos *busca_prod(Sistema *sis, char *nome);//feito
void del_prod(Sistema *sis, int code); //feito

Produtos le_produto(FILE *arq);//feito
void print_prod(Produtos p);//feito