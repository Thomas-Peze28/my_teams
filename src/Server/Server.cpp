/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#include "Server.hpp"

bool myTeams::Server::displayHelp(int argc, char *argv[]) const
{
    for (unsigned int i = 0; argv[i] != NULL; i++) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            std::cout << "USAGE: ./myteams_server PORT" << std::endl;
            std::cout << "PORT is the port number on which the server socket listens." << std::endl;
            return true;
        }
    }

    if (argc != 2) {
        std::cout << "USAGE: ./myteams_server PORT" << std::endl;
        return true;
    }
    return false;
}