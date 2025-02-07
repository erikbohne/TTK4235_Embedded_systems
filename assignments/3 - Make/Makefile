CC = gcc
CFLAGS = -O0 -g3
OBJ = drikke.o main.o grønnsaker.o protein.o taco_krydder.o taco_lefse.o taco_saus.o

.PHONY: clean
clean:
	rm -f *.o taco

.DEFAULT_GOAL := taco
taco: $(OBJ)
	@echo "Koker sammen deilig taco..."
	$(CC) $(CFLAGS) -o taco $(OBJ)