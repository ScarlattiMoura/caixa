#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <termio.h>
#include <time.h> 
#include <unistd.h>

//isso serve para o clique do teclado funcionar no linux
int getch(){
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDERR_FILENO, TCSANOW, &oldt);
    return ch;
}

// --- Estruturas e Variáveis Globais ---
#define MAX_FUNCIONARIOS 100
#define MAX_NOME 100
#define MAX_ITENS 20
#define ARQUIVO_DADOS "notas_fiscais.txt"
#define ARQUIVO_TEMP "temp.txt"

//ÁREA STRUCT
typedef struct {
    char nome[MAX_NOME];
} Funcionario;

typedef struct {
    char nome[MAX_NOME];
    int quantidade;
    float preco;
} Item;

typedef struct {
    int codigo;
    char funcionario[MAX_NOME];
    char cliente[MAX_NOME];
    Item itens[MAX_ITENS];
    int num_itens;
    float total;
    time_t data;
} NotaFiscal;
/////////////////////////////////


Funcionario funcionarios[MAX_FUNCIONARIOS];
int totalFuncionarios = 0;

// --- Protótipos das Funções ---
void cadastrarFuncionario();
void apagarFuncionario();
bool funcionarioExiste(const char* nome);
void listarFuncionarios();
void salvarFuncionarios();
void carregarFuncionarios();
void menuNota();
void criarNotaFiscal();
bool codigoExiste(int codigo);
void listarNotas();
void excluirNota();
void menuFuncionarios();
int main();

// --- Funções dos Funcionários ---
void cadastrarFuncionario() {
    if (totalFuncionarios >= MAX_FUNCIONARIOS) {
        printf("Limite de funcionarios atingido!\n");
        return;
    }

    printf("Digite o nome do funcionario: ");
    char nome[MAX_NOME];
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remove o \n

    if (funcionarioExiste(nome)) {
        printf("Funcionario ja cadastrado!\n");
    } else {
        strcpy(funcionarios[totalFuncionarios].nome, nome);
        totalFuncionarios++;
        salvarFuncionarios();
        printf("Funcionario cadastrado com sucesso!\n");
    }
    printf("Pressione qualquer tecla para continuar...");
    getch();
}

void apagarFuncionario() {
    printf("Digite o nome do funcionario a ser apagado: ");
    char nome[MAX_NOME];
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    bool encontrado = false;
    for (int i = 0; i < totalFuncionarios; i++) {
        if (strcmp(funcionarios[i].nome, nome) == 0) {
            // Move os funcionários posteriores uma posição para trás
            for (int j = i; j < totalFuncionarios - 1; j++) {
                strcpy(funcionarios[j].nome, funcionarios[j+1].nome);
            }
            totalFuncionarios--;
            encontrado = true;
            salvarFuncionarios();
            printf("Funcionario removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Funcionario nao encontrado!\n");
    }
    printf("Pressione qualquer tecla para continuar...");
    getch();
}

bool funcionarioExiste(const char* nome) {
    for (int i = 0; i < totalFuncionarios; i++) {
        if (strcmp(funcionarios[i].nome, nome) == 0) {
            return true;
        }
    }
    return false;
}

void listarFuncionarios() {
    printf("\n--- FUNCIONARIOS CADASTRADOS ---\n");
    for (int i = 0; i < totalFuncionarios; i++) {
        printf("%d. %s\n", i+1, funcionarios[i].nome);
    }
    printf("\nPressione qualquer tecla para continuar...");
    getch();
}

void salvarFuncionarios() {
    FILE *arquivo = fopen("funcionarios.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar funcionarios!\n");
        return;
    }

    for (int i = 0; i < totalFuncionarios; i++) {
        fprintf(arquivo, "%s\n", funcionarios[i].nome);
    }

    fclose(arquivo);
}

