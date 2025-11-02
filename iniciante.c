#include <stdio.h>
#include <string.h>

#define max_territorio 30
#define MAX_TROPAS 30

typedef struct {
    char territorio[max_territorio];
    char cor;
    int num_tropas;
    int Tropas[MAX_TROPAS];
} Jogador;

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Jogador jogadores[MAX_TROPAS];
    int num_jogadores = 0;
    int opcao;

    do {
        printf("🇧🇷 🇳🇿 🇹🇷 🇸🇪 🇿🇦 🇰🇷 🇨🇦 🇲🇽 🇪🇬 🇦🇷\n");
        printf("  escolha \n");
        printf("🟢⚪🔵🔴🟡⚫🟠🟣🟤🔶\n");
        printf("1 - cadastrar nova tropa \n");
        printf("2 - listar tropas\n");
        printf("0 - voltar\n");
        printf("----------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1:
                if (num_jogadores < MAX_TROPAS) {
                    printf("Digite o nome do territorio: ");
                    fgets(jogadores[num_jogadores].territorio, max_territorio, stdin);
                    jogadores[num_jogadores].territorio[strcspn(jogadores[num_jogadores].territorio, "\n")] = 0; // Remove newline

                    printf("Digite a cor do Território (um caractere): ");
                    scanf(" %c", &jogadores[num_jogadores].cor);
                    limpar_buffer();

                    printf("Digite a quantidade de tropas (max %d): ", MAX_TROPAS);
                    scanf("%d", &jogadores[num_jogadores].num_tropas);
                    limpar_buffer();

                    for (int i = 0; i < jogadores[num_jogadores].num_tropas; i++) {
                        printf("Digite o valor da tropa %d: ", i + 1);
                        scanf("%d", &jogadores[num_jogadores].Tropas[i]);
                        limpar_buffer();
                    }

                    num_jogadores++;
                    printf("Jogador adicionado com sucesso!\n");
                } else {
                    printf("Limite de jogadores atingido!\n");
                }
                break;

            case 2:
                if (num_jogadores == 0) {
                   printf("Nenhum jogador cadastrado.\n");
                } else {
                   printf("Lista de jogadores:\n");
                   for (int i = 0; i < num_jogadores; i++) {
                      printf("Jogador %d:\n", i + 1);
                       printf("--------------------------\n");
                       printf("Territorio: %s\n", jogadores[i].territorio);
                       printf("Cor: %c\n", jogadores[i].cor);
                       printf("Tropas: ");
                       for (int j = 0; j < jogadores[i].num_tropas; j++) {
                           printf("%d ", jogadores[i].Tropas[j]);
                       }
                       printf("\n----------------------------------\n");
                       printf("\n-------------------\n");
                    }
               }
                printf("Pressione Enter para continuar...");
                getchar();
                break;

            case 0:
                printf("Voltando...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                printf("Pressione Enter para continuar...");
                getchar();
                break;
        }
    } while (opcao != 0);

    return 0;
}
