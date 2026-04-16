/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** NetworkServer
*/

#include "NetworkServer.hpp"

myTeams::NetworkServer::NetworkServer(PollFD &poll_fds, unsigned int &client_online) : _poll_fds(poll_fds), _client_online(client_online)
{
}

void myTeams::NetworkServer::initNetworkServer(uint16_t port)
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {};
    int opt = 1;

    if (server_socket == -1)
        return;

    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        close(server_socket);
        return;
    }
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    if (bind(server_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        close(server_socket);
        return;
    }
    if (listen(server_socket, 10) == -1) {
        close(server_socket);
        return;
    }
    _server_addr = addr;
    _server_socket = server_socket;
    _poll_fds.initPollFD(_server_socket);
}

std::pair<int, std::unique_ptr<myTeams::Client>> myTeams::NetworkServer::acceptNewConnection()
{
    struct sockaddr_in client_addr = {};
    socklen_t client_len = sizeof(client_addr);
    int client_fd = -1;

    if (_server_socket == -1)
        return {-1, nullptr};
    client_fd = accept(_server_socket, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0)
        return {-1, nullptr};
    if (_client_online >= MAX_CLIENTS) {
        close(client_fd);
        return {-1, nullptr};
    }
    if (_poll_fds.addNewClient(client_fd) == false) {
        close(client_fd);
        return {-1, nullptr};
    }
    return {client_fd, std::make_unique<Client>(client_fd)};
}