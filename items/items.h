#pragma once
#include <unistd.h>
#include <../main/utils.h>

typedef struct {
    int id;
    int qnty;
    float price;
    char name[50];
} Item, *ItemModder;

void register_item();
void modify_item();
void search_item();
void delete_item();
void show_items();
