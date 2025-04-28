#pragma once

// Estrutura de item no carrinho
typedef struct {
    Item item;
    int quantity;
} CartItem;

// Funções principais
Employee choose_employee();
void choose_items();
const char* choose_payment_method();
void generate_receipt(Employee atendente, const char* payment_method, float total);
void make_payment();
