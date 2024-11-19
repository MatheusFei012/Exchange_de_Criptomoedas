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
