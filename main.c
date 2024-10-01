#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void atualizar_cotacao() {
    printf("As cotações das criptomoedas foram atualizadas.\n");
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