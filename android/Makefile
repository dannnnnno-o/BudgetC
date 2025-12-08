C = gcc
CFLAGS = -Wall -g
TARGET = main

SRC = main.c ctrl.c view.c model.c
OBJ = $(SRC:.c=.c)

RM = rm -f

$(TARGET): $(OBJ)
	    $(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

run: $(TARGET)
	    ./$(TARGET)

clean:
	    $(RM) $(OBJ) $(TARGET)

