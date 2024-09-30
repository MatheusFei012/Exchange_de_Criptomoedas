#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    pausar();
    limpar_tela();
}


int main() {
    int totalUsers = 0;
    char users[100][100], cpfs[100][13], senhas[100][20];

    carregar_usuarios(&totalUsers, users, cpfs, senhas);
    menu_principal(&totalUsers, users, cpfs, senhas);

    return 0;
}