#pragma once 
#include <../main/utils.h>

typedef struct {
  int id;
  int age;
  float wage;
  char name[50];
  char email[50];
} Employee, *EmployeeModder;

void register_employee();
void modify_employee();
void search_employee();
void delete_employee();
void show_employee();
