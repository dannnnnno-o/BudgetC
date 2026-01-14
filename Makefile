CC = gcc
CFLAGS = -Wall -g
TARGET = main


ifeq ($(OS),Windows_NT)
    SRC = main.c includes\ctrl\ctrl.c includes\view\view.c includes\model\model.c
    RM = del /Q
    TARGET_EXT = .exe
else
    SRC = main.c includes/ctrl/ctrl.c includes/view/view.c includes/model/model.c
    RM = rm -f
    TARGET_EXT =
endif

OBJ = $(SRC:.c=.o)

$(TARGET)$(TARGET_EXT): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET)$(TARGET_EXT) $(OBJ)

run: $(TARGET)$(TARGET_EXT)
	./$(TARGET)$(TARGET_EXT)

clean:
	$(RM) $(OBJ) $(TARGET)$(TARGET_EXT)
