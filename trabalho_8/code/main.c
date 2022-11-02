#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_OPEN_CODE "\n[ERRO] Nao foi possivel abrir o arquivo codificado"
#define ERR_OPEN_DECODE "\n[ERRO] Nao foi possivel abrir o arquivo decodificado"
#define ERR_OPEN_NLINES "\n[ERRO] Nao foi possivel abrir o arquivo enumerado"

#define MAX_CHAR_LEN 80
#define MAX_LINE_LEN 100
#define MAX_ROWS 800

/*Function prototypes*/
int escolha_menu(void);
void handler_menu(void);
void gera_menu(void);
void decifra_arquivo(void);
void grava_linhas(void);
void numero_linhas(void);
void maior_linha(void);
void pesquisa_palavra(void);
void flush_in(void);

/*Filenames*/
char *file_code = "readme.code.txt";
char *file_decode = "readme.decifra.txt";
char *file_nlines = "readme.nlines.txt";

int main()
{
    FILE *fp_code;

    if ((fp_code = fopen(file_code, "r"))) {
        handler_menu();
    } else {
        perror(ERR_OPEN_CODE);
        puts("");
    }
    fclose(fp_code);

    return (0);
}

void handler_menu()
{
    int escolha;
    do {
        escolha = escolha_menu();

        switch (escolha) {
            //Decifra arquivo
            case 1:
                decifra_arquivo();
            break;
            //Grava numero linha em arquivo
            case 2:
                grava_linhas();
            break;
            //Quantas linhas o arquivo tem
            case 3:
                numero_linhas();
            break;
            //Qual a maior linha
            case 4:
                maior_linha();
            break;
            //Pesquisar uma palavra
            case 5:
                pesquisa_palavra();
            break;
        }
    } while (escolha != 0);
}

void gera_menu()
{
    system("cls");
    fputs("\n[1] Decifra arquivo\n[2] Grava numero linha em arquivo\n[3] Quantas linhas tem o arquivo\n[4] Qual a maior linha\n[5] Pesquisar uma palavra\n[0] Encerrar\n\nQual opcao: ", stdout);
}

int escolha_menu()
{
    int escolha;
    do {
        gera_menu();
    } while ((escolha < 1 && escolha > 5) || (!scanf("%d", &escolha) && getchar()));

    return (escolha);
}

void decifra_arquivo()
{
    FILE *fp_code, *fp_decode;

    fp_code = fopen(file_code, "r");
    fp_decode = fopen(file_decode, "w");

    char fElement, chrTemp[4], chrFinal;
    int inTemp, index = 0;

    do {
        fread(&fElement, 1, 1, fp_code);

        if (fElement != '[' && fElement != ']')
        {
            chrTemp[index++] = fElement;
        }
        else if (fElement == ']') //Leu 1 caractere [...]
        {
            inTemp = atoi(chrTemp);
            chrFinal = (char) inTemp;

            fwrite(&chrFinal, 1, 1, fp_decode); //Registra o caracter no arquivo decifrado
            
            index = 0;
            memset(chrTemp, 0, sizeof(chrTemp)); //Reset do array temporario
        }
    } while (!feof(fp_code));

    fclose(fp_code);
    fclose(fp_decode);

    puts("\n[SUCESSO] Arquivo decifrado!\n");

    system("pause");
}

void grava_linhas()
{
    FILE *fp_decode, *fp_nlines;

    if ((fp_decode = fopen(file_decode, "r")))
    {
        fp_nlines = fopen(file_nlines, "w");

        char lineTemp[MAX_LINE_LEN];
        int numRows = 0;

        while (fgets(lineTemp, MAX_LINE_LEN, fp_decode))
        {
            fprintf(fp_nlines, "[linha:%d] %s", ++numRows, lineTemp); //Registra a string-linha no arquivo
        }
        fclose(fp_nlines);

        puts("\n[SUCESSO] Arquivo enumerado!\n");
    } 
    else {
        perror(ERR_OPEN_DECODE);
        puts("");
    }
    fclose(fp_decode);

    system("pause");
}

void numero_linhas()
{
    FILE *fp_decode;

    if ((fp_decode = fopen(file_decode, "r")))
    {
        char lineTemp[MAX_LINE_LEN];
        int numRows = 0;

        while (fgets(lineTemp, MAX_LINE_LEN, fp_decode))
        {
            numRows++;
        }
        printf("\nO arquivo %s tem (%d) linhas.\n\n", file_decode, numRows);
    }
    else {
        perror(ERR_OPEN_DECODE);
        puts("");
    }
    fclose(fp_decode);

    system("pause");
}

void maior_linha()
{
    FILE *fp_decode;

    if ((fp_decode = fopen(file_decode, "r")))
    {
        char lineTemp[MAX_LINE_LEN]; 
        unsigned numRows = 0, maior_numChr = 0, maior_row;

        while (fgets(lineTemp, MAX_LINE_LEN, fp_decode))
        {
            numRows++;   
            if (strlen(lineTemp) > maior_numChr) 
            {
                maior_row = numRows;
                maior_numChr = strlen(lineTemp);
            }
        }
        
        printf("\nA linha [%u] e a maior com (%u) caracteres.\n\n", maior_row, maior_numChr);
    }
    else {
        perror(ERR_OPEN_DECODE);
        puts("");
    }
    fclose(fp_decode);

    system("pause");
}

void pesquisa_palavra()
{
    FILE *fp_decode, *fp_nlines;

    if ((fp_decode = fopen(file_decode, "r")) == NULL)
    {
        perror(ERR_OPEN_DECODE);
        puts("");
    } 
    else if ((fp_nlines = fopen(file_nlines, "r")) == NULL)
    {
        perror(ERR_OPEN_NLINES);
        puts("");
    }
    else {
        char word[MAX_CHAR_LEN], rowTemp[MAX_LINE_LEN], nlinesTemp[MAX_LINE_LEN], lineExist[MAX_ROWS][MAX_LINE_LEN], *substr;
        int existFile = 0, indexExist = 0, existLine, tam;

        fputs("\nQual palavra pesquisar: ", stdout);
        flush_in();
        fgets(word, MAX_CHAR_LEN, stdin);

        tam = strlen(word);
        word[tam - 1] = 0; //posicao NULL para nao ter erro em strstr

        while (fgets(rowTemp, MAX_LINE_LEN, fp_decode))
        {
            fgets(nlinesTemp, MAX_LINE_LEN, fp_nlines);

            existLine = 0;
            substr = rowTemp;

            while ((substr = strstr(substr, word)))
            {
                existLine++;
                memmove(substr, substr + tam, strlen(substr + tam) + 1);

                existLine == 1 ? strcpy(lineExist[indexExist++], nlinesTemp) : 0;
            }    
            existFile += existLine;
        }
        
        if(existFile)
        {
            printf("\nAs linhas em que a palavra '%s' ocorre:\n\n", word);

            for (int i = 0; i < indexExist; i++) printf("%s", lineExist[i]);

            printf("\ne tem %d ocorrencias.\n\n", existFile);
        }
        else printf("\nNao existem ocorrencias da palavra '%s'!\n\n", word);
    }
    fclose(fp_decode);
    fclose(fp_nlines);

    system("pause");
}

void flush_in()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
