/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** main
*/

#include "Server.hpp"

int main(int argc, char *argv[])
{
    myTeams::Server server;

    if (server.displayHelp(argc, argv))
        return EXIT_SUCCESS;
    server.initServer(static_cast<u_int16_t>(std::atoi(argv[1])));
    server.runServer();
    return EXIT_SUCCESS;
}