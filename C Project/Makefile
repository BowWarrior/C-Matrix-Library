CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC = TestFile1.c MatrixLibraryAssignment.c
OBJ = $(SRC:.c=.o)
EXEC = TestFile1


all: $(EXEC)

#'-fsanitize=address' can check for misuse of memory/usage of variables outside their scope
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test:
	./TestFile1

clean:
	rm -f $(OBJ) $(EXEC)

run: $(EXEC)
	./$(EXEC)
