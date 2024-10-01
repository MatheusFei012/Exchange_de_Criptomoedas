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

void gravarextrato(int usuarioIndex, const char tipo, const charmoeda, float valor, float saldo_apos) {
    char filename[50];
    snprintf(filename, sizeof(filename), "extrato%d.bin", usuarioIndex);

    FILE file = fopen(filename, "ab");
    if (file) {
        char data_hora[30];
        time_t t = time(NULL);
        struct tmtm_info = localtime(&t);
        strftime(data_hora, sizeof(data_hora), "%Y-%m-%d %H:%M:%S", tm_info);

        fwrite(data_hora, sizeof(char[30]), 1, file);
        fwrite(tipo, sizeof(char[50]), 1, file);
        fwrite(moeda, sizeof(char[20]), 1, file);
        fwrite(&valor, sizeof(float), 1, file);
        fwrite(&saldo_apos, sizeof(float), 1, file);

        fclose(file);
    } else {
        printf("Erro ao gravar extrato.\n");
    }
}