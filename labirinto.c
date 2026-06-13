/* TRABALHO II - LABIRINTO
    Discente: Ysis Barduco Straub de Lima
    Discente: Ariane de Oliveira Neves
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
void gera_labirinto(LISTA *labirinto);
void imprime_labirinto(LISTA labirinto);
void movimenta_rato();
void push();
void pop();

// Principal ---------------------------------------------------
int main(){
    LISTA lab;

    gera_labirinto(&lab);
    imprime_labirinto(lab);

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

// Função que imprime o estado atual do labirinto
void imprime_labirinto(LISTA labirinto){
    int i, j;

    system("cls"); // Limpa a tela

    for(i = 0; i < 30; i++){
        for(j = 0; j < 30; j++){
            printf("%d ", labirinto.matriz[i][j]); // Imprime a marca da posição
        }
        printf("\n");
    }
}

void push(HEADERPILHA *P, int linha, int coluna){
    int posicao = 0;
    NODOPILHA novo;

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
    int posicao_beco = 0;

    //Se o rato não tiver se movimentado
    if(P->tamanho == 0){
        return 202; //Retorna posição do inicio
    }

    aux = P->topo;
    posicao_beco = P->topo->posicao;
    P->topo = P->topo->prox;
    free(aux);
    P->tamanho--;

    return posicao_beco; //Retorna a posição que o rato estava

}

// Função que movimenta o rato
    //Enquanto não encontrar a saida
    //Verifica se a posição que a direção aponta é livre
        //Se sim, empilha nova posição
        //Se não, procura outra posição livre
            //Se não há posição livre, marca atual como beco e retrocede para ultima visitada



