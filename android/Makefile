C = gcc
CFLAGS = -Wall -g
TARGET = main

SRC = main.c includes/ctrl/ctrl.c view.c includes/model/model.c
OBJ = $(SRC:.c=.o)

RM = rm -f

$(TARGET): $(OBJ)
	    $(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

run: $(TARGET)
	    ./$(TARGET)

clean:
	    $(RM) $(OBJ) $(TARGET)

