#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void vender_criptomoeda(float consaldo, floatbitcoin, float ethereum, floatripple, int usuarioIndex) {
    limpar_tela();
    int opcao;
    float valor;
    printf("Escolha uma criptomoeda para vender:\n");
    printf("1. Bitcoin (BTC)\n");
    printf("2. Ethereum (ETH)\n");
    printf("3. Ripple (XRP)\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar(); // Limpa o buffer

    printf("Digite o valor que deseja vender: ");
    scanf("%f", &valor);
    getchar(); // Limpa o buffer

    switch (opcao) {
        case 1:
            if (valor > *bitcoin) {
                printf("Saldo insuficiente de Bitcoin para a venda.\n");
                pausar();
                return;
            }
            bitcoin -= valor; // Aqui deve ser feita a conversão para R$
            gravar_extrato(usuarioIndex, "Venda", "Bitcoin", valor,consaldo);
            break;
        case 2:
            if (valor > *ethereum) {
                printf("Saldo insuficiente de Ethereum para a venda.\n");
                pausar();
                return;
            }
            ethereum -= valor; // Aqui deve ser feita a conversão para R$
            gravar_extrato(usuarioIndex, "Venda", "Ethereum", valor,consaldo);
            break;
        case 3:
            if (valor > *ripple) {
                printf("Saldo insuficiente de Ripple para a venda.\n");
                pausar();
                return;
            }
            ripple -= valor; // Aqui deve ser feita a conversão para R$
            gravar_extrato(usuarioIndex, "Venda", "Ripple", valor,consaldo);
            break;
        default:
            printf("Opção inválida.\n");
            pausar();
            return;
    }

    *consaldo += valor; // Aqui deve ser feito o depósito do valor da venda em Reais
    printf("Venda realizada com sucesso!\n");
    pausar();
    limpar_tela();
}
void comprar_criptomoeda(float consaldo, floatbitcoin, float ethereum, floatripple, int usuarioIndex) {
    limpar_tela();
    int opcao;
    float valor;
    printf("Escolha uma criptomoeda para comprar:\n");
    printf("1. Bitcoin (BTC)\n");
    printf("2. Ethereum (ETH)\n");
    printf("3. Ripple (XRP)\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar(); // Limpa o buffer

    printf("Digite o valor que deseja investir: R$ ");
    scanf("%f", &valor);
    getchar(); // Limpa o buffer

    if (valor <= 0 || valor > *consaldo) {
        printf("Valor inválido. O investimento deve ser maior que zero e menor ou igual ao saldo.\n");
        pausar();
        return;
    }

    switch (opcao) {
        case 1:
            bitcoin += valor; // Aqui deve ser feita a conversão para BTC
            gravar_extrato(usuarioIndex, "Compra", "Bitcoin", valor,consaldo);
            break;
        case 2:
            ethereum += valor; // Aqui deve ser feita a conversão para ETH
            gravar_extrato(usuarioIndex, "Compra", "Ethereum", valor,consaldo);
            break;
        case 3:
            ripple += valor; // Aqui deve ser feita a conversão para XRP
            gravar_extrato(usuarioIndex, "Compra", "Ripple", valor,consaldo);
            break;
        default:
            printf("Opção inválida.\n");
            pausar();
            return;
    }

    *consaldo -= valor; // Deduzir o valor do saldo em Reais
    printf("Compra realizada com sucesso!\n");
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