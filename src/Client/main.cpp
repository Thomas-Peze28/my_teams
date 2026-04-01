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

    std::string ip = argv[1];
    uint16_t port = std::stoi(argv[2]);

    client.initClient(ip, port);
    client.run();
    return EXIT_SUCCESS;
}