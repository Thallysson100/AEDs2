# Automatizando o makefile

# Nome do projeto
PROJ_NAME=labirinto

# Arquivos .c
C_SOURCE=$(wildcard *.c)

# Arquivos .h
H_SOURCE=$(wildcard *.h)

# Arquivos objeto
OBJ=$(C_SOURCE:.c=.o)

# Compilador
CC=gcc

# Flags (opções) para o compilador
CC_FLAGS = -c         \
           -W         \
           -Wall      \
           -ansi      \
           -pedantic  \
           -O3        \
           -std=c99

#########################
# Compilação e linkagem #
#########################
all: $(PROJ_NAME) clean

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c %.h
	$(CC) -o $@ $< $(CC_FLAGS)

main.o: main.c $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)

clean:
	@find . -name '*.o' ! -name '$(PROJ_NAME)' -exec rm -rf {} +