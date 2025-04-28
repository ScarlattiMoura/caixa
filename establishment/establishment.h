#pragma once

typedef struct {
    char name[50];
    char address[100];
    int number;
    char cnpj[20];
} Establishment;

void register_establishment();
void modify_establishment();
void show_establishment();
