#include <employee.h>
#include <string.h>
#include <stdlib.h>

#define EMPLOYEE_FILE_PATH "registration/employee.txt"

static Employee emp[100];
static int next_employee = 0;
static int next_id = 0;

// Carrega funcionários do arquivo
void load_employees_from_file() {
    FILE *file = fopen(EMPLOYEE_FILE_PATH, "r");
    if (!file) return;

    next_employee = 0;
    next_id = 0;
    while (fscanf(file, "%d %49s %d %f %49s", &emp[next_employee].id, emp[next_employee].name, &emp[next_employee].age, &emp[next_employee].wage, emp[next_employee].email) == 5) {
        if (emp[next_employee].id >= next_id)
            next_id = emp[next_employee].id + 1;
        next_employee++;
    }
    fclose(file);
}

// Salva todos os funcionários no arquivo
void save_employees_to_file() {
    FILE *file = fopen(EMPLOYEE_FILE_PATH, "w");
    if (!file) {
        perror("Erro ao abrir employee.txt para escrita");
        return;
    }

    for (int i = 0; i < next_employee; i++) {
        if (emp[i].id != -1) {
            fprintf(file, "%d %s %d %.2f %s\n", emp[i].id, emp[i].name, emp[i].age, emp[i].wage, emp[i].email);
        }
    }
    fclose(file);
}

void register_employee() {
    printf("\033[H\033[J");
    load_employees_from_file();

    printf("Digite o nome do funcionário: ");
    scanf("%s", emp[next_employee].name);
    printf("Digite a idade: ");
    scanf("%d", &emp[next_employee].age);
    printf("Digite o salário: ");
    scanf("%f", &emp[next_employee].wage);
    printf("Digite o email: ");
    scanf("%s", emp[next_employee].email);

    emp[next_employee].id = next_id++;
    next_employee++;

    save_employees_to_file();

    printf("Funcionário cadastrado com sucesso! ID: %d\n", emp[next_employee-1].id);
    sleep(2);
}

void search_employee() {
    printf("\033[H\033[J");
    load_employees_from_file();

    char input[50];
    printf("Digite o nome do funcionário ou ID: ");
    scanf("%s", input);

    for (int i = 0; i < next_employee; i++) {
        if (emp[i].id != -1 && (strcmp(emp[i].name, input) == 0 || atoi(input) == emp[i].id)) {
            printf("Funcionário encontrado:\n");
            printf("ID: %d | Nome: %s | Idade: %d | Salário: %.2f | Email: %s\n",
                   emp[i].id, emp[i].name, emp[i].age, emp[i].wage, emp[i].email);
            sleep(3);
            return;
        }
    }
    printf("Funcionário não encontrado.\n");
    sleep(2);
}

void delete_employee() {
    printf("\033[H\033[J");
    load_employees_from_file();

    int id;
    printf("Digite o ID do funcionário para deletar: ");
    scanf("%d", &id);

    for (int i = 0; i < next_employee; i++) {
        if (emp[i].id == id) {
            emp[i].id = -1; // Marca como deletado
            save_employees_to_file();
            printf("Funcionário deletado com sucesso.\n");
            sleep(2);
            return;
        }
    }

    printf("ID inválido.\n");
    sleep(2);
}

void show_employee() {
    printf("\033[H\033[J");
    load_employees_from_file();

    printf("Lista de Funcionários:\n");
    for (int i = 0; i < next_employee; i++) {
        if (emp[i].id != -1) {
            printf("ID: %d | Nome: %s | Idade: %d | Salário: %.2f | Email: %s\n",
                   emp[i].id, emp[i].name, emp[i].age, emp[i].wage, emp[i].email);
        }
    }
    sleep(4);
}

void modify_employee() {
    printf("\033[H\033[J");
    load_employees_from_file();

    char input[50];
    printf("Digite o nome ou ID do funcionário a modificar: ");
    scanf("%s", input);

    EmployeeModder e = NULL;
    for (int i = 0; i < next_employee; i++) {
        if (emp[i].id != -1 && (strcmp(emp[i].name, input) == 0 || atoi(input) == emp[i].id)) {
            e = &emp[i];
            break;
        }
    }

    if (e != NULL) {
        printf("Funcionário atual:\n");
        printf("ID: %d | Nome: %s | Idade: %d | Salário: %.2f | Email: %s\n",
               e->id, e->name, e->age, e->wage, e->email);

        printf("\nDigite o novo nome: ");
        scanf("%s", e->name);
        printf("Digite a nova idade: ");
        scanf("%d", &e->age);
        printf("Digite o novo salário: ");
        scanf("%f", &e->wage);
        printf("Digite o novo email: ");
        scanf("%s", e->email);

        save_employees_to_file();
        printf("Funcionário modificado com sucesso!\n");
    } else {
        printf("Funcionário não encontrado.\n");
    }
    sleep(2);
}


// Helpers para integração com pagamento
int get_employee_count() {
    return next_employee;
}

Employee* get_employee_by_index(int index) {
    if (index >= 0 && index < next_employee) {
        return &emp[index];
    }
    return NULL;
}

Employee* get_employee_by_id(int id) {
    for (int i = 0; i < next_employee; i++) {
        if (emp[i].id == id) {
            return &emp[i];
        }
    }
    return NULL;
}
