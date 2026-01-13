CC = gcc
CFLAGS = -Wall -g
TARGET = main

SRC = main.c includes/ctrl/ctrl.c includes/view/view.c includes/model/model.c
OBJ = $(SRC:.c=.o)

ifeq ($(OS),Windows_NT)
    RM = del /Q
    TARGET_EXT = .exe
else
    RM = rm -f
    TARGET_EXT =
endif

$(TARGET)$(TARGET_EXT): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET)$(TARGET_EXT) $(SRC)

run: $(TARGET)$(TARGET_EXT)
	./$(TARGET)$(TARGET_EXT)

clean:
	$(RM) $(SRC) $(TARGET)$(TARGET_EXT)
