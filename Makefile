CC := gcc
TARGET := password_checker
OBJ := password_checker.o output.o


all: password_checker

password_checker: $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

password_checker.o: password_checker.c
	$(CC) -c password_checker.c

output.o: output.c
	$(CC) -c output.c

clean:
	rm -rf $(TARGET) $(OBJ) 
