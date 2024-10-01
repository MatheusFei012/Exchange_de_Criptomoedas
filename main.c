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



int main() {
    int totalUsers = 0;
    char users[100][100], cpfs[100][13], senhas[100][20];

    carregar_usuarios(&totalUsers, users, cpfs, senhas);
    menu_principal(&totalUsers, users, cpfs, senhas);

    return 0;
}

void depositar(float *consaldo) {
    limpar_tela();
    float valor;
    printf("Digite o valor que deseja depositar: R$ ");
    scanf("%f", &valor);
    getchar(); // Limpa o buffer
    if (valor <= 0) {
        printf("Valor inválido. O depósito deve ser maior que zero.\n");
        pausar();
        return;
    }
    *consaldo += valor;
    printf("Depósito de R$ %.2f realizado com sucesso!\n", valor);
    pausar();
    limpar_tela();
}