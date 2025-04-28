CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I./items -I./employee -I./establishment -I./main -I./menu
LDFLAGS = -lncurses

SRC = main/main.c items/items.c employee/employee.c establishment/establishment.c menu/menu.c
OBJ = $(SRC:.c=.o)
TARGET = caixa

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJ)
