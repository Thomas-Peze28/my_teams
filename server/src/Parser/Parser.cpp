/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Parser
*/

#include "Parser.hpp"

bool myTeams::Parser::isClientDisconnected(int client_socket) const
{
    char buffer[1024] = {0};
    ssize_t bytes_read = recv(client_socket, buffer, sizeof(buffer) - 1, MSG_PEEK | MSG_DONTWAIT);

    if (bytes_read == 0)
        return true;
    if (bytes_read < 0 && errno == ECONNRESET)
        return true;
    if (bytes_read < 0 && (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR))
        return false;
    return false;
}

void myTeams::Parser::handleCommand(int client_socket) const
{
    char buffer[1024] = {0};
    ssize_t bytes_read = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        std::string command(buffer);
        std::cout << "Received command from client " << client_socket << ": " << command << std::endl;
    }
}