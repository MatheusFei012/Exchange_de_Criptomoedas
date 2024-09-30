#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void salvar_usuarios(int totalUsers, char users[][100], char cpfs[][13], char senhas[][20]) {
    FILE *file = fopen("usuarios.bin", "wb");
    if (file) {
        fwrite(&totalUsers, sizeof(int), 1, file);
        fwrite(users, sizeof(char[100]), totalUsers, file);
        fwrite(cpfs, sizeof(char[13]), totalUsers, file);
        fwrite(senhas, sizeof(char[20]), totalUsers, file);
        fclose(file);
    } else {
        printf("Erro ao salvar usuários.\n");
    }
}

int main() {
    int totalUsers = 0;
    char users[100][100], cpfs[100][13], senhas[100][20];

    carregar_usuarios(&totalUsers, users, cpfs, senhas);
    menu_principal(&totalUsers, users, cpfs, senhas);

    return 0;
}