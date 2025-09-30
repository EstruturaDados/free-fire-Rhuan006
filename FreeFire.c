#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// ==============================
// Struct do Componente
// ==============================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ==============================
// Funções de ordenação
// ==============================

// Bubble Sort por nome
int bubbleSortNome(Componente arr[], int n) {
    int comparacoes = 0;
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            comparacoes++;
            if(strcmp(arr[j].nome, arr[j+1].nome) > 0) {
                Componente tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
    return comparacoes;
}

// Insertion Sort por tipo
int insertionSortTipo(Componente arr[], int n) {
    int comparacoes = 0;
    for(int i=1; i<n; i++) {
        Componente key = arr[i];
        int j = i-1;
        while(j >= 0 && (comparacoes++, strcmp(arr[j].tipo, key.tipo) > 0)) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
    return comparacoes;
}

// Selection Sort por prioridade
int selectionSortPrioridade(Componente arr[], int n) {
    int comparacoes = 0;
    for(int i=0; i<n-1; i++) {
        int min_idx = i;
        for(int j=i+1; j<n; j++) {
            comparacoes++;
            if(arr[j].prioridade < arr[min_idx].prioridade)
                min_idx = j;
        }
        Componente tmp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = tmp;
    }
    return comparacoes;
}

// ==============================
// Busca binária por nome
// ==============================
int buscaBinariaPorNome(Componente arr[], int n, char chave[], int *comparacoes) {
    int esq = 0, dir = n-1;
    *comparacoes = 0;
    while(esq <= dir) {
        int meio = (esq + dir) / 2;
        (*comparacoes)++;
        int cmp = strcmp(arr[meio].nome, chave);
        if(cmp == 0) return meio;
        else if(cmp < 0) esq = meio+1;
        else dir = meio-1;
    }
    return -1;
}

// ==============================
// Mostrar componentes
// ==============================
void mostrarComponentes(Componente arr[], int n) {
    printf("\n┌───────────────────────────────┐\n");
    printf("│     Componentes da Torre      │\n");
    printf("├─────────────┬─────────────┬───────────┤\n");
    printf("│ Nome        │ Tipo        │ Prioridade│\n");
    printf("├─────────────┼─────────────┼───────────┤\n");
    for(int i=0; i<n; i++) {
        printf("│ %-11s │ %-11s │ %-9d │\n", arr[i].nome, arr[i].tipo, arr[i].prioridade);
    }
    printf("└─────────────┴─────────────┴───────────┘\n");
}

// ==============================
// Função para medir tempo
// ==============================
double medirTempo(int (*algoritmo)(Componente[], int), Componente arr[], int n, int *comparacoes) {
    Componente copia[MAX_COMPONENTES];
    memcpy(copia, arr, n * sizeof(Componente));

    clock_t inicio = clock();
    *comparacoes = algoritmo(copia, n);
    clock_t fim = clock();

    // Atualiza o vetor original com a ordenação
    memcpy(arr, copia, n * sizeof(Componente));

    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

// ==============================
// Função para cadastrar componente
// ==============================
void cadastrarComponente(Componente arr[], int *num) {
    if(*num >= MAX_COMPONENTES) {
        printf("\n❌ Limite de componentes atingido!\n");
        return;
    }

    printf("\n➕ CADASTRAR COMPONENTE %d\n", *num + 1);
    printf("Nome: ");
    scanf(" %[^\n]", arr[*num].nome);
    printf("Tipo: ");
    scanf(" %[^\n]", arr[*num].tipo);
    printf("Prioridade (1 a 10): ");
    scanf("%d", &arr[*num].prioridade);

    (*num)++;
    printf("✅ Componente adicionado!\n");
}

// ==============================
// Programa Principal
// ==============================
int main() {
    Componente torre[MAX_COMPONENTES];
    int numComponentes = 0;
    int opcao;

    do {
        printf("\n🎮 === MONTAGEM DA TORRE DE FUGA === 🎮\n");
        printf("1 - Cadastrar componente\n");
        printf("2 - Ordenar por nome (Bubble Sort)\n");
        printf("3 - Ordenar por tipo (Insertion Sort)\n");
        printf("4 - Ordenar por prioridade (Selection Sort)\n");
        printf("5 - Mostrar componentes\n");
        printf("6 - Buscar componente-chave (Binária)\n");
        printf("0 - Sair\n");
        printf("----------------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarComponente(torre, &numComponentes);
                break;
            case 2: {
                int comparacoes;
                double tempo = medirTempo(bubbleSortNome, torre, numComponentes, &comparacoes);
                printf("\n✅ Ordenação por nome concluída!\n");
                printf("Comparações: %d\n", comparacoes);
                printf("Tempo: %.6f segundos\n", tempo);
                break;
            }
            case 3: {
                int comparacoes;
                double tempo = medirTempo(insertionSortTipo, torre, numComponentes, &comparacoes);
                printf("\n✅ Ordenação por tipo concluída!\n");
                printf("Comparações: %d\n", comparacoes);
                printf("Tempo: %.6f segundos\n", tempo);
                break;
            }
            case 4: {
                int comparacoes;
                double tempo = medirTempo(selectionSortPrioridade, torre, numComponentes, &comparacoes);
                printf("\n✅ Ordenação por prioridade concluída!\n");
                printf("Comparações: %d\n", comparacoes);
                printf("Tempo: %.6f segundos\n", tempo);
                break;
            }
            case 5:
                mostrarComponentes(torre, numComponentes);
                break;
            case 6: {
                if(numComponentes == 0) {
                    printf("\n⚠️ Nenhum componente cadastrado!\n");
                    break;
                }
                char chave[30];
                printf("\n🔎 Buscar componente-chave (por nome): ");
                scanf(" %[^\n]", chave);
                int comparacoes;
                int pos = buscaBinariaPorNome(torre, numComponentes, chave, &comparacoes);
                if(pos != -1) {
                    printf("🎯 Componente encontrado!\n");
                    printf("Nome: %s | Tipo: %s | Prioridade: %d\n", torre[pos].nome, torre[pos].tipo, torre[pos].prioridade);
                } else {
                    printf("❌ Componente não encontrado!\n");
                }
                printf("Comparações: %d\n", comparacoes);
                break;
            }
            case 0:
                printf("\n👋 Encerrando o jogo...\n");
                break;
            default:
                printf("\n⚠️ Opção inválida!\n");
        }

        if(opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar(); getchar(); // pausa
        }

    } while(opcao != 0);

    return 0;
}