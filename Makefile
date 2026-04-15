##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## my_teams
##

# Colors
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
MAGENTA=\033[0;35m
CYAN=\033[0;36m
RESET=\033[0m

CLIENT_DIR = client
SERVER_DIR = server

CLIENT_BIN = teams_cli
SERVER_BIN = teams_server

.SILENT:

.PHONY: all client server binaires clean fclean re

all: client server binaires

client:
	@$(MAKE) -C $(CLIENT_DIR) --no-print-directory

server:
	@$(MAKE) -C $(SERVER_DIR) --no-print-directory

binaires:
	@mv $(CLIENT_DIR)/$(CLIENT_BIN) ./$(CLIENT_BIN)
	@mv $(SERVER_DIR)/$(SERVER_BIN) ./$(SERVER_BIN)
	@printf "$(GREEN)[OK]$(RESET) Root binaries '$(CLIENT_BIN)' and '$(SERVER_BIN)' ready.\n"

clean:
	@$(MAKE) -C $(CLIENT_DIR) clean --no-print-directory
	@$(MAKE) -C $(SERVER_DIR) clean --no-print-directory
	@printf "$(BLUE)[INFO]$(RESET) Client and server object files removed.\n"

fclean: clean
	@$(MAKE) -C $(CLIENT_DIR) fclean --no-print-directory
	@$(MAKE) -C $(SERVER_DIR) fclean --no-print-directory
	@rm -f $(CLIENT_BIN) $(SERVER_BIN)
	@printf "$(BLUE)[INFO]$(RESET) Client and server binaries removed.\n"

re: fclean all
	@printf "$(BLUE)[INFO]$(RESET) Project rebuilt successfully.\n"