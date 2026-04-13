/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Client
*/

#include "Client.hpp"

myTeams::Client::Client(struct sockaddr_in addr, int socket) : _server_addr(addr), _client_socket(socket)
{
}
