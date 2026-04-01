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
    u_int16_t port = static_cast<u_int16_t>(std::stoi(argv[2]));

    client.initClient(ip, port);
    client.run();
    return EXIT_SUCCESS;
}