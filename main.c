#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void menu() {
    printf("1. Consultar saldo\n");
    printf("2. Consultar extrato\n");
    printf("3. Depositar\n");
    printf("4. Sacar\n");
    printf("5. Comprar criptomoedas\n");
    printf("6. Vender criptomoedas\n");
    printf("7. Atualizar cotação\n");
    printf("8. Sair\n");
    printf("\nEscolha uma opção: ");
}

void limpar_tela() {
    system("cls || clear");
}

void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar();
}

int validar_cpf(const char *cpf) {
    return strlen(cpf) == 11 && strspn(cpf, "0123456789") == 11;
}


int main() {
    int totalUsers = 0;
    char users[100][100], cpfs[100][13], senhas[100][20];

    carregar_usuarios(&totalUsers, users, cpfs, senhas);
    menu_principal(&totalUsers, users, cpfs, senhas);

    return 0;
}

void menu_principal(int totalUsers, char users[][100], char cpfs[][13], char senhas[][20]) {
    while (1) {
        printf("Menu:\n");
        printf("1. Login\n");
        printf("2. Registrar\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");

        int opcao;
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer

        switch (opcao) {
            case 1: {
                int usuarioIndex = login(totalUsers, users, cpfs, senhas);
                if (usuarioIndex < 0) {
                    continue;
                }

                float consaldo, bitcoin, ethereum, ripple;
                carregar_saldo(&consaldo, &bitcoin, &ethereum, &ripple, usuarioIndex);

                while (1) {
                    menu();
                    scanf("%d", &opcao);
                    getchar(); // Limpa o buffer

                    switch (opcao) {
                        case 1:
                            saldo(consaldo, bitcoin, ethereum, ripple);
                            break;
                        case 2:
                            carregar_extrato(usuarioIndex);
                            break;
                        case 3:
                            depositar(&consaldo);
                            salvar_saldo(consaldo, bitcoin, ethereum, ripple, usuarioIndex);
                            break;
                        case 4:
                            sacar(&consaldo);
                            salvar_saldo(consaldo, bitcoin, ethereum, ripple, usuarioIndex);
                            break;
                        case 5:
                            comprar_criptomoeda(&consaldo, &bitcoin, &ethereum, &ripple, usuarioIndex);
                            salvar_saldo(consaldo, bitcoin, ethereum, ripple, usuarioIndex);
                            break;
                        case 6:
                            vender_criptomoeda(&consaldo, &bitcoin, &ethereum, &ripple, usuarioIndex);
                            salvar_saldo(consaldo, bitcoin, ethereum, ripple, usuarioIndex);
                            break;
                        case 7:
                            atualizar_cotacao();
                            break;
                        case 8:
                            printf("Saindo...\n");
                            return;
                        default:
                            printf("Opção inválida. Tente novamente.\n");
                            pausar();
                            break;
                    }
                }
                break;
            }
            case 2:
                registrar(totalUsers, users, cpfs, senhas);
                break;
            case 3:
                printf("Saindo...\n");
                return;
            default:
                printf("Opção inválida. Tente novamente.\n");
                pausar();
                break;
        }
    }
}