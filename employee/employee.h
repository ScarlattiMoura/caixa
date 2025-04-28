#pragma once
#include <stdio.h>

typedef struct {
    int id;
    int age;
    float wage;
    char name[50];
    char email[50];
} Employee, *EmployeeModder;

// Funções principais
void register_employee();
void search_employee();
void delete_employee();
void show_employee();
void modify_employee();

// Funções auxiliares (helpers para pagamento)
void load_employees_from_file();
void save_employees_to_file();
int get_employee_count();
Employee* get_employee_by_index(int index);
Employee* get_employee_by_id(int id);
