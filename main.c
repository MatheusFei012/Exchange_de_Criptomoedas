#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    int totalUsers = 0;
    char users[100][100], cpfs[100][13], senhas[100][20];

    carregar_usuarios(&totalUsers, users, cpfs, senhas);
    menu_principal(&totalUsers, users, cpfs, senhas);

    return 0;
}
void sacar(float consaldo) {
    limpar_tela();
    float valor;
    printf("Digite o valor que deseja sacar: R$ ");
    scanf("%f", &valor);
    getchar(); // Limpa o buffer
    if (valor <= 0 || valor >consaldo) {
        printf("Valor inválido. O saque deve ser maior que zero e menor ou igual ao saldo.\n");
        pausar();
        return;
    }
    *consaldo -= valor;
    printf("Saque de R$ %.2f realizado com sucesso!\n", valor);
    pausar();
    limpar_tela();
}