void carregarFuncionarios() {
    FILE *arquivo = fopen("funcionarios.txt", "r");
    if (arquivo == NULL) {
        return; // Arquivo não existe ainda
    }

    char nome[MAX_NOME];
    while (fgets(nome, MAX_NOME, arquivo) != NULL) {
        nome[strcspn(nome, "\n")] = '\0';
        if (totalFuncionarios < MAX_FUNCIONARIOS) {
            strcpy(funcionarios[totalFuncionarios].nome, nome);
            totalFuncionarios++;
        }
    }

    fclose(arquivo);
}

//--- Menu notas fiscal ---
void menuNota() {
    int opcao;
    system("cls || clear");
    do {
        printf("\n--- Sistema de Notas Fiscais ---\n");
        printf("1. Cadastrar nova nota fiscal\n");
        printf("2. Listar todas as notas fiscais\n");
        printf("3. Excluir nota fiscal\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                criarNotaFiscal();
                break;
            case 2:
                listarNotas();
                break;
            case 3:
                excluirNota();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

// --- Função criar Nota Fiscal ---
void criarNotaFiscal() {
    system("cls || clear");
    NotaFiscal nota;
    nota.num_itens = 0;
    nota.total = 0.0;
    nota.data = time(NULL);
    char nomeFuncionario[MAX_NOME];

    printf("\n--- CRIAR NOTA FISCAL ---\n");

    //pede o numero da nota fiscal e ver se ela existe ou não
        do {
            printf("Número da nota fiscal: ");
            scanf("%d", &nota.codigo);
            
            if (codigoExiste(nota.codigo)) {
                printf("O número escolhido já pertence a uma nota fiscal. Escolha outro número.\n");
            }
        } while (codigoExiste(nota.codigo));

    //procura o funcionario e diz se existe ou não
        do {
            printf("Digite o nome do funcionario: ");
            fgets(nomeFuncionario, MAX_NOME, stdin);
            nomeFuncionario[strcspn(nomeFuncionario, "\n")] = '\0';
    
            if (!funcionarioExiste(nomeFuncionario)) {
                printf("Funcionario nao cadastrado!\n");
            }
    
        } while (!funcionarioExiste(nomeFuncionario));
        
        printf("Nome do cliente: ");
        fgets(nota.cliente, MAX_NOME, stdin);
        nota.cliente[strcspn(nota.cliente, "\n")] = '\0';
        
        printf("\nCadastro de Itens (máximo %d itens)\n", MAX_ITENS);
        char continuar = 's';
        
        while (continuar == 's' && nota.num_itens < MAX_ITENS) {
            printf("\nItem %d:\n", nota.num_itens + 1);
            
            printf("Nome do item: ");
            fgets(nota.itens[nota.num_itens].nome, MAX_NOME, stdin);
            nota.itens[nota.num_itens].nome[strcspn(nota.itens[nota.num_itens].nome, "\n")] = '\0';
            
            printf("Quantidade: ");
            scanf("%d", &nota.itens[nota.num_itens].quantidade);
            
            printf("Preço unitário: ");
            scanf("%f", &nota.itens[nota.num_itens].preco);
            
            nota.total += nota.itens[nota.num_itens].quantidade * nota.itens[nota.num_itens].preco;
            nota.num_itens++;
            
            if (nota.num_itens < MAX_ITENS) {
                printf("Deseja adicionar outro item? (s/n): ");
                scanf("%c", &continuar);
            } else {
                printf("Limite máximo de itens atingido.\n");
            }
    }
    // Salvar no arquivo
    FILE *arquivo = fopen(ARQUIVO_DADOS, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para salvar!\n");
        return;
    }
    
    fprintf(arquivo, "Código: %d\n", nota.codigo);
    fprintf(arquivo, "Funcionário: %s\n", nota.funcionario);
    fprintf(arquivo, "Cliente: %s\n", nota.cliente);
    fprintf(arquivo, "Data: %s", ctime(&nota.data));
    fprintf(arquivo, "Itens:\n");
    
    for (int i = 0; i < nota.num_itens; i++) {
        fprintf(arquivo, "- %s, Quantidade: %d, Preço: R$%.2f\n", 
                nota.itens[i].nome, nota.itens[i].quantidade, nota.itens[i].preco);
    }
    
    fprintf(arquivo, "Total: R$%.2f\n", nota.total);
    fprintf(arquivo, "--------------------------------\n");
    fclose(arquivo);
    
    printf("\nNota fiscal cadastrada com sucesso!\n");
}

// ver se o codigo da nota já existe
bool codigoExiste(int codigo) {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "r");
    if (arquivo == NULL) {
        return false;
    }

    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strstr(linha, "Código:") != NULL) {
            int codigo_atual;
            scanf(linha, "Código: %d", &codigo_atual);
            if (codigo_atual == codigo) {
                fclose(arquivo);
                return true;
            }
        }
    }

    fclose(arquivo);
    return false;
}

