#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct {
    char nome[30];  
    char cor[10];   
    int tropas;    
} Territorio;


typedef struct {
    char atacante[30];  
    char defensor[30];  
    int dado_atacante;  
    int dado_defensor;  
    char resultado[50]; 
} Ataque;


void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void cadastrar_territorios(Territorio* mapa, int num_territorios) {
    for (int i = 0; i < num_territorios; i++) {
        printf("Digite o nome do território %d: ", i + 1);
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0; 

        printf("Digite a cor do exército (dono) do território %d: ", i + 1);
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0; 

        printf("Digite o número de tropas no território %d: ", i + 1);
        scanf("%d", &mapa[i].tropas);
        limpar_buffer();
    }
}


void exibir_territorios(Territorio* mapa, int num_territorios) {
    printf("\n--- Territórios Cadastrados ---\n");
    for (int i = 0; i < num_territorios; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor (Dono): %s\n", mapa[i].cor);
        printf("  Tropas: %d\n", mapa[i].tropas);
        printf("-----------------------------\n");
    }
}


void exibir_historico_ataques(Ataque* historico_ataques, int num_ataques) {
    printf("\n--- Histórico de Ataques ---\n");
    if (num_ataques == 0) {
        printf("Nenhum ataque realizado ainda.\n");
    } else {
        for (int i = 0; i < num_ataques; i++) {
            printf("Ataque %d:\n", i + 1);
            printf("  Atacante: %s\n", historico_ataques[i].atacante);
            printf("  Defensor: %s\n", historico_ataques[i].defensor);
            printf("  Dado Atacante: %d\n", historico_ataques[i].dado_atacante);
            printf("  Dado Defensor: %d\n", historico_ataques[i].dado_defensor);
            printf("  Resultado: %s\n", historico_ataques[i].resultado);
            printf("-----------------------------\n");
        }
    }
}


void atacar(Territorio* atacante, Territorio* defensor, Ataque* historico_ataques, int* num_ataques) {
    if (atacante->tropas < 2) {
        printf("impossível: ALERTA DO PH! Atacante não tem tropas suficientes.\n");
        return;
    }

    int dado_atacante = rand() % 6 + 1;
    int dado_defensor = rand() % 6 + 1;

    printf("Resultado do ataque:\n");
    printf("Dado Atacante (%s): %d\n", atacante->nome, dado_atacante);
    printf("Dado Defensor (%s): %d\n", defensor->nome, dado_defensor);

    strcpy(historico_ataques[*num_ataques].atacante, atacante->nome);
    strcpy(historico_ataques[*num_ataques].defensor, defensor->nome);
    historico_ataques[*num_ataques].dado_atacante = dado_atacante;
    historico_ataques[*num_ataques].dado_defensor = dado_defensor;

    if (dado_atacante > dado_defensor) {
        strcpy(defensor->cor, atacante->cor);
        int tropas_transferidas = atacante->tropas / 2;
        defensor->tropas = tropas_transferidas;
        atacante->tropas -= tropas_transferidas;
        strcpy(historico_ataques[*num_ataques].resultado, "AGORA PODE IR PRA VALHALLA! Território conquistado.");
        printf("AGORA PODE IR PRA VALHALLA! Território conquistado2.\n");
    } else {
        atacante->tropas--;
        strcpy(historico_ataques[*num_ataques].resultado, "Defensor venceu! Atacante perdeu uma tropa.");
        printf("Defensor venceu! Atacante perdeu uma tropa.\n");
    }

    (*num_ataques)++;
}

void liberar_memoria(Territorio* mapa, Ataque* historico_ataques) {
    free(mapa);
    free(historico_ataques);
    printf("Memória liberada com sucesso.\n");
}

int main() {
    srand(time(NULL));

    int num_territorios;
    printf("Digite o número total de territórios: ");
    scanf("%d", &num_territorios);
    limpar_buffer();

    Territorio* mapa = (Territorio*) calloc(num_territorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    Ataque* historico_ataques = (Ataque*) calloc(100, sizeof(Ataque));
    if (historico_ataques == NULL) {
        printf("Erro ao alocar memória para histórico.\n");
        free(mapa);
        return 1;
    }
    int num_ataques = 0;

    cadastrar_territorios(mapa, num_territorios);

    int opcao;
    do {
        printf("\n--- Menu do Jogo WAR ---\n");
        printf("1 - Exibir territórios\n");
        printf("2 - Realizar ataque\n");
        printf("3 - Exibir histórico de ataques\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1:
                exibir_territorios(mapa, num_territorios);
                break;
            case 2: {
                int idx_atacante, idx_defensor;
                printf("Digite o índice do território atacante (1 a %d): ", num_territorios);
                scanf("%d", &idx_atacante);
                limpar_buffer();
                idx_atacante--;
                printf("Digite o índice do território defensor (1 a %d): ", num_territorios);
                scanf("%d", &idx_defensor);
                limpar_buffer();
                idx_defensor--; 

                if (idx_atacante < 0 || idx_atacante >= num_territorios ||
                    idx_defensor < 0 || idx_defensor >= num_territorios) {
                    printf("Índices inválidos.\n");
                    break;
                }
                if (strcmp(mapa[idx_atacante].cor, mapa[idx_defensor].cor) == 0) {
                    printf("Não é possível atacar um território do mesmo dono.\n");
                    break;
                }

            
                atacar(&mapa[idx_atacante], &mapa[idx_defensor], historico_ataques, &num_ataques);
                break;
            }
            case 3:
                exibir_historico_ataques(historico_ataques, num_ataques);
                break;
            case 0:
                liberar_memoria(mapa, historico_ataques);
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
