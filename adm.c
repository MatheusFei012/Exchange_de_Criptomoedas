#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ADMIN_CPF "12345678901"  // CPF do administrador
#define ADMIN_SENHA "admin123"   // Senha do administrador

// Estrutura para criptomoeda
typedef struct {
    char nome[100];
    float cotacao_inicial;
    float taxa_compra;
    float taxa_venda;
} Criptomoeda;

// Função para limpar a tela
void limpar_tela() {
    system("cls || clear");
}

// Função para pausar a execução e aguardar o usuário pressionar Enter
void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar();  // Espera o usuário pressionar Enter
}

// Função de login do administrador
int login_administrador() {
    char cpf[13], senha[20];

    limpar_tela();
    printf("Digite o CPF do administrador: ");
    fgets(cpf, sizeof(cpf), stdin);
    strtok(cpf, "\n");

    if (strcmp(cpf, ADMIN_CPF) != 0) {
        printf("CPF incorreto.\n");
        pausar();
        return 0;
    }

    printf("Digite a senha do administrador: ");
    fgets(senha, sizeof(senha), stdin);
    strtok(senha, "\n");

    if (strcmp(senha, ADMIN_SENHA) != 0) {
        printf("Senha incorreta.\n");
        pausar();
        return 0;
    }

    printf("Login realizado com sucesso!\n");
    pausar();
    return 1;  // Login bem-sucedido
}

// Função para cadastrar um novo investidor
typedef struct {
    char nome[100];
    char cpf[13];
    char senha[20];
} Investidor;

