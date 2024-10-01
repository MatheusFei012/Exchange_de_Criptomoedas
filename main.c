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

void carregarextrato(int usuarioIndex) {
    char filename[50];
    snprintf(filename, sizeof(filename), "extrato%d.bin", usuarioIndex);

    FILE *file = fopen(filename, "rb");
    if (file) {
        char data_hora[30], tipo[50], moeda[20];
        float valor, saldo_apos;
        int found = 0;

        printf("\nExtrato de transações:\n");
        printf("------------------------------------------------------------\n");
        printf("%-20s | %-10s | %-10s | %-10s | %-10s\n", "Data/Hora", "Tipo", "Moeda", "Valor", "Saldo Após");
        printf("------------------------------------------------------------\n");

        while (fread(data_hora, sizeof(char[30]), 1, file) &&
               fread(tipo, sizeof(char[50]), 1, file) &&
               fread(moeda, sizeof(char[20]), 1, file) &&
               fread(&valor, sizeof(float), 1, file) &&
               fread(&saldo_apos, sizeof(float), 1, file)) {
            printf("%-20s | %-10s | %-10s | %-10.2f | %-10.2f\n", data_hora, tipo, moeda, valor, saldo_apos);
            found = 1;
        }

        if (!found) {
            printf("Nenhuma transação realizada até o momento.\n");
        }

        printf("------------------------------------------------------------\n");
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo de extrato.\n");
    }
}