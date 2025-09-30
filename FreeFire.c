#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10   // capacidade máxima da mochila (vetor)

// ==============================
// Structs
// ==============================

// Item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ==============================
// Variáveis globais para estatísticas
// ==============================
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ==============================
// Funções para o VETOR
// ==============================

void listarItensVetor(Item mochila[], int numItens) {
    printf("\n📦 Mochila (Vetor):\n");
    if (numItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    for (int i = 0; i < numItens; i++) {
        printf("%d. %s (%s) x%d\n", i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

void inserirItemVetor(Item mochila[], int *numItens) {
    if (*numItens >= MAX_ITENS) {
        printf("❌ Mochila cheia!\n");
        return;
    }
    Item novo;
    printf("Digite nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Digite tipo: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Digite quantidade: ");
    scanf("%d", &novo.quantidade);
    mochila[*numItens] = novo;
    (*numItens)++;
}

void removerItemVetor(Item mochila[], int *numItens) {
    if (*numItens == 0) {
        printf("❌ Mochila já está vazia!\n");
        return;
    }
    char nome[30];
    printf("Digite nome do item a remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < *numItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*numItens)--;
            printf("✅ Item removido!\n");
            return;
        }
    }
    printf("❌ Item não encontrado.\n");
}

// Busca sequencial no vetor
int buscarSequencialVetor(Item mochila[], int numItens, char nome[]) {
    comparacoesSequencial = 0;
    for (int i = 0; i < numItens; i++) {
        comparacoesSequencial++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

// Ordenação (Bubble Sort por nome)
void ordenarVetor(Item mochila[], int numItens) {
    for (int i = 0; i < numItens - 1; i++) {
        for (int j = 0; j < numItens - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j+1].nome) > 0) {
                Item temp = mochila[j];
                mochila[j] = mochila[j+1];
                mochila[j+1] = temp;
            }
        }
    }
    printf("✅ Mochila (vetor) ordenada por nome!\n");
}

// Busca binária no vetor
int buscarBinariaVetor(Item mochila[], int numItens, char nome[]) {
    comparacoesBinaria = 0;
    int esq = 0, dir = numItens - 1;
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(mochila[meio].nome, nome);
        if (cmp == 0) return meio;
        if (cmp < 0) esq = meio + 1;
        else dir = meio - 1;
    }
    return -1;
}

// ==============================
// Funções para a LISTA ENCADEADA
// ==============================

void listarItensLista(No* inicio) {
    printf("\n🔗 Mochila (Lista Encadeada):\n");
    if (!inicio) {
        printf("Mochila vazia!\n");
        return;
    }
    int i = 1;
    for (No* p = inicio; p != NULL; p = p->proximo) {
        printf("%d. %s (%s) x%d\n", i++, p->dados.nome, p->dados.tipo, p->dados.quantidade);
    }
}

void inserirItemLista(No** inicio) {
    No* novo = (No*) malloc(sizeof(No));
    printf("Digite nome: ");
    scanf(" %[^\n]", novo->dados.nome);
    printf("Digite tipo: ");
    scanf(" %[^\n]", novo->dados.tipo);
    printf("Digite quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    novo->proximo = *inicio;
    *inicio = novo;
}

void removerItemLista(No** inicio) {
    if (*inicio == NULL) {
        printf("❌ Mochila já está vazia!\n");
        return;
    }
    char nome[30];
    printf("Digite nome do item a remover: ");
    scanf(" %[^\n]", nome);

    No* atual = *inicio;
    No* anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("❌ Item não encontrado.\n");
        return;
    }

    if (anterior == NULL) { // removendo o primeiro
        *inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    printf("✅ Item removido!\n");
}

// Busca sequencial na lista encadeada
No* buscarSequencialLista(No* inicio, char nome[]) {
    comparacoesSequencial = 0;
    for (No* p = inicio; p != NULL; p = p->proximo) {
        comparacoesSequencial++;
        if (strcmp(p->dados.nome, nome) == 0) {
            return p;
        }
    }
    return NULL;
}

// ==============================
// Programa Principal
// ==============================
int main() {
    Item mochilaVetor[MAX_ITENS];
    int numItensVetor = 0;

    No* mochilaLista = NULL;

    int opcao, estrutura;

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("Escolha a estrutura de dados:\n");
        printf("1. Vetor (lista sequencial)\n");
        printf("2. Lista Encadeada\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &estrutura);

        if (estrutura == 0) break;

        do {
            printf("\n--- MENU MOCHILA ---\n");
            printf("1. Inserir item\n");
            printf("2. Remover item\n");
            printf("3. Listar itens\n");
            printf("4. Buscar item (sequencial)\n");
            if (estrutura == 1) {
                printf("5. Ordenar vetor por nome\n");
                printf("6. Buscar item (binária)\n");
            }
            printf("0. Voltar\n");
            printf("Opcao: ");
            scanf("%d", &opcao);

            if (estrutura == 1) { // VETOR
                switch (opcao) {
                    case 1: inserirItemVetor(mochilaVetor, &numItensVetor); break;
                    case 2: removerItemVetor(mochilaVetor, &numItensVetor); break;
                    case 3: listarItensVetor(mochilaVetor, numItensVetor); break;
                    case 4: {
                        char nome[30];
                        printf("Digite o nome: ");
                        scanf(" %[^\n]", nome);
                        int pos = buscarSequencialVetor(mochilaVetor, numItensVetor, nome);
                        if (pos != -1) {
                            printf("✅ Encontrado: %s (%s) x%d\n", mochilaVetor[pos].nome,
                                   mochilaVetor[pos].tipo, mochilaVetor[pos].quantidade);
                        } else printf("❌ Não encontrado.\n");
                        printf("Comparações: %d\n", comparacoesSequencial);
                        break;
                    }
                    case 5: ordenarVetor(mochilaVetor, numItensVetor); break;
                    case 6: {
                        char nome[30];
                        printf("Digite o nome: ");
                        scanf(" %[^\n]", nome);
                        int pos = buscarBinariaVetor(mochilaVetor, numItensVetor, nome);
                        if (pos != -1) {
                            printf("✅ Encontrado: %s (%s) x%d\n", mochilaVetor[pos].nome,
                                   mochilaVetor[pos].tipo, mochilaVetor[pos].quantidade);
                        } else printf("❌ Não encontrado.\n");
                        printf("Comparações: %d\n", comparacoesBinaria);
                        break;
                    }
                }
            } else if (estrutura == 2) { // LISTA
                switch (opcao) {
                    case 1: inserirItemLista(&mochilaLista); break;
                    case 2: removerItemLista(&mochilaLista); break;
                    case 3: listarItensLista(mochilaLista); break;
                    case 4: {
                        char nome[30];
                        printf("Digite o nome: ");
                        scanf(" %[^\n]", nome);
                        No* achado = buscarSequencialLista(mochilaLista, nome);
                        if (achado != NULL) {
                            printf("✅ Encontrado: %s (%s) x%d\n", achado->dados.nome,
                                   achado->dados.tipo, achado->dados.quantidade);
                        } else printf("❌ Não encontrado.\n");
                        printf("Comparações: %d\n", comparacoesSequencial);
                        break;
                    }
                }
            }

        } while (opcao != 0);

    } while (estrutura != 0);

    printf("\n👋 Encerrando o programa!\n");
    return 0;
}