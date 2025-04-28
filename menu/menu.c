#define _XOPEN_SOURCE 700
#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../main/utils.h"
#include "../items/items.h"
#include "../employee/employee.h"
#include "../establishment/establishment.h"
#include "../payment/payment.h"

const char *logo[] = {
    "   ######      ####    ",
    "  ##    ##     ####    ",
    " ##            ####    ",
    " ##            ####    ",
    " ##     ###    ####    ",
    "  ########     ####    ",
    "    ####       ####    ",
    "                       ",
    " CENTRO DE INFORMATICA ",
    "     SUPERMARKET       ",
    NULL
};

void animate_logo_start() {
    erase();
    refresh();
    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);
    int logo_height = 0;
    int logo_width = strlen(logo[0]);
    while (logo[logo_height] != NULL) logo_height++;
    int starty = (term_height - logo_height) / 2;
    int startx = (term_width - logo_width) / 2;

    for (int i = 0; logo[i] != NULL; i++) {
        size_t len = strlen(logo[i]);
        for (size_t j = 0; j < len; j++) {
            mvaddch(starty + i, startx + j, logo[i][j]);
            refresh();
            usleep(12000);
        }
        usleep(30000);
    }
    usleep(400000);
}

void animate_logo_end() {
    erase();
    refresh();
    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);
    int logo_height = 0;
    int logo_width = strlen(logo[0]);
    while (logo[logo_height] != NULL) logo_height++;
    int starty = (term_height - logo_height) / 2;
    int startx = (term_width - logo_width) / 2;

    for (int i = 0; logo[i] != NULL; i++) {
        mvprintw(starty + i, startx, "%s", logo[i]);
    }
    refresh();
    usleep(400000);

    for (int i = logo_height - 1; i >= 0; i--) {
        size_t len = strlen(logo[i]);
        for (ssize_t j = len; j > 0; j--) {
            mvaddch(starty + i, startx + j - 1, ' ');
            refresh();
            usleep(8000);
        }
    }
    usleep(200000);
}

void update_status_bar() {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char buffer[64];
    strftime(buffer, sizeof(buffer), " %d/%m/%Y %H:%M:%S ", tm_info);

    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);

    attron(A_REVERSE);
    mvhline(term_height - 1, 0, ' ', term_width);
    mvprintw(term_height - 1, (term_width - strlen(buffer)) / 2, "%s", buffer);
    attroff(A_REVERSE);
    refresh();
}

void reset_screen(WINDOW **menu_win, int height, int width) {
    if (*menu_win != NULL) delwin(*menu_win);
    erase();
    refresh();
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;
    *menu_win = newwin(height, width, starty, startx);
    wbkgd(*menu_win, COLOR_PAIR(1));
    box(*menu_win, 0, 0);
    wrefresh(*menu_win);
    update_status_bar();
}

void print_menu(WINDOW *menu_win, const char **options, int highlight) {
    werase(menu_win);
    int win_height, win_width;
    getmaxyx(menu_win, win_height, win_width);
    box(menu_win, 0, 0);

    int menu_lines = 0;
    size_t max_option_len = 0;
    while (options[menu_lines] != NULL) {
        size_t len = strlen(options[menu_lines]);
        if (len > max_option_len) max_option_len = len;
        menu_lines++;
    }

    int logo_lines = 0;
    int logo_width = strlen(logo[0]);
    while (logo[logo_lines] != NULL) logo_lines++;

    int starty_menu = (win_height - menu_lines) / 2;
    int startx_menu = (win_width / 4) - (max_option_len / 2);
    int starty_logo = (win_height - logo_lines) / 2;
    int startx_logo = (win_width * 3 / 4) - (logo_width / 2);

    for (int i = 0; i < menu_lines; i++) {
        if (i == highlight)
            wattron(menu_win, A_REVERSE | A_BOLD | COLOR_PAIR(1));
        else
            wattron(menu_win, A_BOLD | COLOR_PAIR(1));

        mvwprintw(menu_win, starty_menu + i, startx_menu, "%s", options[i]);

        if (i == highlight)
            wattroff(menu_win, A_REVERSE | A_BOLD | COLOR_PAIR(1));
        else
            wattroff(menu_win, A_BOLD | COLOR_PAIR(1));
    }

    for (int i = 0; logo[i] != NULL; i++) {
        mvwprintw(menu_win, starty_logo + i, startx_logo, "%s", logo[i]);
    }

    wrefresh(menu_win);
    update_status_bar();
}

void pause_screen() {
    int width = 40, height = 5;
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;
    WINDOW *pause_win = newwin(height, width, starty, startx);
    box(pause_win, 0, 0);
    mvwprintw(pause_win, 2, (width - 28) / 2, "Pressione qualquer tecla...");
    wrefresh(pause_win);
    getch();
    delwin(pause_win);
}

