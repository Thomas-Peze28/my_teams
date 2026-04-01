##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## my_teams
##

# --- Couleurs ---
GREEN       =   \033[0;32m
BLUE        =   \033[0;34m
YELLOW      =   \033[1;33m
RESET       =   \033[0m

CXX         =   g++
CXXFLAGS    =   -Wextra -Wall -std=c++20

# --- Configuration du Serveur ---
SERVER_NAME =   myteams_server

SERVER_SRC  =   src/Server/main.cpp \
				src/Server/Server.cpp

SERVER_OBJ  =   $(SERVER_SRC:.cpp=.o)
SERVER_INC  =   -I ./src/Server

# --- Configuration du Client ---
CLIENT_NAME =   myteams_cli

CLIENT_SRC  =   src/Client/main.cpp \
				src/Client/Client.cpp

CLIENT_OBJ  =   $(CLIENT_SRC:.cpp=.o)
CLIENT_INC  =   -I ./src/Client

.SILENT:

all:    $(SERVER_NAME) $(CLIENT_NAME)

# --- Règles de compilation indépendantes ---
server: $(SERVER_NAME)
client: $(CLIENT_NAME)

# Compilation du Serveur
$(SERVER_NAME): $(SERVER_OBJ)
	$(CXX) -o $(SERVER_NAME) $(SERVER_OBJ) $(CXXFLAGS) $(SERVER_INC)
	@printf "$(GREEN)[OK]$(RESET) Binary '$(SERVER_NAME)' compiled successfully.\n"

# Compilation du Client
$(CLIENT_NAME): $(CLIENT_OBJ)
	$(CXX) -o $(CLIENT_NAME) $(CLIENT_OBJ) $(CXXFLAGS) $(CLIENT_INC)
	@printf "$(GREEN)[OK]$(RESET) Binary '$(CLIENT_NAME)' compiled successfully.\n"

clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)
	@printf "$(BLUE)[INFO]$(RESET) Object files removed.\n"

fclean: clean
	rm -f $(SERVER_NAME) $(CLIENT_NAME)
	@printf "$(BLUE)[INFO]$(RESET) Binaries removed.\n"

re: fclean all
	@printf "$(YELLOW)[INFO]$(RESET) Project rebuilt successfully.\n"