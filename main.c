#include <stdio.h>
#include "sistema.h"

int menu(void){
    int op;
    printf("======================================\n");
    printf("(1) Para ver os produtos cadastrados\n");
    printf("(2) Para adicionar um produto\n");
    printf("(3) Para buscar um produto\n");
    printf("(4) Para adicionar um produto do carrinho\n");
    printf("(5) Para remover um produto do carrinho\n");
    printf("(6) Para dar desconto na compra\n");
    printf("(7) Para finalizar a venda\n");
    printf("(0) Para encerrar o programa\n");
    scanf("%d%*c", &op);
    return op;
}

int main(int argc, char ** argv){
    int op, code, continu;
    int i, j = 0, tester = 0, t = 0;
    int recebe_code[1000];
    float soma = 0, desconto;
    Produtos p, *pdt = NULL;
    char nome [50];
    Sistema *SIS = NULL;
    
    SIS = carrega_sistema(argv[1]);

    while(1){
        op = menu();
        if(op==0) break;

        switch(op){
            case 1:
                print_produtos(SIS);
                break; 
            case 2:
                p = le_produto(stdin);
                add_prod(SIS, &p);
                break;
            case 3:
               printf("Digite o nome do produto que deseja buscar:\n");
               scanf("%s", nome);
               pdt = busca_prod(SIS, nome);
               if(pdt == NULL){
                   printf("Produto nao encontrado\n");
               } else print_prod(*pdt);
               break;
            case 4: 
                printf("Digite o codigo do produto que deseja adicionar ao carrinho:\n");
                scanf("%d%*c", &code);
            
                for(i=0;i<SIS->np;i++){
                    if(code==SIS->pdt[i].code){
                        soma = soma + SIS->pdt[i].valor;
                        tester++;
                    }
                }
                if(tester==0)printf("Erro ao adicionar produto: Codigo nao encontrado!\n");
                recebe_code[j] = code;
                j++;
                tester = 0;
                break;
            case 5: 
                printf("Digite o codigo do produto que deseja remover do carrinho:\n");
                scanf("%d%*c", &code);

                for(i=0;i<SIS->np;i++){
                    if(code==SIS->pdt[i].code){
                        soma = soma - SIS->pdt[i].valor;
                        tester++;
                    }
                }
                if(tester==0)printf("Erro ao remover produto: Codigo nao encontrado!\n");
                for(i=0;i<j;i++){
                    if(code==recebe_code[i]){
                        recebe_code[i] = -2;
                    }
                }
                tester=0;
                break;
            case 6:
                printf("Digite o valor do desconto em porcentagem:\n");
                scanf("%f", &desconto);
                if(desconto<=0 || desconto>=100){
                    printf("Valor inválido!\n");
                    break;
                }
                else soma = soma - (soma * (desconto/100));
                printf("Desconto dado!\n");
                break;
            case 7:
            printf("Os produtos selecionados foram:\n");
            for(t=0;t<j;t++){
                for(i=0;i<SIS->np;i++){
                    if(SIS->pdt[i].code==recebe_code[t]){
                        printf("%s codigo %d: R$%.2f\n", SIS->pdt[i].nome,SIS->pdt[i].code, SIS->pdt[i].valor);
                    }
                }
            }
            printf("\nValor total:\n");
            printf("%.2f\n", soma);
            printf("---------------------------\n");
            while(continu!=1){
                printf("Digite 1 para continuar: ");
                scanf("%d", &continu);
                setbuf(stdin, NULL);
            }            
            
            soma = 0;
            j = 0;        
        }
    }

    salvar_sis(SIS, argv[1]);

    return 0;
}