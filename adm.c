#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ADMIN_CPF "12345678901"  // CPF do administrador
#define ADMIN_SENHA "admin123"   // Senha do administrador

// Estrutura para criptomoeda
typedef struct {
    char nome[100];
    float cotacao_inicial;
    float taxa_compra;
    float taxa_venda;
} Criptomoeda;

// Função para limpar a tela
void limpar_tela() {
    system("cls || clear");
}

// Função para pausar a execução e aguardar o usuário pressionar Enter
void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar();  // Espera o usuário pressionar Enter
}

// Função de login do administrador
int login_administrador() {
    char cpf[13], senha[20];

    limpar_tela();
    printf("Digite o CPF do administrador: ");
    fgets(cpf, sizeof(cpf), stdin);
    strtok(cpf, "\n");

    if (strcmp(cpf, ADMIN_CPF) != 0) {
        printf("CPF incorreto.\n");
        pausar();
        return 0;
    }

    printf("Digite a senha do administrador: ");
    fgets(senha, sizeof(senha), stdin);
    strtok(senha, "\n");

    if (strcmp(senha, ADMIN_SENHA) != 0) {
        printf("Senha incorreta.\n");
        pausar();
        return 0;
    }

    printf("Login realizado com sucesso!\n");
    pausar();
    return 1;  // Login bem-sucedido
}

// Função para cadastrar um novo investidor
typedef struct {
    char nome[100];
    char cpf[13];
    char senha[20];
} Investidor;

