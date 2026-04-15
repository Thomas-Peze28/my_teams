##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## my_teams
##

SRC     =   src/main.cpp \
			src/Server/Server.cpp \
			src/Client/Client.cpp \
			src/PollFD/PollFD.cpp \
			src/NetworkServer/NetworkServer.cpp

HEADERS =	-I src/Server \
			-I src/Client \
			-I src/PollFD \
			-I src/NetworkServer \

CXX     =   g++

OBJ     =   $(SRC:.cpp=.o)

NAME    =   teams_server

CXXFLAGS = -Wextra -Wall $(HEADERS) -std=c++20

.SILENT:

all:    $(NAME)

$(NAME):    $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)
# 	@echo "[OK] Binary '$(NAME)' compiled successfully."

clean:
	rm -f $(OBJ)
# 	@echo "[INFO] Object files removed."

fclean: clean
	rm -f $(NAME)
# 	@echo "[INFO] Binary '$(NAME)' removed."

re: fclean all
# 	@echo "[INFO] Project rebuilt successfully."