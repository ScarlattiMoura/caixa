#pragma once 
#include <../main/utils.h>

typedef struct {
    char chave[100];
    int opcao;
    char numcartao[17];
    char nome[50];
    char validade[6];
    char cvv[4];
    float recebido;
    int opcao;
    float total;
} payment, *payment;

void mostra_caixa(float valor);
void limpa_buffer();
void pagarcomcartao(char *tipo);
void pagarcompix();
void pagarcomdinheiro(float total);
void mostra_caixa(total);