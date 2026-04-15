##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## my_teams
##

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
	@cp $(CLIENT_DIR)/$(CLIENT_BIN) ./$(CLIENT_BIN)
	@cp $(SERVER_DIR)/$(SERVER_BIN) ./$(SERVER_BIN)
	@echo "[OK] Root binaries '$(CLIENT_BIN)' and '$(SERVER_BIN)' ready."

clean:
	@$(MAKE) -C $(CLIENT_DIR) clean --no-print-directory
	@$(MAKE) -C $(SERVER_DIR) clean --no-print-directory
	@echo "[INFO] Client and server object files removed."

fclean: clean
	@$(MAKE) -C $(CLIENT_DIR) fclean --no-print-directory
	@$(MAKE) -C $(SERVER_DIR) fclean --no-print-directory
	@rm -f $(CLIENT_BIN) $(SERVER_BIN)
	@echo "[INFO] Client and server binaries removed."

re: fclean all
	@echo "[INFO] Project rebuilt successfully."