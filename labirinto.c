/* TRABALHO II - LABIRINTO
    Discente: Ysis Barduco Straub de Lima
    Discente: Ariane de Oliveira Neves
 */

#include <stdio.h>
#include <stdlib.h>

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
    int inicio, fim;
}LISTA;

// Protótipos de função
NODOPILHA Cria_Nodo();
void gera_labirinto();
void movimenta_rato();
void push();
void pop();

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
    //Bordas sempre são paredes
    //Entrada e saida são livres
    //Gera um labirinto aleatório

// Função que movimenta o rato
    //Enquanto não encontrar a saida
    //Verifica se a posição que a direção aponta é livre
        //Se sim, empilha nova posição
        //Se não, procura outra posição livre
            //Se não há posição livre, marca atual como beco e retrocede para ultima visitada