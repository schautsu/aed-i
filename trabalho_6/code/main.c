#include "myList.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FORA_LIMITE "\n[ERRO] O Valor informado deve ser entre %d e %d!\n"
#define INEXISTENTE "\nNao existem numeros narcisistas entre 10 e %d!\n"
#define BUSCA_0 "\n[ERRO] O numero %d nao existe na lista!\n"
#define MIN_N 10
#define MAX_N 1000000

void pause(){system("read -p '\n\nAperte qualquer tecla para continuar...\n' var");} //<=> system("pause");

void clear(){puts("\x1b[H\x1b[2J");} //<=> system("clear");

void console_exclusao()
{
    int n_delete;
    char choice;

    printf("\n\nDeseja excluir algum numero da lista? (S/n)\n--> ");
        do{
            scanf(" %c", &choice);

            if(choice == 'S' || choice == 's'){
                do{
                    printf("\n\nInforme o numero que deseja excluir:\n--> ");
                    scanf("%d", &n_delete);

                    if(!busca(n_delete))
                        printf(BUSCA_0, n_delete);
                    
                }while(!busca(n_delete));

                retira(n_delete);

                clear();
                printf("\nLista sem o numero %d:\n\n", n_delete);
                imprime();
            }
            else if(choice == 'n' || choice == 'N')
                printf("\n\nFim da execucao!\n");
            else
                printf("\n\n[ERRO] Informe: (S/n)\n--> ");
        }while(choice != 'S' && choice != 's' && choice != 'n' && choice != 'N');
}

int comprimento(int num)
{
    if(num == 1000000) return 7;
    if(num >= 100000) return 6;
    if(num >= 10000) return 5;
    if(num >= 1000) return 4;
    if(num >= 100) return 3;
    return 2;
}

int numNarcisista(int num)
{
    int pot = comprimento(num), sum = 0, num_aux = num;

    while(num_aux > 0){
        sum += pow(num_aux % 10, pot);

        num_aux /= 10;
    }

    if(sum == num) return num;
    return 0;
}

int main(/*int argc, char *argv[]*/)
{
    int i, exist = 0, number;// = atoi(argv[1]);

    //leitura de n
    do{
        clear();

        printf("Informe um numero entre %d e %d:\n--> ", MIN_N, MAX_N);
        scanf("%d", &number);

        if((number < MIN_N) || (number > MAX_N)){
            printf(FORA_LIMITE, MIN_N, MAX_N);
            pause();
        }
    }while((number < MIN_N) || (number > MAX_N));

    inicializa();

    for(i=MIN_N;i<=number;i++){
        if(numNarcisista(i)){
            exist++;
            insereOrdem(i);
        }
    }

    //se nao existirem numeros narcisistas entre 10 e o numero informado
    if(!exist)
        printf(INEXISTENTE, number);
    else //caso contrario
        imprime();

    console_exclusao();

    esvazia();
}
