#include<stdio.h>
#include<string.h>

void novacompra(){};
void funcionarios(){};

//
void itensatuais(){}
void novoitem(){}
void removeritem(){}
//

void itens(){
    int itensopcao;

    do
    {
        printf("\n==== ITENS ====\n");
        printf("\n1.Itens atuais\n");
        printf("2.Adicionar novo item\n");
        printf("3.Remover item\n");
        printf("0.Voltar ao menu inicial\n");
        printf("\n Digite a opcao desejada: ");
        scanf("%d", &itensopcao);

            switch (itensopcao){
            case 1:
            itensatuais();
            break;
        case 2:
            novoitem();
            break;
        case 3:
            removeritem();
            break;
        case 0:
                itensopcao = 0;
        break;
        default:
            printf("\n OPCAO INVALIDA!!!\n");
            break;
        }
    } while (itensopcao!= 0);

};

int main(){
    int opcao;
    do
    {
        printf("\n======  caixa de supermercado  ======\n");

    printf("\nOpcoes disponiveis :\n");
    printf("\n1.Nova compra\n");
    printf("2.Funcionarios\n");
    printf("3.Itens\n");
    printf("0.sair\n");
    printf("\n Digite a opcao desejada: ");
    scanf("%d", &opcao);


    switch (opcao)
    {
    case 1:
        novacompra();
        break;
    case 2:
        funcionarios();
        break;
    case 3:
        itens();
        break;
    case 0:
        opcao = 0;
        break;
    default:
        printf("\n OPCAO INVALIDA!!!\n");
        break;
    }
    } while (opcao != 0);
    return 0;
}