void produtos_menu(WINDOW **menu_win) {
    const char *produtos_options[] = {
        "Cadastrar Produto", "Buscar Produto", "Modificar Produto",
        "Listar Produtos", "Deletar Produto", "Voltar", NULL
    };
    int highlight = 0, choice, menu_size = 0;
    while (produtos_options[menu_size] != NULL) menu_size++;

    while (1) {
        print_menu(*menu_win, produtos_options, highlight);
        choice = getch();
        switch (choice) {
            case KEY_UP: highlight = (highlight - 1 + menu_size) % menu_size; break;
            case KEY_DOWN: highlight = (highlight + 1) % menu_size; break;
            case 10:
                clear();
                refresh();
                switch (highlight) {
                    case 0: endwin(); register_item(); pause_screen(); reset_screen(menu_win, 20, 100); break;
                    case 1: endwin(); search_item(); pause_screen(); reset_screen(menu_win, 20, 100); break;
                    case 2: endwin(); modify_item(); pause_screen(); reset_screen(menu_win, 20, 100); break;
                    case 3: endwin(); show_items(); pause_screen(); reset_screen(menu_win, 20, 100); break;
                    case 4: endwin(); delete_item(); pause_screen(); reset_screen(menu_win, 20, 100); break;
                    case 5: return;
                }
                break;
        }
    }
}

void funcionarios_menu(WINDOW **menu_win) {
    const char *funcionarios_options[] = {
        "Cadastrar Funcionário", "Buscar Funcionário", "Modificar Funcionário",
        "Listar Funcionários", "Deletar Funcionário", "Voltar", NULL
    };
    int highlight = 0, choice, menu_size = 0;
    while (funcionarios_options[menu_size] != NULL) menu_size++;

    while (1) {
        print_menu(*menu_win, funcionarios_options, highlight);
        choice = getch();
        switch (choice) {
            case KEY_UP: highlight = (highlight - 1 + menu_size) % menu_size; break;
            case KEY_DOWN: highlight = (highlight + 1) % menu_size; break;
            case 10:
                clear();
                refresh();
                switch (highlight) {
                    case 0: endwin(); register_employee(); pause_screen(); reset_screen(menu_win, 20, 100); break;
                    case 1: endwin(); search_employee(); pause_screen(); reset_screen(menu_win, 20, 100); break;
                    case 2: endwin(); modify_employee(); pause_screen(); reset_screen(menu_win, 20, 100); break;
                    case 3: endwin(); show_employee(); pause_screen(); reset_screen(menu_win, 20, 100); break;
                    case 4: endwin(); delete_employee(); pause_screen(); reset_screen(menu_win, 20, 100); break;
                    case 5: return;
                }
                break;
        }
    }
}

void establishment_menu(WINDOW **menu_win) {
    const char *establishment_options[] = {
        "Cadastrar Estabelecimento", "Modificar Estabelecimento", "Visualizar Estabelecimento", "Voltar", NULL
    };
    int highlight = 0, choice, menu_size = 0;
    while (establishment_options[menu_size] != NULL) menu_size++;

    while (1) {
        print_menu(*menu_win, establishment_options, highlight);
        choice = getch();
        switch (choice) {
            case KEY_UP: highlight = (highlight - 1 + menu_size) % menu_size; break;
            case KEY_DOWN: highlight = (highlight + 1) % menu_size; break;
            case 10:
                clear();
                refresh();
                switch (highlight) {
                    case 0: endwin(); register_establishment(); pause_screen(); reset_screen(menu_win, 20, 100); break;
                    case 1: endwin(); modify_establishment(); pause_screen(); reset_screen(menu_win, 20, 100); break;
                    case 2: endwin(); show_establishment(); pause_screen(); reset_screen(menu_win, 20, 100); break;
                    case 3: return;
                }
                break;
        }
    }
}

void pagamento_menu(WINDOW **menu_win) {
    const char *payment_options[] = {
        "Realizar Pagamento", "Voltar", NULL
    };
    int highlight = 0, choice, menu_size = 0;
    while (payment_options[menu_size] != NULL) menu_size++;

    while (1) {
        print_menu(*menu_win, payment_options, highlight);
        choice = getch();
        switch (choice) {
            case KEY_UP: highlight = (highlight - 1 + menu_size) % menu_size; break;
            case KEY_DOWN: highlight = (highlight + 1) % menu_size; break;
            case 10:
                clear();
                refresh();
                switch (highlight) {
                    case 0: endwin(); make_payment(); pause_screen(); reset_screen(menu_win, 20, 100); break;
                    case 1: return;
                }
                break;
        }
    }
}

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_BLUE, COLOR_BLACK);
        init_pair(2, COLOR_BLACK, COLOR_BLACK);
    }

    bkgd(COLOR_PAIR(0));
    animate_logo_start();

    const char *main_options[] = {
        "Produtos", "Funcionários", "Estabelecimento", "Pagamento", "Sair", NULL
    };

    int highlight = 0, choice, menu_size = 0;
    while (main_options[menu_size] != NULL) menu_size++;

    WINDOW *menu_win = NULL;
    reset_screen(&menu_win, 20, 100);

    while (1) {
        print_menu(menu_win, main_options, highlight);
        choice = getch();
        switch (choice) {
            case KEY_UP: highlight = (highlight - 1 + menu_size) % menu_size; break;
            case KEY_DOWN: highlight = (highlight + 1) % menu_size; break;
            case 10:
                clear();
                refresh();
                switch (highlight) {
                    case 0: produtos_menu(&menu_win); break;
                    case 1: funcionarios_menu(&menu_win); break;
                    case 2: establishment_menu(&menu_win); break;
                    case 3: pagamento_menu(&menu_win); break;
                    case 4: animate_logo_end(); endwin(); exit(0);
                }
                break;
        }
    }

    endwin();
    return 0;
}
