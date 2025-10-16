// Sistema_Inventario_Mochila.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
  Sistema de inventário — mochila inicial
  - Até 10 itens (vetor de structs)
  - Operações: inserir, remover, listar, buscar
  - Comentado e organizado para facilitar manutenção
*/

// CONSTANTES
#define MAX_ITENS 10
#define MAX_NOME 30
#define MAX_TIPO 20

// STRUCT: Item
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
} Item;

// VETOR GLOBAL (mochila) e contador
Item mochila[MAX_ITENS];
int totalItens = 0;

// PROTÓTIPOS (evita implicit declaration)
void inserirItem(void);
void removerItem(void);
void listarItens(void);
void buscarItem(void);
void limparBuffer(void);

// IMPLEMENTAÇÃO

// limpa caracteres remanescentes do stdin (para usar scanf e fgets com segurança)
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// Insere um novo item (se houver espaço)
void inserirItem(void) {
    if (totalItens >= MAX_ITENS) {
        printf("❌ A mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\n=== CADASTRO DE ITEM ===\n");

    // leitura de strings com espaços: usamos scanf(" %[^\n]", ...) para ler até o Enter
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", novo.nome);

    printf("Digite o tipo do item (arma, municao, cura, ferramenta...): ");
    scanf(" %[^\n]", novo.tipo);

    printf("Digite a quantidade: ");
    if (scanf("%d", &novo.quantidade) != 1) {
        printf("Entrada inválida para quantidade. Operação cancelada.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    mochila[totalItens] = novo;
    totalItens++;
    printf("✅ Item '%s' adicionado com sucesso!\n", novo.nome);

    // listar automaticamente após operação (melhora usabilidade)
    listarItens();
}

// Remove um item pelo nome (busca sequencial)
void removerItem(void) {
    if (totalItens == 0) {
        printf("❌ A mochila está vazia. Nada para remover.\n");
        return;
    }

    char nomeBusca[MAX_NOME];
    printf("\n=== REMOVER ITEM ===\n");
    printf("Digite o nome do item a ser removido: ");
    scanf(" %[^\n]", nomeBusca);

    int encontrado = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
        return;
    }

    // desloca elementos à esquerda para preencher o índice removido
    for (int i = encontrado; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    totalItens--;
    printf("✅ Item '%s' removido com sucesso!\n", nomeBusca);

    // listar automaticamente após operação
    listarItens();
}

// Lista todos os itens
void listarItens(void) {
    printf("\n=== LISTA DE ITENS DA MOCHILA ===\n");
    if (totalItens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Busca sequencial por nome e mostra os dados do item
void buscarItem(void) {
    if (totalItens == 0) {
        printf("❌ A mochila está vazia. Nada para buscar.\n");
        return;
    }

    char nomeBusca[MAX_NOME];
    printf("\n=== BUSCAR ITEM ===\n");
    printf("Digite o nome do item que deseja encontrar: ");
    scanf(" %[^\n]", nomeBusca);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("✅ Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }
    printf("❌ Item '%s' não foi encontrado na mochila.\n", nomeBusca);
}

// MAIN: menu interativo
int main(void) {
    int opcao;

    do {
        printf("\n==============================\n");
        printf("🎒 SISTEMA DE INVENTÁRIO\n");
        printf("==============================\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("==============================\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            limparBuffer();
            opcao = -1;
        } else {
            limparBuffer();
        }

        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: buscarItem(); break;
            case 0: printf("🚪 Saindo do sistema...\n"); break;
            default: printf("❌ Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
