##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## my_teams
##

SRC     =   src/main.cpp \
			src/Server/Server.cpp \

CXX     =   g++

OBJ     =   $(SRC:.cpp=.o)

NAME    =   myteams_server

CXXFLAGS = -Wextra -Wall -I ./src/Server -std=c++20

.SILENT:

all:    $(NAME)

$(NAME):    $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)
	@echo "[OK] Binary '$(NAME)' compiled successfully."

clean:
	rm -f $(OBJ)
	@echo "[INFO] Object files removed."

fclean: clean
	rm -f $(NAME)
	@echo "[INFO] Binary '$(NAME)' removed."

re: fclean all
	@echo "[INFO] Project rebuilt successfully."

