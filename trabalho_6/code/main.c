/*
  ALUNOS
- Emerson B. Filho
- Gustavo K. Volobueff
- Gustavo M. Goncalves
- Victor K. O. Takatu
- Vinicius A. Schautz

  TERMINAL - OPERACAO EM LINUX (Pasta com 'main.c | myList.a | myList.h')

- Compilacao: gcc main.c -lm myList.a -o main
- Execucao: ./main
*/
#include "myList.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//SAIDAS DE ERRO - INSUCESSO
#define SAIDA_FORA_LIMITE "\n[ERRO] O Valor informado deve ser entre %d e %d!\n"
#define SAIDA_BUSCA_0 "\n[ERRO] O numero %d nao existe na lista!\n"
//SAIDAS DE RESULTADOS
#define SAIDA_INEXISTE "\nNao existem numeros narcisistas entre 10 e %d!\n"
//DADOS-BASE
#define MIN_N 10
#define MAX_N 1000000

//como em system("pause")
void pause(){system("read -p '\n\nAperte qualquer tecla para continuar...\n' var");}
//como em system("clear")
void clear(){puts("\x1b[H\x1b[2J");}

void console_exclusao()
{
    int n_delete;
    char escolha;

        do{
            printf("\nDeseja excluir algum numero da lista? (S/n)\n--> ");
            scanf(" %c", &escolha);

            if(escolha == 'S' || escolha == 's'){
                do{
                    printf("\nInforme o numero que deseja excluir:\n--> ");
                    scanf("%d", &n_delete);

                    if(!busca(n_delete))
                        printf(SAIDA_BUSCA_0, n_delete);
                    
                }while(!busca(n_delete));

                retira(n_delete);

                clear();
                printf("Lista sem o numero %d:\n", n_delete);
                imprime();
            }
            else if(escolha == 'n' || escolha == 'N')
                printf("\n\n---Fim da execucao---\n");

        }while(escolha != 'S' && escolha != 's' && escolha != 'N' && escolha != 'n');
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

int leitura_inicial()
{
    int num;

    do{
        clear();

        printf("Informe um numero entre %d e %d:\n--> ", MIN_N, MAX_N);
        scanf("%d", &num);

        if((num < MIN_N) || (num > MAX_N)){
            printf(SAIDA_FORA_LIMITE, MIN_N, MAX_N);
            pause();
        }
    }while((num < MIN_N) || (num > MAX_N));

    return num;
}

int main(/*int argc, char *argv[]*/)
{
    int n, i, existe = 0;

    n = leitura_inicial();

    inicializa();

    for(i=MIN_N;i<=n;i++){
        if(numNarcisista(i)){
            existe++;
            insereOrdem(i);
        }
    }

    //se nao existirem numeros narcisistas entre 10 e o numero informado
    if(!existe)
        printf(SAIDA_INEXISTE, n);
    else
    { //caso contrario
        imprime();

        console_exclusao();
    }

    esvazia();
}
