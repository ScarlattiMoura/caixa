#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <payment.h>



// caixa
void mostra_caixa(float valor) {
    
    printf("\n");
    printf("  ╔══════════════════╗\n");
    printf("  ║  ┌────────────┐  ║\n");
    printf("  ║  │ R$ %7.2f │  ║\n", valor);
    printf("  ║  └────────────┘  ║\n");
    printf("  ║  ┌──────┬──────┐ ║\n");
    printf("  ║  │ PIX  │ CART │ ║\n");
    printf("  ║  └──────┴──────┘ ║\n");
    printf("  ╚══════════════════╝\n");
}

void limpa_buffer() {
    while(getchar() != '\n');
}

void pagarcomcartao(char *tipo) {
    char numcartao[17], nome[50], validade[6], cvv[4];

    printf("\nPagando com %s\n", tipo);
    printf("Número do cartão: ");
    scanf("%16s", numcartao);
    limpa_buffer();

    printf("Nome no cartão: ");
    fgets(nome, 50, stdin);
    nome[strlen(nome)-1] = '\0';

    printf("Validade (MM/AA): ");
    scanf("%5s", validade);
    limpa_buffer();

    printf("CVV: ");
    scanf("%3s", cvv);
    limpa_buffer();

    printf("\nProcessando %s... cartão %s\n", tipo, numcartao);
    printf(">>> %s aprovado!\n", tipo);
}

void pagarcompix() {
    char chave[100];
    int opcao;

    printf("\nPIX !\n");
    printf("1 - CPF\n2 - Email\n3 - Celular\n4 - Chave aleatória\n>>> Qual chave vai usar?:  ");
    scanf("%d", &opcao);
    limpa_buffer();

    switch(opcao) {
        case 1: 
          printf("CPF: "); 
          break;
        case 2: 
          printf("Email: "); 
          break;
        case 3: 
          printf("Celular: "); 
          break;
        case 4: 
          printf("Chave aleatória: "); 
          break;
        default: 
          printf(">>> Opção inválida!\n"); 
          return;
    }
    scanf("%99s", chave);
    limpa_buffer();

    printf("\nGerando QR Code pra %s...\n", chave);
    printf(">>> Transferência concluída!\n");
}

void pagarcomdinheiro(float total) {
    float recebido;

    printf("\nPagando em espécie\n");
    printf(">>> Total: R$ %.2f\n", total);

    do {
        printf(">>>Valor recebido: R$ ");
        scanf("%f", &recebido);
        limpa_buffer();
        if (recebido < total) printf(">>> Valor não está pago totalmente! Falta R$ %.2f\n", total - recebido);
    } while(recebido < total);

    if (recebido > total) printf(">>> Seu troco: R$ %.2f\n", recebido - total);
    printf(">>> Transferência concluída!\n");
}

int main() {
    int opcao;
    float total;
  
    printf("==== Sistema de pagamento ===\n");
    printf(">>> Valor a ser pago: R$ ");
    scanf("%f", &total);
    limpa_buffer();

    mostra_caixa(total);

    do {
        printf("\n[1] Débito\n[2] Crédito\n[3] PIX\n[4] Dinheiro\n[5] Sair\n>>> Escolha: ");
        scanf("%d", &opcao);
        limpa_buffer();

        switch(opcao) {
            case 1: 
              pagarcomcartao("DÉBITO");
              break;
            case 2: 
              pagarcomcartao("CRÉDITO"); 
              break;
            case 3: 
              pagarcompix(); 
              break;
            case 4: 
              pagarcomdinheiro(total); 
              break;
            case 5: 
              printf(">>> Fechou então!\n"); 
              break;
            default: 
              printf(">>> Opção errada!\n");
        }
    } while(opcao != 5);

    mostra_caixa(0.00); 
    return 0;
}