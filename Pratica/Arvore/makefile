# Nome do projeto
PROJ_NAME = Projeto_arvore.exe

# Arquivos .c
C_SOURCE = $(wildcard *.c)

# Arquivos objeto
OBJ = $(C_SOURCE:.c=.o)

# Compilador
CC = gcc

# Flags (opções) para o compilador
CC_FLAGS =-g -c -Wall -Wpedantic -MMD -MP

#########################
# Compilação e linkagem #
#########################
all: $(PROJ_NAME)

# Regra para linkar o executável
$(PROJ_NAME): $(OBJ)
	$(CC) -g $^ -o $@

# Regra para compilar os arquivos objeto
%.o: %.c
	$(CC) $(CC_FLAGS) -o $@ $<

# Regra para limpar os arquivos gerados
clean:
	rm -rf *.o *.d *~ $(PROJ_NAME)

# Incluindo automaticamente as dependências geradas
-include $(OBJ:.o=.d)
