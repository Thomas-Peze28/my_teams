/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#include "Client.hpp"

bool myTeams::Client::displayHelp(int argc, char *argv[]) const
{
    if (argc != 3) {
        std::cout << "USAGE: ./myteams_cli IP PORT" << std::endl;
        return true;
    }
    for (unsigned int i = 0; argv[i] != NULL; i++) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            std::cout << "USAGE: ./myteams_cli IP PORT" << std::endl;
            std::cout << "IP is the IP address of the server." << std::endl;
            std::cout << "PORT is the port number on which the client connects." << std::endl;
            return true;
        }
    }
    return false;
}