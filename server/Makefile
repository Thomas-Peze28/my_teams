##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## my_teams (Server)
##

# Colors
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
MAGENTA=\033[0;35m
CYAN=\033[0;36m
RESET=\033[0m

SRC     =   src/main.cpp \
			src/Server/Server.cpp \
			src/Client/Client.cpp \
			src/PollFD/PollFD.cpp \
			src/NetworkServer/NetworkServer.cpp \
			src/Parser/Parser.cpp \
			src/Hub/Hub.cpp \
			src/Team/Team.cpp \
			src/Command/Command.cpp \
			src/Channel/Channel.cpp \
			src/Thread/Thread.cpp \

HEADERS =	-I src/Server \
			-I src/Client \
			-I src/PollFD \
			-I src/NetworkServer \
			-I src/Parser \
			-I src/Team \
			-I src/Channel \
			-I src/Thread \
			-I src/Hub \
			-I src/Command \
			-I src/Include \

CXX     =   g++

OBJ     =   $(SRC:.cpp=.o)

NAME    =   teams_server

CXXFLAGS = -Wextra -Wall $(HEADERS) -std=c++20

LDFLAGS  = -L../libs/myteams -lmyteams

.SILENT:

all:    $(NAME)

$(NAME):    $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS) $(LDFLAGS)
	@printf "$(GREEN)[OK]$(RESET) Binary '$(NAME)' compiled successfully.\n"

clean:
	rm -f $(OBJ)
	@printf "$(BLUE)[INFO]$(RESET) Object files removed.\n"

fclean: clean
	rm -f $(NAME)
	@printf "$(BLUE)[INFO]$(RESET) Binary '$(NAME)' removed.\n"

re: fclean all
	@printf "$(BLUE)[INFO]$(RESET) Project rebuilt successfully.\n"