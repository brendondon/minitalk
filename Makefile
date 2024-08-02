# Nome dos executáveis
SERVER = server
CLIENT = client

# Compilador
CC = gcc

# Flags do compilador
CFLAGS = -Wall -Wextra -g

# Arquivos fonte
SERVER_SRCS = server.c #util.c
CLIENT_SRCS = client.c #util.c

# Arquivos objeto
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

# Regra padrão para compilar servidor e cliente
all: $(SERVER) $(CLIENT)

# Regra para criar o executável do servidor
$(SERVER): $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OBJS)

# Regra para criar o executável do cliente
$(CLIENT): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJS)

# Regra para criar arquivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos compilados
clean:
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS) $(SERVER) $(CLIENT)

# Phony targets
.PHONY: all clean
