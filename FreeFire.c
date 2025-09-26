// Código da Ilha – Edição Free Fire

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <stdbool.h>

#define MAX_ITENS 10 // capacidade máxima da mochila

//Struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Funções de interface

// Titulo
void exibirTitulo() {
    printf("=========================================\n");
    printf("      🎒 MOCHILA DE SOBREVIVÊNCIA 🎮\n");
    printf("=========================================\n");
}

// Lista todos os itens areos na mochila
void listarItens(Item mochila[], int numItens) {
    printf("\n📜 INVENTÁRIO ATUAL: \n");
    if (numItens == 0) {
        printf("⚠️  A mochila está vazia!\n");
        return;
    }

    printf("┌──────────────────────┬───────────────┬─────────────┐\n");
    printf("│ %-20s │ %-13s │ %-11s│\n", "Nome", "Tipo", "Quantidade");
    printf("├──────────────────────┼───────────────┼─────────────┤\n");

    for (int i = 0; i < numItens; i++) {
        printf("| %-20s | %-13s | %-11d |\n",
                mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }

    printf("└──────────────────────┴───────────────┴─────────────┘\n");

}

// Inseri um novo item
void inserirItem(Item mochila[], int *numItens) {
    if(*numItens >= MAX_ITENS) {
        printf("\n❌ A mochila está cheia!\n");
        return;
    }

    Item novo;
    printf("\n➕ CADASTRAR NOVO ITEM:\n");

    printf("Digite o nome do item: ");
    scanf(" %[^\n]", novo.nome);

    printf("Digite o tipo do item: ");
    scanf(" %[^\n]", novo.tipo);

    printf("Digite a quantidade: ");
    scanf(" %d", &novo.quantidade);

    mochila[*numItens] = novo;
    (*numItens)++;

     printf("\n✅ Item adicionado com sucesso!\n");
}

void removerItem(Item mochila[], int *numItens) {
    if (numItens == 0) {
        printf("\n⚠️  A mochila está vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n❌ REMOVER ITEM\nDigite o nome do item: ");
    scanf(" %[^\n]", nomeBusca);

    int encontrado = -1;
    for (int i = 0;i < *numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\n⚠️ Item não encontrado!\n");
    } else {
        for (int i = encontrado; i < *numItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        (*numItens)--;
         printf("\n✅ Item removido com sucesso!\n");
    }
}

//Buscar item por nome
void buscarItem(Item mochila[], int numItens) {
    if (numItens == 0) {
        printf("\n⚠️  A mochila está vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n🔎 BUSCAR ITEM\nDigite o nome do item: ");
    scanf(" %[^\n]", nomeBusca);

    int encontrado = -1;
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\n⚠️  Item não encontrado!\n");
    } else {
         printf("\n🎯 Item encontrado!\n");
        printf("┌───────────────────────────┐\n");
        printf("│ Nome: %-20s │\n", mochila[encontrado].nome);
        printf("│ Tipo: %-20s │\n", mochila[encontrado].tipo);
        printf("│ Quantidade: %-13d │\n", mochila[encontrado].quantidade);
        printf("└───────────────────────────┘\n");
    }
}

// Programa Principal
int main() {
    Item mochila[MAX_ITENS];
    int numItens = 0;
    int opcao;

    // Menu principal com opções:
    do {
        exibirTitulo();
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item por nome\n");
        printf("0 - Sair\n");
        printf("-----------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &numItens);
                break;
            case 2:
                removerItem(mochila, &numItens);
                break;
            case 3:
                listarItens(mochila, numItens);
                break;
            case 4:
                buscarItem(mochila, numItens);
                break;
             case 0:
                printf("\n👋 Saindo do jogo... até a próxima!\n");
                break;
            default:
                printf("\n⚠️  Opção inválida!\n");
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar(); getchar(); // pausa
        }
    } while (opcao != 0);

    
    return 0;
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
