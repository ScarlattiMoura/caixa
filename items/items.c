#include <items.h>
#include <string.h>
#include <stdlib.h>

#define ITEMS_FILE_PATH "registration/items.txt"

static Item obj[100];
static int next_item = 0;

// Função para carregar itens do arquivo para a memória
void load_items_from_file() {
    FILE *file = fopen(ITEMS_FILE_PATH, "r");
    if (!file) return;

    next_item = 0;
    while (fscanf(file, "%d %49s %d %f", &obj[next_item].id, obj[next_item].name, &obj[next_item].qnty, &obj[next_item].price) == 4) {
        next_item++;
    }
    fclose(file);
}

// Função para salvar todos os itens da memória para o arquivo
void save_items_to_file() {
    FILE *file = fopen(ITEMS_FILE_PATH, "w");
    if (!file) {
        perror("Erro ao abrir items.txt para escrita");
        return;
    }

    for (int i = 0; i < next_item; i++) {
        fprintf(file, "%d %s %d %.2f\n", obj[i].id, obj[i].name, obj[i].qnty, obj[i].price);
    }
    fclose(file);
}

void register_item() {
    printf("\033[H\033[J");
    load_items_from_file(); // Carrega os itens atuais

    printf("Digite o nome do item: ");
    scanf("%s", obj[next_item].name);
    printf("Digite a quantidade em estoque: ");
    scanf("%d", &obj[next_item].qnty);
    printf("Digite o preco do item: ");
    scanf("%f", &obj[next_item].price);
    obj[next_item].id = next_item;

    next_item++;

    save_items_to_file(); // Salva todos os itens de volta (atualizado)

    printf("Produto cadastrado com sucesso! ID: %d\n", obj[next_item - 1].id);
    sleep(2);
}

void search_item() {
    printf("\033[H\033[J");
    load_items_from_file();

    char input[50];
    printf("Digite o nome do item ou ID: ");
    scanf("%s", input);

    int found = 0;
    for (int i = 0; i < next_item; i++) {
        if (strcmp(obj[i].name, input) == 0 || atoi(input) == obj[i].id) {
            printf("Item encontrado:\n");
            printf("ID: %d | Nome: %s | Quantidade: %d | Preço: %.2f\n",
                   obj[i].id, obj[i].name, obj[i].qnty, obj[i].price);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Item não encontrado.\n");
    }
    sleep(2);
}

void delete_item() {
    printf("\033[H\033[J");
    load_items_from_file();

    int id;
    printf("Digite o ID do item para deletar: ");
    scanf("%d", &id);

    if (id >= 0 && id < next_item) {
        for (int i = id; i < next_item - 1; i++) {
            obj[i] = obj[i + 1];
            obj[i].id = i;
        }
        next_item--;
        save_items_to_file();
        printf("Item deletado com sucesso.\n");
    } else {
        printf("ID inválido.\n");
    }
    sleep(2);
}

void show_items() {
    printf("\033[H\033[J");
    load_items_from_file();

    printf("Lista de Itens:\n");
    for (int i = 0; i < next_item; i++) {
        printf("ID: %d | Nome: %s | Quantidade: %d | Preço: %.2f\n",
               obj[i].id, obj[i].name, obj[i].qnty, obj[i].price);
    }
    sleep(4);
}

void modify_item() {
    printf("\033[H\033[J");
    load_items_from_file();

    char input[50];
    printf("Digite o nome ou ID do item a modificar: ");
    scanf("%s", input);

    ItemModder item = NULL;

    for (int i = 0; i < next_item; i++) {
        if (strcmp(obj[i].name, input) == 0 || atoi(input) == obj[i].id) {
            item = &obj[i];
            break;
        }
    }

    if (item != NULL) {
        printf("Item atual:\n");
        printf("ID: %d | Nome: %s | Quantidade: %d | Preço: %.2f\n",
               item->id, item->name, item->qnty, item->price);

        printf("\nDigite o novo nome do item: ");
        scanf("%s", item->name);
        printf("Digite a nova quantidade: ");
        scanf("%d", &item->qnty);
        printf("Digite o novo preço: ");
        scanf("%f", &item->price);

        save_items_to_file();
        printf("Item modificado com sucesso!\n");
        sleep(2);
    } else {
        printf("Item não encontrado.\n");
        sleep(2);
    }
}
