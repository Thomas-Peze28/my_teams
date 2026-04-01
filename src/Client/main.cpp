/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** main
*/

#include "Client.hpp"

int main(int argc, char *argv[])
{
    myTeams::Client client;

    if (client.displayHelp(argc, argv))
        return EXIT_SUCCESS;
    return EXIT_SUCCESS;
}