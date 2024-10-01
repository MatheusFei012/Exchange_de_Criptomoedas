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
int main() {
    int totalUsers = 0;
    char users[100][100], cpfs[100][13], senhas[100][20];

    carregar_usuarios(&totalUsers, users, cpfs, senhas);
    menu_principal(&totalUsers, users, cpfs, senhas);

    return 0;
}