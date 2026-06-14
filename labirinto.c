/* TRABALHO II - LABIRINTO
    Discente: Ysis Barduco Straub de Lima
    Discente: Ariane de Oliveira Neves
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Estrutura de dados Pilha
typedef struct Nodo_Pilha{
    int posicao;
    struct Nodo_Pilha *prox;
}*NODOPILHA;

// Estrutura de dados Cabeçalho da Pilha
typedef struct Head{
    int tamanho;
    NODOPILHA topo;
}HEADERPILHA;

// Estrutura de dados para Lista Estática
typedef struct Nodo_Estatica{
    int matriz[30][30];
    int entrada, saida;
}LISTA;

// Protótipos de função
NODOPILHA Cria_Nodo();
void inicializa_pilha(HEADERPILHA *P);
void gera_labirinto(LISTA *labirinto);
void imprime_labirinto(LISTA *labirinto);
void movimenta_rato(LISTA *labirinto, HEADERPILHA *P);
void push(HEADERPILHA *P, int linha, int coluna);
int pop(HEADERPILHA *P);

// Principal ---------------------------------------------------
int main(){
    LISTA lab;
    HEADERPILHA P;

    SetConsoleOutputCP(CP_UTF8); //Garante que o terminal mostre os caracteres em UTF8

    inicializa_pilha(&P);
    gera_labirinto(&lab);
    movimenta_rato(&lab, &P);

    return 0;
}

// Implementação das funções

NODOPILHA Cria_Nodo(){
    NODOPILHA p;

    p = (NODOPILHA) malloc(sizeof(struct Nodo_Pilha));

    if(!p){
        printf("Erro de alocacao!\n");
        exit(0);
    }

    return p;
}

// Função que gera a matriz do labirinto:
void gera_labirinto(LISTA *labirinto){
    int i, j;
    srand(time(NULL)); //Inicializa rand()

    for(i = 0; i < 30; i++){
        for(j = 0; j < 30; j++){

            //Se for uma borda
            if(i == 0 || i == 29 ||
               j == 0 || j == 29){
                    labirinto->matriz[i][j] = 1; //Sempre será parede
            }

            //Entrada e saida são livres
            //Se for entrada
            else if(i == 2 && j == 2){
                labirinto->entrada = (i * 100) + j; //Salva a posição de entrada
                labirinto->matriz[i][j] = 0; //Define como livre
            }
            //Se for saida
            else if(i == 28 && j == 28){
                labirinto->saida = (i * 100) + j; //Salva a posição de saida
                labirinto->matriz[i][j] = 0; //Define como livre
            }

            //Gera um labirinto aleatório
            else{
                int marca = rand() % 2;
                labirinto->matriz[i][j] = marca;
            }
        }
    }
}

void inicializa_pilha(HEADERPILHA *P){
    P->tamanho = 0;
    P->topo = NULL;
}

// Função que imprime o estado atual do labirinto
void imprime_labirinto(LISTA *labirinto){
    int i, j;

    Sleep(1000); // Aguarda um segundo
    system("cls"); // Limpa a tela

    for(i = 0; i < 30; i++){
        for(j = 0; j < 30; j++){
            if(labirinto->matriz[i][j] == 0){
                printf("  ");
            }
            else if(labirinto->matriz[i][j] == 1){
                printf("■ ");
            }
            else if(labirinto->matriz[i][j] == 2){
                printf(". ");
            }
            else if(labirinto->matriz[i][j] == 3){
                printf("░ ");
            }
            else if(labirinto->matriz[i][j] == 9){
                printf("☺ ");
            }
            else{
                printf("☻ ");
            }
        }
        printf("\n");
    }
}

void push(HEADERPILHA *P, int linha, int coluna){
    int posicao = 0;
    NODOPILHA novo;
    novo = Cria_Nodo();
    posicao = linha * 100 + coluna; //Calcula linha e coluna como um unico inteiro
    novo->posicao = posicao;

    if(P->tamanho == 0){
        novo->prox = NULL;
        P->topo = novo;
    }
    else{
        novo->prox = P->topo;
        P->topo = novo;
    }

    P->tamanho++;

}

int pop(HEADERPILHA *P){
    NODOPILHA aux;

    aux = P->topo;
    P->topo = P->topo->prox;
    free(aux);
    P->tamanho--;

    //Se não houver mais como retroceder
    if(P->tamanho == 0){
        return 0; //Não há um caminho, retorna 0 (falso)
    }

    return 1; //Ainda há um caminho, retorna 1 (verdadeiro)

}

void movimenta_rato(LISTA *labirinto, HEADERPILHA *P){
    int i, j;
    int posicao_atual = 0, lin = 0, col = 0, caminho = 1;


    do{
        //Posição inicial do rato:
        if(P->tamanho == 0){
            push(P, 2, 2);
            labirinto->matriz[2][2] = 9;
        }
        else{
            lin = P->topo->posicao / 100; //Calcula a linha em que o rato está
            col = P->topo->posicao % 100; //Calcula a coluna em que o rato está

            //Se a posição acima está livre, movimenta para cima
            if(labirinto->matriz[lin-1][col] == 0){
                push(P, lin-1, col);
                labirinto->matriz[lin][col] = 2;
                labirinto->matriz[lin-1][col] = 9;
            }
            //Se a posição abaixo está livre, movimenta para baixo
            else if(labirinto->matriz[lin+1][col] == 0){
                push(P, lin+1, col);
                labirinto->matriz[lin][col] = 2;
                labirinto->matriz[lin+1][col] = 9;
            }
            //Se a posição a esquerda está livre, movimenta para esquerda
            else if(labirinto->matriz[lin][col-1] == 0){
                push(P, lin, col-1);
                labirinto->matriz[lin][col] = 2;
                labirinto->matriz[lin][col-1] = 9;
            }
            //Se a posição a direita está livre, movimenta para direita
            else if(labirinto->matriz[lin][col+1] == 0){
                push(P, lin, col+1);
                labirinto->matriz[lin][col] = 2;
                labirinto->matriz[lin][col+1] = 9;
            }
            //Senão, retrocede
            else{
                labirinto->matriz[lin][col] = 3; //Marca atual como beco
                caminho = pop(P);

                if(caminho == 0){
                    labirinto->matriz[lin][col] = 6; //Se não há caminho, o rato morre
                }
                else{
                    lin = P->topo->posicao / 100; //Calcula a linha em que o rato retrocedeu
                    col = P->topo->posicao % 100; //Calcula a coluna em que o rato retrocedeu

                    labirinto->matriz[lin][col] = 9;
                }
            }
        }
        imprime_labirinto(labirinto);
    }while((caminho == 1) && (P->topo->posicao != labirinto->saida)); //Executa enquanto não encontrar a saida e haver um caminho
}
