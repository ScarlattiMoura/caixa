#include <ncurses.h>
#include "../main/utils.h"
#include "../items/items.h"
#include "../employee/employee.h"


char *menu[] = {"Cadastrar produto", "Procurar produto", "Modificar produto", "Listar produtos", "Deletar produto", "Cadastrar funcionario", "Procurar funcionario", "Modificar funcionario", "Listar Funcionario", "Deletar funcionario" , "Sair", NULL};

char *logo[] = {"  ____                 ",
                " / ___| ___ _ __ ___  ",
                "| |  _ / _ \\ '__/ _ \\ ",
                "| |_| |  __/ | | (_) |",
                " \\____|\\___|_|  \\___/ ",
                "   SUPERMARKET        ",
                NULL};

#define MENU_X 4
#define LOGO_X 40
#define MENU_Y 2

void print_menu(int highlight) {
  clear();

  // Título
  mvprintw(0, MENU_X, "Menu");

  // Itens do menu
  for (int i = 0; menu[i] != NULL; i++) {
    if (i == highlight)
      attron(A_REVERSE);
    mvprintw(MENU_Y + i, MENU_X, "%s", menu[i]);
    if (i == highlight)
      attroff(A_REVERSE);
  }

  // Logo ASCII
  for (int i = 0; logo[i] != NULL; i++) {
    mvprintw(MENU_Y + i, LOGO_X, "%s", logo[i]);
  }

  refresh();
}

int main() {
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  keypad(stdscr, TRUE);

  int highlight = 0;
  int choice;
  int menu_size = 0;
  while (menu[menu_size] != NULL)
    menu_size++;

  print_menu(highlight);

  while (1) {
    choice = getch();
    switch (choice) {
      case KEY_UP:
        highlight = (highlight - 1 + menu_size) % menu_size;
        break;
      case KEY_DOWN:
        highlight = (highlight + 1) % menu_size;
        break;
      case 10:  // Enter
        clear();
        endwin();  // Fecha o modo ncurses

        if (highlight == 0)
          register_item();
        else if (highlight == 1)
          search_item();
        else if (highlight == 2)
          modify_item();
        else if (highlight == 3)
          show_items();
        else if (highlight == 4)
          delete_item();
        else if (highlight == 5)
          register_employee();
        else if (highlight == 6)
          search_employee();
        else if (highlight == 6)
          modify_employee();
        else if (highlight == 6)
          show_employee();
        else if (highlight == 6)
          delete_employee();
        else if (highlight == 6)
          return 0;

        printf("Pressione Enter para continuar...");
        getchar();  // Pausa até o usuário pressionar Enter
        getchar();  // Garante que o buffer esteja limpo

        // Reinicia ncurses
        initscr();
        noecho();
        cbreak();
        curs_set(0);
        keypad(stdscr, TRUE);
        break;
      default:
        break;
    }
    print_menu(highlight);
  }

  endwin();
  return 0;
}
