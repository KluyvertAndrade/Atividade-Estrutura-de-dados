#include <stdio.h>
#include <stdlib.h>

// Definição do nó da lista
typedef struct No {
    int dado;
    struct No* proximo;
} No;

// Definição da lista
typedef struct Lista {
    No* cabeca;
} Lista;

// Função para criar uma lista
Lista* criarLista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    if (!lista) {
        fprintf(stderr, "Falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    lista->cabeca = NULL;
    return lista;
}

// Função para verificar se a lista está vazia
int verificarVazia(Lista* lista) {
    return lista->cabeca == NULL;
}

// Função para inserir na lista em ordem crescente
void inserirLista(Lista* lista, int dado) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (!novoNo) {
        fprintf(stderr, "Falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    novoNo->dado = dado;
    novoNo->proximo = NULL;

    // Inserir no início ou em posição ordenada
    if (lista->cabeca == NULL || lista->cabeca->dado >= dado) {
        novoNo->proximo = lista->cabeca;
        lista->cabeca = novoNo;
    } else {
        No* atual = lista->cabeca;
        while (atual->proximo != NULL && atual->proximo->dado < dado) {
            atual = atual->proximo;
        }
        novoNo->proximo = atual->proximo;
        atual->proximo = novoNo;
    }
}

// Função para exibir a lista
void exibirLista(Lista* lista) {
    No* atual = lista->cabeca;
    while (atual != NULL) {
        printf("%d -> ", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

// Função para buscar um elemento na lista
No* buscarLista(Lista* lista, int dado) {
    No* atual = lista->cabeca;
    while (atual != NULL) {
        if (atual->dado == dado) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

// Função para excluir um elemento da lista
void excluirLista(Lista* lista, int dado) {
    No* atual = lista->cabeca;
    No* anterior = NULL;

    while (atual != NULL && atual->dado != dado) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual != NULL) {
        if (anterior == NULL) { // O elemento a ser excluído é o primeiro
            lista->cabeca = atual->proximo;
        } else {
            anterior->proximo = atual->proximo;
        }
        free(atual);
    } else {
        printf("Elemento %d não encontrado na lista.\n", dado);
    }
}

// Função para liberar a lista
void liberarLista(Lista* lista) {
    No* atual = lista->cabeca;
    No* proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(lista);
}

// Função principal para teste
int main() {
    Lista* lista = criarLista();

    // Inserir elementos
    inserirLista(lista, 5);
    inserirLista(lista, 3);
    inserirLista(lista, 8);
    inserirLista(lista, 1);
    inserirLista(lista, 7);

    // Exibir lista
    printf("Lista: ");
    exibirLista(lista);

    // Buscar elemento
    No* resultado = buscarLista(lista, 3);
    if (resultado) {
        printf("Elemento %d encontrado.\n", resultado->dado);
    } else {
        printf("Elemento não encontrado.\n");
    }

    // Excluir elemento
    excluirLista(lista, 5);
    printf("Lista após exclusão do 5: ");
    exibirLista(lista);

    // Tentar excluir um elemento que não existe
    excluirLista(lista, 10);

    // Liberar a lista
    liberarLista(lista);
    return 0;
}