#include <establishment.h>
#include <stdio.h>
#include <string.h>

#define ESTABLISHMENT_FILE_PATH "registration/establishment.txt"

static Establishment est;

void save_establishment_to_file() {
    FILE *file = fopen(ESTABLISHMENT_FILE_PATH, "w");
    if (!file) {
        perror("Erro ao salvar o estabelecimento");
        return;
    }
    fprintf(file, "%s\n%s\n%d\n%s\n", est.name, est.address, est.number, est.cnpj);
    fclose(file);
}

void load_establishment_from_file() {
    FILE *file = fopen(ESTABLISHMENT_FILE_PATH, "r");
    if (!file) return;

    fgets(est.name, sizeof(est.name), file);
    est.name[strcspn(est.name, "\n")] = 0;

    fgets(est.address, sizeof(est.address), file);
    est.address[strcspn(est.address, "\n")] = 0;

    fscanf(file, "%d\n", &est.number);

    fgets(est.cnpj, sizeof(est.cnpj), file);
    est.cnpj[strcspn(est.cnpj, "\n")] = 0;

    fclose(file);
}

void register_establishment() {
    printf("\033[H\033[J");
    
    printf("Digite o nome do estabelecimento: ");
    scanf(" %[^\n]", est.name);

    printf("Digite o endereço do estabelecimento: ");
    scanf(" %[^\n]", est.address);

    printf("Digite o número: ");
    scanf("%d", &est.number);

    printf("Digite o CNPJ: ");
    scanf(" %[^\n]", est.cnpj);

    save_establishment_to_file();
    printf("Estabelecimento cadastrado com sucesso!\n");
    sleep(2);
}

void modify_establishment() {
    printf("\033[H\033[J");

    load_establishment_from_file();

    printf("Alteração de Estabelecimento:\n");
    printf("Nome atual: %s\n", est.name);
    printf("Endereço atual: %s\n", est.address);
    printf("Número atual: %d\n", est.number);
    printf("CNPJ atual: %s\n\n", est.cnpj);

    printf("Digite o novo nome (ou ENTER para manter): ");
    char temp[100];
    getchar(); // limpar buffer
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n') {
        temp[strcspn(temp, "\n")] = 0;
        strncpy(est.name, temp, sizeof(est.name));
    }

    printf("Digite o novo endereço (ou ENTER para manter): ");
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n') {
        temp[strcspn(temp, "\n")] = 0;
        strncpy(est.address, temp, sizeof(est.address));
    }

    printf("Digite o novo número (ou 0 para manter): ");
    int num;
    scanf("%d", &num);
    if (num != 0) {
        est.number = num;
    }

    printf("Digite o novo CNPJ (ou ENTER para manter): ");
    getchar(); // limpar
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n') {
        temp[strcspn(temp, "\n")] = 0;
        strncpy(est.cnpj, temp, sizeof(est.cnpj));
    }

    save_establishment_to_file();
    printf("Estabelecimento modificado com sucesso!\n");
    sleep(2);
}

void show_establishment() {
    printf("\033[H\033[J");

    load_establishment_from_file();

    printf("Dados do Estabelecimento:\n");
    printf("Nome: %s\n", est.name);
    printf("Endereço: %s\n", est.address);
    printf("Número: %d\n", est.number);
    printf("CNPJ: %s\n", est.cnpj);
    
    sleep(5);
}
