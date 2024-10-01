#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void saldo(float consaldo, float bitcoin, float ethereum, float ripple) {
    limpar_tela();
    printf("Saldo disponível: R$ %.2f\n", consaldo);
    printf("Bitcoin: %.6f BTC\n", bitcoin);
    printf("Ethereum: %.6f ETH\n", ethereum);
    printf("Ripple: %.6f XRP\n", ripple);
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