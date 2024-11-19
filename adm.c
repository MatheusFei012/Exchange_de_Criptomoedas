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

// Função para cadastrar um investidor
void cadastrar_investidor() {
    Investidor novo_investidor;

    printf("Digite o nome do investidor: ");
    fgets(novo_investidor.nome, sizeof(novo_investidor.nome), stdin);
    strtok(novo_investidor.nome, "\n");  // Remover o caractere de nova linha

    printf("Digite o CPF do investidor: ");
    fgets(novo_investidor.cpf, sizeof(novo_investidor.cpf), stdin);
    strtok(novo_investidor.cpf, "\n");

    printf("Digite a senha do investidor: ");
    fgets(novo_investidor.senha, sizeof(novo_investidor.senha), stdin);
    strtok(novo_investidor.senha, "\n");

    // Abre o arquivo de usuários para adicionar o novo investidor
    FILE *file = fopen("usuarios.bin", "ab"); // Abertura para adicionar no final
    if (!file) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    fwrite(&novo_investidor, sizeof(Investidor), 1, file);
    fclose(file);

    // Criar arquivo de saldo com valor inicial de 0.0
    char saldo_file[50];
    sprintf(saldo_file, "saldo_%s.bin", novo_investidor.cpf);
    FILE *saldo = fopen(saldo_file, "wb");
    if (saldo) {
        float saldo_inicial = 0.0;
        fwrite(&saldo_inicial, sizeof(float), 1, saldo);
        fclose(saldo);
        printf("Arquivo de saldo criado com sucesso.\n");
    } else {
        printf("Erro ao criar o arquivo de saldo.\n");
    }

    // Criar arquivo de extrato vazio ou com texto inicial
    char extrato_file[50];
    sprintf(extrato_file, "extrato_%s.bin", novo_investidor.cpf);
    FILE *extrato = fopen(extrato_file, "wb");
    if (extrato) {
        char texto_inicial[500] = "Nenhuma transação realizada até o momento.\n";
        fwrite(texto_inicial, sizeof(char), strlen(texto_inicial) + 1, extrato);
        fclose(extrato);
        printf("Arquivo de extrato criado com sucesso.\n");
    } else {
        printf("Erro ao criar o arquivo de extrato.\n");
    }

    printf("Investidor cadastrado com sucesso!\n");
    pausar();
}