void listarNotas() {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "r");
    if (arquivo == NULL) {
        printf("Nenhuma nota fiscal cadastrada ainda.\n");
        return;
    }
    
    printf("\n--- Notas Fiscais Cadastradas ---\n");
    
    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }
    
    fclose(arquivo);
}

void excluirNota() {
    int codigo;
    printf("\nDigite o código da nota fiscal que deseja excluir: ");
    scanf("%d", &codigo);
    
    FILE *arquivo = fopen(ARQUIVO_DADOS, "r");
    if (arquivo == NULL) {
        printf("Nenhuma nota fiscal cadastrada ainda.\n");
        return;
    }
    
    FILE *temp = fopen(ARQUIVO_TEMP, "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(arquivo);
        return;
    }
    
    char linha[200];
    int encontrou = 0;
    int excluir = 0;
    
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strstr(linha, "Código:") != NULL) {
            int codigo_atual;
            sscanf(linha, "Código: %d", &codigo_atual);
            
            if (codigo_atual == codigo) {
                encontrou = 1;
                excluir = 1;
                continue;
            } else {
                excluir = 0;
            }
        }
        
        if (!excluir) {
            fprintf(temp, "%s", linha);
        }
    }
    
    fclose(arquivo);
    fclose(temp);
    
    if (encontrou) {
        remove(ARQUIVO_DADOS);
        rename(ARQUIVO_TEMP, ARQUIVO_DADOS);
        printf("Nota fiscal com código %d excluída com sucesso.\n", codigo);
    } else {
        remove(ARQUIVO_TEMP);
        printf("Nota fiscal com código %d não encontrada.\n", codigo);
    }
}

// --- Menu de Funcionários ---
void menuFuncionarios() {
    int opcao;
    do {
        system("cls || clear");
        printf("\n--- MENU FUNCIONARIOS ---\n");
        printf("\n[1] Cadastrar funcionario\n");
        printf("[2] Apagar funcionario\n");
        printf("[3] Listar funcionarios\n");
        printf("[4] Voltar\n");
        printf("\nEscolha uma opcao: ");
        opcao = getch();

        switch(opcao) {
            case '1': cadastrarFuncionario(); break;
            case '2': apagarFuncionario(); break;
            case '3': listarFuncionarios(); break;
            case '4': return;
            default: printf("Opcao invalida!\n"); getch();
        }
    } while (1);
}

// --- MAIN ---
int main() {
    carregarFuncionarios(); // Carrega os funcionários do arquivo

    int opcao;
    do {
        system("cls || clear");
        printf("\n==== CAIXA DE SUPERMERCADO ====\n");
        printf("\n[1] NOVA COMPRA\n");
        printf("[2] ITENS\n");
        printf("[3] FUNCIONARIOS\n");
        printf("[0] SAIR\n");
        printf("\nEscolha uma opcao: ");
        opcao = getch();

        switch(opcao) {
            case '1': menuNota(); break;
            case '2': printf("\nOpcao ITENS selecionada."); getch(); break;
            case '3': menuFuncionarios(); break;
            case '0': printf("\nSaindo...\n"); break;
            default: printf("\nOpcao invalida!"); getch();
        }
    } while (opcao != '0');

    return 0;
}