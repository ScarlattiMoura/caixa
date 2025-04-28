#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../items/items.h"
#include "../employee/employee.h"
#include "../payment/payment.h"

#define SALES_FILE_PATH "registration/sales.txt"

static CartItem cart[100];
static int cart_size = 0;

// Função para escolher funcionário
Employee choose_employee() {
    load_employees_from_file();
    printf("Funcionários disponíveis:\n");

    for (int i = 0; i < get_employee_count(); i++) {
        Employee *e = get_employee_by_index(i);
        printf("ID: %d | Nome: %s\n", e->id, e->name);
    }

    int id;
    printf("Digite o ID do funcionário que está atendendo: ");
    scanf("%d", &id);

    Employee *e = get_employee_by_id(id);
    if (e == NULL) {
        printf("Funcionário não encontrado! Cancelando venda.\n");
        sleep(2);
        exit(1);
    }
    return *e;
}

// Função para escolher itens
void choose_items() {
    load_items_from_file();
    printf("Itens disponíveis:\n");

    for (int i = 0; i < get_item_count(); i++) {
        Item *it = get_item_by_index(i);
        printf("ID: %d | Nome: %s | Preço: %.2f | Estoque: %d\n",
               it->id, it->name, it->price, it->qnty);
    }

    while (1) {
        int id, quantity;
        printf("Digite o ID do item a adicionar (ou -1 para finalizar): ");
        scanf("%d", &id);

        if (id == -1) break;

        Item *it = get_item_by_id(id);
        if (it == NULL) {
            printf("Item não encontrado.\n");
            continue;
        }

        printf("Digite a quantidade: ");
        scanf("%d", &quantity);

        if (quantity <= 0 || quantity > it->qnty) {
            printf("Quantidade inválida.\n");
            continue;
        }

        cart[cart_size].item = *it;
        cart[cart_size].quantity = quantity;
        cart_size++;
    }
}

// Função para escolher forma de pagamento
const char* choose_payment_method() {
    int opcao;
    printf("Formas de pagamento:\n");
    printf("1 - Dinheiro\n");
    printf("2 - Cartão\n");
    printf("3 - Pix\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: return "Dinheiro";
        case 2: return "Cartão";
        case 3: return "Pix";
        default: return "Desconhecido";
    }
}

// Função para gerar nota fiscal
void generate_receipt(Employee atendente, const char* payment_method, float total) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    char time_buffer[64];
    strftime(time_buffer, sizeof(time_buffer), "%d/%m/%Y %H:%M:%S", tm_info);

    printf("\033[H\033[J");
    printf("========== NOTA FISCAL ==========\n");
    printf("Data: %s\n", time_buffer);
    printf("Atendente: %s\n\n", atendente.name);

    for (int i = 0; i < cart_size; i++) {
        printf("%s x%d - R$ %.2f\n", cart[i].item.name, cart[i].quantity, cart[i].item.price * cart[i].quantity);
    }

    printf("\nForma de pagamento: %s\n", payment_method);
    printf("TOTAL: R$ %.2f\n", total);
    printf("=================================\n");

    FILE *f = fopen(SALES_FILE_PATH, "a");
    if (f) {
        fprintf(f, "Data: %s\n", time_buffer);
        fprintf(f, "Atendente: %s\n", atendente.name);
        for (int i = 0; i < cart_size; i++) {
            fprintf(f, "%s x%d - R$ %.2f\n", cart[i].item.name, cart[i].quantity, cart[i].item.price * cart[i].quantity);
        }
        fprintf(f, "Forma de pagamento: %s\n", payment_method);
        fprintf(f, "TOTAL: R$ %.2f\n", total);
        fprintf(f, "---------------------------------\n");
        fclose(f);
    }
}

// Função principal
void make_payment() {
    cart_size = 0;
    Employee atendente = choose_employee();
    choose_items();
    const char *payment_method = choose_payment_method();

    float total = 0.0;
    for (int i = 0; i < cart_size; i++) {
        total += cart[i].item.price * cart[i].quantity;
    }

    generate_receipt(atendente, payment_method, total);

    printf("\nVenda concluída!\n");
    sleep(3);
}
