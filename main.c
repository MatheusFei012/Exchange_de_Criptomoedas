#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
int main() {
    int totalUsers = 0;
    char users[100][100], cpfs[100][13], senhas[100][20];

    carregar_usuarios(&totalUsers, users, cpfs, senhas);
    menu_principal(&totalUsers, users, cpfs, senhas);

    return 0;
}