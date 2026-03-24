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
    return EXIT_SUCCESS;
}