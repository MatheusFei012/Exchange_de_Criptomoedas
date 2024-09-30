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