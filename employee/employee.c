#include <employee.h>
#include <string.h>

static Employee emp[100];
static int next_employee = 0;

void register_employee() {
  printf("\033[H\033[J");
  printf("Digite o nome do funcionário: ");
  scanf("%s", emp[next_employee].name);
  printf("Digite a idade: ");
  scanf("%d", &emp[next_employee].age);
  printf("Digite o salário: ");
  scanf("%f", &emp[next_employee].wage);
  printf("Digite o email: ");
  scanf("%s", emp[next_employee].email);
  emp[next_employee].id = next_employee;
  printf("Funcionário cadastrado com sucesso! ID: %d\n", emp[next_employee].id);
  next_employee++;
  sleep(2);
}

void search_employee() {
  printf("\033[H\033[J");
  char input[50];
  printf("Digite o nome do funcionário ou ID: ");
  scanf("%s", input);

  for (int i = 0; i < next_employee; i++) {
    if (strcmp(emp[i].name, input) == 0 || atoi(input) == emp[i].id) {
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
  int id;
  printf("Digite o ID do funcionário para deletar: ");
  scanf("%d", &id);

  if (id >= 0 && id < next_employee) {
    for (int i = id; i < next_employee - 1; i++) {
      emp[i] = emp[i + 1];
      emp[i].id = i;
    }
    next_employee--;
    printf("Funcionário deletado com sucesso.\n");
  } else {
    printf("ID inválido.\n");
  }
  sleep(2);
}

void show_employee() {
  printf("\033[H\033[J");
  printf("Lista de Funcionários:\n");
  for (int i = 0; i < next_employee; i++) {
    printf("ID: %d | Nome: %s | Idade: %d | Salário: %.2f | Email: %s\n",
           emp[i].id, emp[i].name, emp[i].age, emp[i].wage, emp[i].email);
  }
  sleep(4);
}

void modify_employee() {
  printf("\033[H\033[J");
  char input[50];
  printf("Digite o nome ou ID do funcionário a modificar: ");
  scanf("%s", input);

  EmployeeModder e = NULL;
  for (int i = 0; i < next_employee; i++) {
    if (strcmp(emp[i].name, input) == 0 || atoi(input) == emp[i].id) {
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

    printf("Funcionário modificado com sucesso!\n");
  } else {
    printf("Funcionário não encontrado.\n");
  }
  sleep(2);
}