// Função para cadastrar um investidor
void cadastrar_investidor() {
    Investidor novo_investidor;

    printf("Digite o nome do investidor: ");
    fgets(novo_investidor.nome, sizeof(novo_investidor.nome), stdin);
    strtok(novo_investidor.nome, "\n");  // Remover o caractere de nova linha

    printf("Digite o CPF do investidor: ");
    fgets(novo_investidor.cpf, sizeof(novo_investidor.cpf), stdin);
    strtok(novo_investidor.cpf, "\n");

    printf("Digite a senha do investidor: ");
    fgets(novo_investidor.senha, sizeof(novo_investidor.senha), stdin);
    strtok(novo_investidor.senha, "\n");

    // Abre o arquivo de usuários para adicionar o novo investidor
    FILE *file = fopen("usuarios.bin", "ab"); // Abertura para adicionar no final
    if (!file) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    fwrite(&novo_investidor, sizeof(Investidor), 1, file);
    fclose(file);

    // Criar arquivo de saldo com valor inicial de 0.0
    char saldo_file[50];
    sprintf(saldo_file, "saldo_%s.bin", novo_investidor.cpf);
    FILE *saldo = fopen(saldo_file, "wb");
    if (saldo) {
        float saldo_inicial = 0.0;
        fwrite(&saldo_inicial, sizeof(float), 1, saldo);
        fclose(saldo);
        printf("Arquivo de saldo criado com sucesso.\n");
    } else {
        printf("Erro ao criar o arquivo de saldo.\n");
    }

    // Criar arquivo de extrato vazio ou com texto inicial
    char extrato_file[50];
    sprintf(extrato_file, "extrato_%s.bin", novo_investidor.cpf);
    FILE *extrato = fopen(extrato_file, "wb");
    if (extrato) {
        char texto_inicial[500] = "Nenhuma transação realizada até o momento.\n";
        fwrite(texto_inicial, sizeof(char), strlen(texto_inicial) + 1, extrato);
        fclose(extrato);
        printf("Arquivo de extrato criado com sucesso.\n");
    } else {
        printf("Erro ao criar o arquivo de extrato.\n");
    }

    printf("Investidor cadastrado com sucesso!\n");
    pausar();
}
void excluir_investidor() {
    FILE *file = fopen("usuarios.bin", "rb+");
    if (!file) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    Investidor investidor;
    char cpf[13];
    int found = 0;
    long position;

    printf("Digite o CPF do investidor a ser excluído: ");
    fgets(cpf, sizeof(cpf), stdin);
    strtok(cpf, "\n");

    // Procurar o investidor no arquivo
    while ((position = ftell(file)) != -1 && fread(&investidor, sizeof(Investidor), 1, file)) {
        if (strcmp(investidor.cpf, cpf) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Investidor não encontrado.\n");
        fclose(file);
        return;
    }

    // Confirmar a exclusão
    char confirmacao;
    printf("Tem certeza de que deseja excluir o investidor %s (CPF: %s)? [S/N]: ", investidor.nome, investidor.cpf);
    scanf(" %c", &confirmacao);
    getchar();  // Limpar o buffer

    if (confirmacao != 'S' && confirmacao != 's') {
        printf("Exclusão cancelada.\n");
        fclose(file);
        return;
    }

    // Criar arquivo temporário para regravar os dados sem o investidor excluído
    FILE *tempFile = fopen("temp.bin", "wb");
    if (!tempFile) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(file);
        return;
    }

    fseek(file, 0, SEEK_SET);  // Voltar para o início do arquivo
    while (fread(&investidor, sizeof(Investidor), 1, file)) {
        if (strcmp(investidor.cpf, cpf) != 0) {
            fwrite(&investidor, sizeof(Investidor), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Excluir o arquivo original e renomear o arquivo temporário
    remove("usuarios.bin");
    rename("temp.bin", "usuarios.bin");

    // Agora, vamos excluir os arquivos de saldo e extrato do investidor
    char saldo_file[50], extrato_file[50];
    sprintf(saldo_file, "saldo_%s.bin", cpf);
    sprintf(extrato_file, "extrato_%s.bin", cpf);

    // Excluir o arquivo de saldo, se existir
    if (remove(saldo_file) == 0) {
        printf("Arquivo de saldo excluído.\n");
    } else {
        printf("Erro ao excluir o arquivo de saldo ou ele não existe.\n");
    }

    // Excluir o arquivo de extrato, se existir
    if (remove(extrato_file) == 0) {
        printf("Arquivo de extrato excluído.\n");
    } else {
        printf("Erro ao excluir o arquivo de extrato ou ele não existe.\n");
    }

    printf("Investidor e seus dados (saldo e extrato) excluídos com sucesso!\n");
    pausar();
}
void carregar_extrato(int usuarioIndex) {
    char filename[50];
    snprintf(filename, sizeof(filename), "extrato_%d.bin", usuarioIndex);

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

    pausar();  // Pausa para o usuário visualizar antes de sair
}
void consultar_saldo_investidor() {
    char cpf[13];
    int found = 0;
    Investidor investidor;

    printf("Digite o CPF do investidor: ");
    fgets(cpf, sizeof(cpf), stdin);
    strtok(cpf, "\n");

    FILE *file = fopen("usuarios.bin", "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    while (fread(&investidor, sizeof(Investidor), 1, file)) {
        if (strcmp(investidor.cpf, cpf) == 0) {
            found = 1;
            // Se encontrado, consultar o saldo
            char saldo_file[50];
            sprintf(saldo_file, "saldo_%s.bin", investidor.cpf);

            FILE *saldoFile = fopen(saldo_file, "rb");
            if (saldoFile) {
                float saldo;
                fread(&saldo, sizeof(float), 1, saldoFile);
                printf("Saldo do investidor %s (CPF: %s): %.2f\n", investidor.nome, investidor.cpf, saldo);
                fclose(saldoFile);  // Fechar o arquivo de saldo
            } else {
                printf("Erro ao ler o arquivo de saldo.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Investidor não encontrado.\n");
    }

    fclose(file);  // Fechar o arquivo de usuários
    pausar();
}
void consultar_extrato_investidor() {
    char cpf[13];
    int found = 0;
    Investidor investidor;

    printf("Digite o CPF do investidor: ");
    fgets(cpf, sizeof(cpf), stdin);
    strtok(cpf, "\n");

    FILE *file = fopen("usuarios.bin", "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    while (fread(&investidor, sizeof(Investidor), 1, file)) {
        if (strcmp(investidor.cpf, cpf) == 0) {
            found = 1;
            // Se encontrado, consultar o extrato
            char extrato_file[50];
            sprintf(extrato_file, "extrato_%s.bin", investidor.cpf);

            FILE *extratoFile = fopen(extrato_file, "rb");
            if (extratoFile) {
                char extrato[500];
                fread(extrato, sizeof(char), 500, extratoFile);
                printf("Extrato do investidor %s (CPF: %s):\n%s\n", investidor.nome, investidor.cpf, extrato);
                fclose(extratoFile);  // Fechar o arquivo de extrato
            } else {
                printf("Erro ao ler o arquivo de extrato.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Investidor não encontrado.\n");
    }

    fclose(file);  // Fechar o arquivo de usuários
    pausar();
}

void cadastrar_criptomoeda() {
  FILE *file = fopen("criptomoedas.bin", "ab");
  if (!file) {
    printf("Erro ao abrir o arquivo de criptomoedas.\n");
    return;
  }

  Criptomoeda moeda;
  printf("Digite o nome da criptomoeda: ");
  fgets(moeda.nome, sizeof(moeda.nome), stdin);
  strtok(moeda.nome, "\n");

  printf("Digite a cotação inicial da criptomoeda: ");
  scanf("%f", &moeda.cotacao_inicial);

  printf("Digite a taxa de compra da criptomoeda: ");
  scanf("%f", &moeda.taxa_compra);

  printf("Digite a taxa de venda da criptomoeda: ");
  scanf("%f", &moeda.taxa_venda);
  getchar(); // Limpar o buffer

  fwrite(&moeda, sizeof(Criptomoeda), 1, file);
  printf("Criptomoeda cadastrada com sucesso!\n");

  pausar();
  fclose(file);
}


void excluir_criptomoeda() {
  FILE *file = fopen("criptomoedas.bin", "rb+");
  if (!file) {
    printf("Erro ao abrir o arquivo de criptomoedas.\n");
    return;
  }

  Criptomoeda moeda;
  char nome[100];
  int found = 0;

  printf("Digite o nome da criptomoeda a ser excluída: ");
  fgets(nome, sizeof(nome), stdin);
  strtok(nome, "\n");

  while (fread(&moeda, sizeof(Criptomoeda), 1, file)) {
    if (strcmp(moeda.nome, nome) == 0) {
      printf("Criptomoeda encontrada: %s\n", moeda.nome);
      printf("Cotação inicial: %.2f\n", moeda.cotacao_inicial);
      printf("Taxa de compra: %.2f\n", moeda.taxa_compra);
      printf("Taxa de venda: %.2f\n", moeda.taxa_venda);

      
      char confirmacao;
      printf("Tem certeza que deseja excluir essa criptomoeda? [S/N]: ");
      scanf(" %c", &confirmacao);
      getchar(); 

      if (confirmacao == 'S' || confirmacao == 's') {
        
        FILE *temp = fopen("temp.bin", "wb");
        if (!temp) {
          printf("Erro ao criar arquivo temporário.\n");
          fclose(file);
          return;
        }

        rewind(file);
        while (fread(&moeda, sizeof(Criptomoeda), 1, file)) {
          if (strcmp(moeda.nome, nome) != 0) {
            fwrite(&moeda, sizeof(Criptomoeda), 1, temp);
          }
        }

        fclose(file);
        fclose(temp);

        remove("criptomoedas.bin");
        rename("temp.bin", "criptomoedas.bin");

        printf("Criptomoeda excluída com sucesso!\n");
      } else {
        printf("Exclusão cancelada.\n");
      }

      found = 1;
      break;
    }
  }

  if (!found) {
    printf("Criptomoeda não encontrada.\n");
  }

  pausar();
  fclose(file);
}

void atualizar_cotacao_criptomoeda() {
  FILE *file = fopen("criptomoedas.bin", "rb+");
  if (!file) {
    printf("Erro ao abrir o arquivo de criptomoedas.\n");
    return;
  }

  Criptomoeda moeda;
  char nome[100];
  int found = 0;

  printf("Digite o nome da criptomoeda a ser atualizada: ");
  fgets(nome, sizeof(nome), stdin);
  strtok(nome, "\n");

  while (fread(&moeda, sizeof(Criptomoeda), 1, file)) {
    if (strcmp(moeda.nome, nome) == 0) {
      printf("Criptomoeda encontrada: %s\n", moeda.nome);
      printf("Cotação inicial: %.2f\n", moeda.cotacao_inicial);
      printf("Taxa de compra: %.2f\n", moeda.taxa_compra);
      printf("Taxa de venda: %.2f\n", moeda.taxa_venda);

      printf("Digite a nova cotação inicial: ");
      scanf("%f", &moeda.cotacao_inicial);

      printf("Digite a nova taxa de compra: ");
      scanf("%f", &moeda.taxa_compra);

      printf("Digite a nova taxa de venda: ");
      scanf("%f", &moeda.taxa_venda);

      fseek(file, -sizeof(Criptomoeda),
            SEEK_CUR); 
      fwrite(&moeda, sizeof(Criptomoeda), 1, file);
      printf("Criptomoeda atualizada com sucesso!\n");

      found = 1;
      break;
    }
  }

  if (!found) {
    printf("Criptomoeda não encontrada.\n");
  }

  pausar();
  fclose(file);
}
