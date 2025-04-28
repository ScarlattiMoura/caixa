#pragma once
#include <stdio.h>

typedef struct {
    int id;
    int qnty;
    float price;
    char name[50];
} Item, *ItemModder;

// Funções principais
void register_item();
void search_item();
void delete_item();
void show_items();
void modify_item();

// Funções auxiliares (helpers para pagamento)
void load_items_from_file();
void save_items_to_file();
int get_item_count();
Item* get_item_by_index(int index);
Item* get_item_by_id(int id);
