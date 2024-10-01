#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void carregar_usuarios(int *totalUsers, char users[][100], char cpfs[][13], char senhas[][20]){
    FILE *file = fopen("usuarios.bin", "rb");
    if(file){
        fread(totalUsers, sizeof(int), 1, file);
        fread(users, sizeof(char[100]), *totalUsers, file);
        fread(cpfs, sizeof(char[13]), *totalUsers, file);
        fread(senhas, sizeof(char[20]), *totalUsers, file);
        fclose(file);
    }
    else{
        printf("Erro ao abrir o arquivo de usuários.\n");
    }
}



void salvar_usuarios(int totalUsers, char users[][100], char cpfs[][13], char senhas[][20]) {
    FILE *file = fopen("usuarios.bin", "wb");
    if (file) {
        fwrite(&totalUsers, sizeof(int), 1, file);
        fwrite(users, sizeof(char[100]), totalUsers, file);
        fwrite(cpfs, sizeof(char[13]), totalUsers, file);
        fwrite(senhas, sizeof(char[20]), totalUsers, file);
        fclose(file);
    } else {
        printf("Erro ao salvar usuários.\n");
    }
}

void registrar(int *totalUsers, char users[][100], char cpfs[][13], char senhas[][20]) {
    limpar_tela();
    if (*totalUsers >= 100) {
        printf("Limite de usuários atingido.\n");
        pausar();
        return;
    }

    char novo_usuario[100], novo_cpf[13], nova_senha[20];

    printf("Digite seu nome: ");
    fgets(novo_usuario, sizeof(novo_usuario), stdin);
    strtok(novo_usuario, "\n");

    if (strlen(novo_usuario) == 0) {
        printf("Nome não pode ser vazio.\n");
        pausar();
        return;
    }

    printf("Digite o CPF (apenas números): ");
    fgets(novo_cpf, sizeof(novo_cpf), stdin);
    strtok(novo_cpf, "\n");

    if (!validar_cpf(novo_cpf)) {
        printf("CPF inválido. Deve conter 11 dígitos.\n");
        pausar();
        return;
    }

    printf("Digite a senha: ");
    fgets(nova_senha, sizeof(nova_senha), stdin);
    strtok(nova_senha, "\n");

    if (strlen(nova_senha) < 6) {
        printf("A senha deve ter pelo menos 6 caracteres.\n");
        pausar();
        return;
    }

    strcpy(users[*totalUsers], novo_usuario);
    strcpy(cpfs[*totalUsers], novo_cpf);
    strcpy(senhas[*totalUsers], nova_senha);
    (*totalUsers)++;
    salvar_usuarios(*totalUsers, users, cpfs, senhas);

    // Criar arquivo de saldo inicial para o novo usuário
    salvar_saldo(0.0, 0.0, 0.0, 0.0, *totalUsers - 1);

    printf("\nUsuário registrado com sucesso!\n");
void saldo(float consaldo, float bitcoin, float ethereum, float ripple) {
    limpar_tela();
    printf("Saldo disponível: R$ %.2f\n", consaldo);
    printf("Bitcoin: %.6f BTC\n", bitcoin);
    printf("Ethereum: %.6f ETH\n", ethereum);
    printf("Ripple: %.6f XRP\n", ripple);
void atualizar_cotacao() {
    printf("As cotações das criptomoedas foram atualizadas.\n");
    pausar();
    limpar_tela();
}


int login(int totalUsers, char users[][100], char cpfs[][13], char senhas[][20]) {
    limpar_tela();
    char cpf[13], senha[20];

    printf("Digite seu CPF: ");
    fgets(cpf, sizeof(cpf), stdin);
    strtok(cpf, "\n");

    if (!validar_cpf(cpf)) {
        printf("CPF inválido. Deve conter 11 dígitos.\n");
        pausar();
        return -1;
    }

    printf("Digite sua senha: ");
    fgets(senha, sizeof(senha), stdin);
    strtok(senha, "\n");

    for (int i = 0; i < totalUsers; i++) {
        if (strcmp(cpfs[i], cpf) == 0 && strcmp(senhas[i], senha) == 0) {
            printf("\nBem-vindo(a), %s!\n", users[i]);
            pausar();
            limpar_tela();
            return i; // Retorna o índice do usuário logado
        }
    }

    printf("\nCPF ou senha incorretos!\n");
    pausar();
    limpar_tela();
    return -1;
}
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


void carregarsaldo(float consaldo, floatbitcoin, float ethereum, floatripple, int usuarioIndex) {
    char filename[50];
    snprintf(filename, sizeof(filename), "saldo%d.bin", usuarioIndex);
    FILE file = fopen(filename, "rb");
    if (file) {
        fread(consaldo, sizeof(float), 1, file);
        fread(bitcoin, sizeof(float), 1, file);
        fread(ethereum, sizeof(float), 1, file);
        fread(ripple, sizeof(float), 1, file);
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo de saldo.\n");
    }
}

void salvarsaldo(float consaldo, float bitcoin, float ethereum, float ripple, int usuarioIndex) {
    char filename[50];
    snprintf(filename, sizeof(filename), "saldo%d.bin", usuarioIndex);
    FILEfile = fopen(filename, "wb");
    if (file) {
        fwrite(&consaldo, sizeof(float), 1, file);
        fwrite(&bitcoin, sizeof(float), 1, file);
        fwrite(&ethereum, sizeof(float), 1, file);
        fwrite(&ripple, sizeof(float), 1, file);
        fclose(file);
    } else {
        printf("Erro ao salvar saldo.\n");
    }
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