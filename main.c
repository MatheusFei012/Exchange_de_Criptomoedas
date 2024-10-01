#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void carregarsaldo(float consaldo, floatbitcoin, float ethereum, floatripple, int usuarioIndex) {
    char filename[50];
    snprintf(filename, sizeof(filename), "saldo%d.bin", usuarioIndex);
    FILE file = fopen(filename, "rb");
    if (file) {
        fread(consaldo, sizeof(float), 1, file);
        fread(bitcoin, sizeof(float), 1, file);
        fread(ethereum, sizeof(float), 1, file);
        fread(ripple, sizeof(float), 1, file);
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo de saldo.\n");
    }
}

void salvarsaldo(float consaldo, float bitcoin, float ethereum, float ripple, int usuarioIndex) {
    char filename[50];
    snprintf(filename, sizeof(filename), "saldo%d.bin", usuarioIndex);
    FILEfile = fopen(filename, "wb");
    if (file) {
        fwrite(&consaldo, sizeof(float), 1, file);
        fwrite(&bitcoin, sizeof(float), 1, file);
        fwrite(&ethereum, sizeof(float), 1, file);
        fwrite(&ripple, sizeof(float), 1, file);
        fclose(file);
    } else {
        printf("Erro ao salvar saldo.\n");
    }
}

int main() {
    int totalUsers = 0;
    char users[100][100], cpfs[100][13], senhas[100][20];

    carregar_usuarios(&totalUsers, users, cpfs, senhas);
    menu_principal(&totalUsers, users, cpfs, senhas);

    return 0;
}